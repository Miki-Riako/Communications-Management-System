// widgets/system_setting.c
#include "../header.h"

void systemSettingWidget(GtkWidget *parent) {
    systemSettingWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(systemSettingWidgets.window), "通信管理系统 - 经理菜单 - 系统设置");
    gtk_window_set_default_size(GTK_WINDOW(systemSettingWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(systemSettingWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(systemSettingWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(systemSettingWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    systemSettingWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(systemSettingWidgets.window), systemSettingWidgets.grid);
    gtk_widget_set_halign(systemSettingWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(systemSettingWidgets.grid, GTK_ALIGN_CENTER);

    systemSettingWidgets.changePassword_btn = gtk_button_new_with_label("密码维护");
    g_signal_connect(systemSettingWidgets.changePassword_btn, "clicked", G_CALLBACK(on_changePassword_clicked), NULL);
    gtk_grid_attach(GTK_GRID(systemSettingWidgets.grid), systemSettingWidgets.changePassword_btn, 0, 0, 2, 1);

    systemSettingWidgets.resetPassword_btn = gtk_button_new_with_label("重置业务员密码");
    g_signal_connect(systemSettingWidgets.resetPassword_btn, "clicked", G_CALLBACK(on_resetPassword_clicked), NULL);
    gtk_grid_attach(GTK_GRID(systemSettingWidgets.grid), systemSettingWidgets.resetPassword_btn, 0, 1, 2, 1);

    systemSettingWidgets.backupData_btn = gtk_button_new_with_label("数据备份");
    g_signal_connect(systemSettingWidgets.backupData_btn, "clicked", G_CALLBACK(on_backupData_clicked), NULL);
    gtk_grid_attach(GTK_GRID(systemSettingWidgets.grid), systemSettingWidgets.backupData_btn, 0, 2, 2, 1);

    systemSettingWidgets.restoreData_btn = gtk_button_new_with_label("数据恢复");
    g_signal_connect(systemSettingWidgets.restoreData_btn, "clicked", G_CALLBACK(on_restoreData_clicked), NULL);
    gtk_grid_attach(GTK_GRID(systemSettingWidgets.grid), systemSettingWidgets.restoreData_btn, 0, 3, 2, 1);

    WidgetPair *widgetPair = g_slice_new(WidgetPair);
    widgetPair->parentWindow = parent;
    widgetPair->currentWindow = systemSettingWidgets.window;
    systemSettingWidgets.backToManageMenu_btn = gtk_button_new_with_label("返回");
    g_signal_connect(systemSettingWidgets.backToManageMenu_btn, "clicked", G_CALLBACK(on_back_clicked), widgetPair);
    gtk_grid_attach(GTK_GRID(systemSettingWidgets.grid), systemSettingWidgets.backToManageMenu_btn, 0, 4, 2, 1);
    
    gtk_widget_show_all(systemSettingWidgets.window);
    gtk_main();
}

bool changeUserPassword(const char *username, const char *newEncryptedPassword) {
    bool updated = false;
    FILE *file = fopen("user.csv", "r");
    FILE *tempFile = fopen("user_backup.csv", "w");

    if (!file || !tempFile) {
        perror("无法打开文件");
        return false;
    }

    char line[MAX_LENGTH * 3];
    while (fgets(line, sizeof(line), file)) {
        char fileUsername[MAX_LENGTH], filePassword[MAX_LENGTH];
        sscanf(line, "%[^|||]|||%s", fileUsername, filePassword);
        if (isSameString(username, fileUsername)) {
            fprintf(tempFile, "%s|||%s\n", username, newEncryptedPassword);
            updated = true;
        } else {
            fputs(line, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("user.csv");
    rename("user_backup.csv", "user.csv");

    return updated;
}

void changePassword() {
    if (IsManager) {
        char confirmation[10];
        infoInput(confirmation, sizeof(confirmation),"您是经理，无法改变自己的密钥。\n要查看公司密钥吗？这是一个敏感操作。\n输入 'yes' 确认查看，其他任意键取消：");

        if (strcmp(confirmation, "yes") == 0) {
            char message[MAX_LENGTH*2];
            snprintf(message,sizeof(message),"公司密钥是：%s",SECRET_KEY);
            show_info_dialog(NULL,message);
        } else {
            show_info_dialog(NULL,"操作已取消。");
        }
    } else {
        char oldPassword[MAX_LENGTH], newPassword[MAX_LENGTH], confirmPassword[MAX_LENGTH];
        char encryptedOldPassword[MAX_LENGTH * 2], encryptedNewPassword[MAX_LENGTH * 2];

        infoInput(oldPassword, sizeof(oldPassword), "请输入当前密码：");
        xorEncryptDecrypt(oldPassword, strlen(oldPassword), encryptedOldPassword);

        if (!verify(User, encryptedOldPassword)) {
            show_info_dialog(NULL,"密码错误。无法更改密码。");
            return;
        }

        infoInput(newPassword, sizeof(newPassword), "请输入新密码：");
        if (!matchRegex(newPassword)) {
            show_info_dialog(NULL,"密码不符合要求。必须至少8个字符且包含大写字母、小写字母、数字、标点符号中的两种。");
            return;
        }

        infoInput(confirmPassword, sizeof(confirmPassword), "请再次输入新密码以确认：");
        if (!isSameString(newPassword, confirmPassword)) {
            show_info_dialog(NULL,"两次输入的密码不匹配。");
            return;
        }

        xorEncryptDecrypt(newPassword, strlen(newPassword), encryptedNewPassword);
        if (changeUserPassword(User, encryptedNewPassword)) {
            show_info_dialog(NULL,"密码更新成功");
        } else {
            show_info_dialog(NULL,"密码更新失败");
        }
    }
}

void resetPassword() {
    if (!IsManager) {
        show_info_dialog(NULL,"您没有权限执行此操作。");
        return;
    }
    char employeeName[MAX_LENGTH];
    char newPassword[MAX_LENGTH];
    char encryptedNewPassword[MAX_LENGTH * 2];

    infoInput(employeeName, sizeof(employeeName), "请输入要重置密码的业务员用户名：");

    // 检查该用户是否存在
    if (!alreadyExists("user.csv", employeeName)) {
        char message[MAX_LENGTH*2];
        snprintf(message,sizeof(message),"没有找到用户：%s\n", employeeName);
        show_info_dialog(NULL,message);
        return;
    }
    infoInput(newPassword, sizeof(newPassword),"请输入新密码");

    if (!matchRegex(newPassword)) {
        show_info_dialog(NULL,"密码不符合安全要求。");
        return;
    }

    xorEncryptDecrypt(newPassword, strlen(newPassword), encryptedNewPassword);

    // 更新密码
    if (changeUserPassword(employeeName, encryptedNewPassword)) {
        show_info_dialog(NULL,"密码重置成功。");
    } else {
        show_info_dialog(NULL,"密码重置失败。");
    }
}

void backupData() {
    if (!IsManager) {
        show_info_dialog(NULL,"您没有权限执行此操作");
        return;
    }
    char choice[MAX_LENGTH];
    infoInput(choice, sizeof(choice),"请选择备份类型：\n1. 基本信息备份\n2. 分组信息备份\n请输入选择（1-2）：");

    char basePath[10] = "";
    if (isOneChar(choice) && choice[0] == '2') {
        strcpy(basePath, "groups/");
    }

    char filename[MAX_LENGTH];
    char fullPath[2 *MAX_LENGTH ];
    char backupFilename[2 * MAX_LENGTH];  // 留足够空间用于添加前缀

    infoInput(filename, sizeof(filename),"请输入要备份的文件名：");

    // 构建完整的原文件路径和备份文件路径
    snprintf(fullPath, sizeof(fullPath), "%s%s", basePath, filename);
    snprintf(backupFilename, sizeof(backupFilename), "%sbackup_%s", basePath, filename);

    // 执行文件复制操作
    if (!copyFile(fullPath, backupFilename)) {
        show_info_dialog(NULL,"备份失败，请检查文件名和路径是否正确。");
    } else {
        char message[MAX_LENGTH*4];
        snprintf(message,sizeof(message),"备份成功。备份文件名为：%s\n", backupFilename);
        show_info_dialog(NULL,message);
    }
}

void restoreData() {
    if (!IsManager) {
        show_info_dialog(NULL,"您没有权限执行此操作。");
        return;
    }
    char choice[MAX_LENGTH];
    infoInput(choice, sizeof(choice),"请选择恢复类型：\n1. 基本信息恢复\n2. 分组信息恢复\n请输入选择（1-2）：");

    char basePath[10] = "";
    if (isOneChar(choice) && choice[0] == '2') {
        strcpy(basePath, "groups/");
    }

    char backupFilename[MAX_LENGTH];
    char originalFilename[2 * MAX_LENGTH];  // 留足够空间处理文件名和路径

    infoInput(backupFilename, sizeof(backupFilename),"请输入要恢复的备份文件名（包含前缀）：");

    // 构建原始文件路径
    snprintf(originalFilename, sizeof(originalFilename), "%s%s", basePath, backupFilename + 7); // 假设前缀 "backup_" 占用7个字符

    // 检查备份文件是否存在
    char fullBackupPath[2 * MAX_LENGTH];
    snprintf(fullBackupPath, sizeof(fullBackupPath), "%s%s", basePath, backupFilename);
    if (ACCESS(fullBackupPath, F_OK) == -1) {
        show_info_dialog(NULL,"备份文件不存在。");
        return;
    }

    // 执行文件复制操作以恢复数据
    if (!copyFile(fullBackupPath, originalFilename)) {
        show_info_dialog(NULL,"恢复失败，请检查备份文件名和路径是否正确");
    } else {
        char message[MAX_LENGTH*4];
        snprintf(message,sizeof(message),"恢复成功。文件 '%s' 已被恢复。\n", originalFilename);
        show_info_dialog(NULL,message);
    }
}

static void on_changePassword_clicked(GtkWidget *widget, gpointer data) {
    changePassword();
}
static void on_resetPassword_clicked(GtkWidget *widget, gpointer data) {
    resetPassword();
}
static void on_backupData_clicked(GtkWidget *widget, gpointer data) {
    backupData();
}
static void on_restoreData_clicked(GtkWidget *widget, gpointer data) {
    restoreData();
}

// end widgets/system_setting.c