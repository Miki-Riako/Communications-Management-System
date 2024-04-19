// widgets/system_setting.c
#include "../header.h"

void systemSettingWidget();
bool changeUserPassword(const char *username, const char *newEncryptedPassword);
void changePassword();
void resetPassword();
void backupData();
void restoreData();

void systemSettingWidget() {
    while (true) {
        printf("\n系统设置\n");
        printf("1. 密码维护\n");
        printf("2. 重置业务员密码\n");
        printf("3. 数据备份\n");
        printf("4. 数据恢复\n");
        printf("5. 返回\n");
        printf("请选择一个操作（1-5）：");
        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);
        if (!isOneChar(get)) {
            printf("无效的选择，请重新输入。\n");
            continue;
        }
        switch(get[0]) {
        case '1':
            changePassword();
            break;
        case '2':
            resetPassword();
            break;
        case '3':
            backupData();
            break;
        case '4':
            restoreData();
            break;
        case '5':
            return;
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
    }
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
        printf("您是经理，无法改变自己的密钥。\n");
        printf("要查看公司密钥吗？这是一个敏感操作。\n");
        printf("输入 'yes' 确认查看，其他任意键取消：");

        char confirmation[10];
        getInput(confirmation, sizeof(confirmation));

        if (strcmp(confirmation, "yes") == 0) {
            printf("公司密钥是：%s\n", SECRET_KEY);
        } else {
            printf("操作已取消。\n");
        }
    } else {
        char oldPassword[MAX_LENGTH], newPassword[MAX_LENGTH], confirmPassword[MAX_LENGTH];
        char encryptedOldPassword[MAX_LENGTH * 2], encryptedNewPassword[MAX_LENGTH * 2];

        infoInput(oldPassword, sizeof(oldPassword), "请输入当前密码：");
        xorEncryptDecrypt(oldPassword, strlen(oldPassword), encryptedOldPassword);

        if (!verify(User, encryptedOldPassword)) {
            printf("密码错误。无法更改密码。\n");
            return;
        }

        infoInput(newPassword, sizeof(newPassword), "请输入新密码：");
        if (!matchRegex(newPassword)) {
            printf("密码不符合要求。必须至少8个字符且包含大写字母、小写字母、数字、标点符号中的两种。\n");
            return;
        }

        infoInput(confirmPassword, sizeof(confirmPassword), "请再次输入新密码以确认：");
        if (!isSameString(newPassword, confirmPassword)) {
            printf("两次输入的密码不匹配。\n");
            return;
        }

        xorEncryptDecrypt(newPassword, strlen(newPassword), encryptedNewPassword);
        if (changeUserPassword(User, encryptedNewPassword)) {
            printf("密码更新成功。\n");
        } else {
            printf("密码更新失败。\n");
        }
    }
}

void resetPassword() {
    if (!IsManager) {
        printf("您没有权限执行此操作。\n");
        return;
    }
    char employeeName[MAX_LENGTH];
    char newPassword[MAX_LENGTH];
    char encryptedNewPassword[MAX_LENGTH * 2];

    infoInput(employeeName, sizeof(employeeName), "请输入要重置密码的业务员用户名：");

    // 检查该用户是否存在
    if (!alreadyExists("user.csv", employeeName)) {
        printf("没有找到用户：%s\n", employeeName);
        return;
    }

    printf("请输入新密码为用户 '%s' 设置：", employeeName);
    getInput(newPassword, sizeof(newPassword));

    if (!matchRegex(newPassword)) {
        printf("密码不符合安全要求。\n");
        return;
    }

    xorEncryptDecrypt(newPassword, strlen(newPassword), encryptedNewPassword);

    // 更新密码
    if (changeUserPassword(employeeName, encryptedNewPassword)) {
        printf("密码重置成功。\n");
    } else {
        printf("密码重置失败。\n");
    }
}

void backupData() {
    if (!IsManager) {
        printf("您没有权限执行此操作。\n");
        return;
    }

    printf("请选择备份类型：\n");
    printf("1. 基本信息备份\n");
    printf("2. 分组信息备份\n");
    printf("请输入选择（1-2）：");

    char choice[MAX_LENGTH];
    getInput(choice, sizeof(choice));

    char basePath[10] = "";
    if (isOneChar(choice) && choice[0] == '2') {
        strcpy(basePath, "groups/");
    }

    char filename[MAX_LENGTH];
    char fullPath[2 *MAX_LENGTH ];
    char backupFilename[2 * MAX_LENGTH];  // 留足够空间用于添加前缀

    printf("请输入要备份的文件名：");
    getInput(filename, sizeof(filename));

    // 构建完整的原文件路径和备份文件路径
    snprintf(fullPath, sizeof(fullPath), "%s%s", basePath, filename);
    snprintf(backupFilename, sizeof(backupFilename), "%sbackup_%s", basePath, filename);

    // 执行文件复制操作
    if (!copyFile(fullPath, backupFilename)) {
        printf("备份失败，请检查文件名和路径是否正确。\n");
    } else {
        printf("备份成功。备份文件名为：%s\n", backupFilename);
    }
}

void restoreData() {
    if (!IsManager) {
        printf("您没有权限执行此操作。\n");
        return;
    }

    printf("请选择恢复类型：\n");
    printf("1. 基本信息恢复\n");
    printf("2. 分组信息恢复\n");
    printf("请输入选择（1-2）：");

    char choice[MAX_LENGTH];
    getInput(choice, sizeof(choice));

    char basePath[10] = "";
    if (isOneChar(choice) && choice[0] == '2') {
        strcpy(basePath, "groups/");
    }

    char backupFilename[MAX_LENGTH];
    char originalFilename[2 * MAX_LENGTH];  // 留足够空间处理文件名和路径

    printf("请输入要恢复的备份文件名（包含前缀）：");
    getInput(backupFilename, sizeof(backupFilename));

    // 构建原始文件路径
    snprintf(originalFilename, sizeof(originalFilename), "%s%s", basePath, backupFilename + 7); // 假设前缀 "backup_" 占用7个字符

    // 检查备份文件是否存在
    char fullBackupPath[2 * MAX_LENGTH];
    snprintf(fullBackupPath, sizeof(fullBackupPath), "%s%s", basePath, backupFilename);
    if (ACCESS(fullBackupPath, F_OK) == -1) {
        printf("备份文件 '%s' 不存在。\n", backupFilename);
        return;
    }

    // 执行文件复制操作以恢复数据
    if (!copyFile(fullBackupPath, originalFilename)) {
        printf("恢复失败，请检查备份文件名和路径是否正确。\n");
    } else {
        printf("恢复成功。文件 '%s' 已被恢复。\n", originalFilename);
    }
}

// end widgets/system_setting.c