// widgets/group_manage.c
#include "../header.h"

void groupManageWidget(GtkWidget *parent) {
    createDirectory("groups");

    groupManageWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(groupManageWidgets.window), "通信管理系统 - 经理菜单 - 分组管理");
    gtk_window_set_default_size(GTK_WINDOW(groupManageWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(groupManageWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(groupManageWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(groupManageWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    groupManageWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(groupManageWidgets.window), groupManageWidgets.grid);
    gtk_widget_set_halign(groupManageWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(groupManageWidgets.grid, GTK_ALIGN_CENTER);

    groupManageWidgets.addGroup_btn = gtk_button_new_with_label("创建分组");
    g_signal_connect(groupManageWidgets.addGroup_btn, "clicked", G_CALLBACK(on_addGroup_clicked), NULL);
    gtk_grid_attach(GTK_GRID(groupManageWidgets.grid), groupManageWidgets.addGroup_btn, 0, 0, 2, 1);

    groupManageWidgets.changeGroup_btn = gtk_button_new_with_label("修改分组");
    g_signal_connect(groupManageWidgets.changeGroup_btn, "clicked", G_CALLBACK(on_changeGroup_clicked), NULL);
    gtk_grid_attach(GTK_GRID(groupManageWidgets.grid), groupManageWidgets.changeGroup_btn, 0, 1, 2, 1);

    groupManageWidgets.removeGroup_btn = gtk_button_new_with_label("删除分组");
    g_signal_connect(groupManageWidgets.removeGroup_btn, "clicked", G_CALLBACK(on_removeGroup_clicked), NULL);
    gtk_grid_attach(GTK_GRID(groupManageWidgets.grid), groupManageWidgets.removeGroup_btn, 0, 2, 2, 1);

    groupManageWidgets.showGroups_btn = gtk_button_new_with_label("查看所有分组");
    g_signal_connect(groupManageWidgets.showGroups_btn, "clicked", G_CALLBACK(on_showGroups_clicked), NULL);
    gtk_grid_attach(GTK_GRID(groupManageWidgets.grid), groupManageWidgets.showGroups_btn, 0, 3, 2, 1);

    groupManageWidgets.divideCustomer_btn = gtk_button_new_with_label("客户划分");
    g_signal_connect(groupManageWidgets.divideCustomer_btn, "clicked", G_CALLBACK(on_divideCustomer_clicked), NULL);
    gtk_grid_attach(GTK_GRID(groupManageWidgets.grid), groupManageWidgets.divideCustomer_btn, 0, 4, 2, 1);

    groupManageWidgets.adjustCustomer_btn = gtk_button_new_with_label("客户调整");
    g_signal_connect(groupManageWidgets.adjustCustomer_btn, "clicked", G_CALLBACK(on_adjustCustomer_clicked), NULL);
    gtk_grid_attach(GTK_GRID(groupManageWidgets.grid), groupManageWidgets.adjustCustomer_btn, 0, 5, 2, 1);

    WidgetPair *widgetPair = g_slice_new(WidgetPair);
    widgetPair->parentWindow = parent;
    widgetPair->currentWindow = groupManageWidgets.window;
    groupManageWidgets.backToManageMenu_btn = gtk_button_new_with_label("返回");
    g_signal_connect(groupManageWidgets.backToManageMenu_btn, "clicked", G_CALLBACK(on_back_clicked), widgetPair);
    gtk_grid_attach(GTK_GRID(groupManageWidgets.grid), groupManageWidgets.backToManageMenu_btn, 0, 6, 2, 1);
    
    gtk_widget_show_all(groupManageWidgets.window);
    gtk_main();
}

void createDirectory(const char *path) {
    CREATE_DIRECTORY(path);
}

void createGroup(const char *groupName) {
    char filename[MAX_LENGTH + 12];
    snprintf(filename, sizeof(filename), "groups/%s.csv", groupName);
    initializeInfoFile(filename, "Name|||Region|||Address|||LegalRepresentative|||Scale|||BusinessContactLevel|||Email|||Phone");
    char message[MAX_LENGTH*2];
    snprintf(message,sizeof(message),"自定义分组 '%s' 已创建。",groupName);
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                GTK_MESSAGE_INFO,
                                GTK_BUTTONS_OK,
                                "%s",message);
    gtk_window_set_title(GTK_WINDOW(dialog), "创建成功");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void addGroup() {
    char groupName[MAX_LENGTH];
    GtkWidget *dialog, *content_area, *combo_box;
    GtkWindow *parent_window = NULL;  // 如果有主窗口，此处应设置为相应的 GtkWindow 指针
    int response_id;

    if(!infoInput(groupName, sizeof(groupName),"请输入新分组的名称")) return;

    // 创建对话框
    dialog = gtk_dialog_new_with_buttons("选择分组类型",
                                         parent_window,
                                         GTK_DIALOG_MODAL,
                                         "_OK", GTK_RESPONSE_OK,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // 创建一个下拉菜单用于选择分组类型
    combo_box = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "按区域分组");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "按规模分组");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "按联系程度分组");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "自定义分组");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), 0);  // 设置默认选项
    gtk_box_pack_start(GTK_BOX(content_area), combo_box, FALSE, FALSE, 0);

    // 显示所有控件
    gtk_widget_show_all(dialog);

    // 运行对话框并等待用户响应
    response_id = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response_id == GTK_RESPONSE_OK) {
        int index = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box));
        switch (index) {
        case 0:
            regionGroup(groupName);
            break;
        case 1:
            scaleGroup(groupName);
            break;
        case 2:
            contactGroup(groupName);
            break;
        case 3:
            createGroup(groupName);
            break;
        }
    }
    gtk_widget_destroy(dialog);
}

void regionGroup(const char *groupName) {
    char inputRegion[MAX_LENGTH];
    if(!infoInput(inputRegion, sizeof(inputRegion),"请输入区域名")) return;

    char filename[MAX_LENGTH];
    snprintf(filename, sizeof(filename), "groups/%s.csv", groupName);
    createGroup(groupName);  // 创建空分组文件并初始化

    copyLine("customers.csv", filename, "Region", inputRegion);  // 复制符合条件的行
}

void scaleGroup(const char *groupName) {
    GtkWidget *dialog, *content_area;
    GtkComboBoxText *combo_box;
    char filename[MAX_LENGTH + 20];
    int response_id;

    // 创建带有下拉菜单的对话框
    dialog = gtk_dialog_new_with_buttons("选择客户规模",
                                         NULL,  // 无父窗口
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "_OK", GTK_RESPONSE_OK,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // 创建下拉菜单并添加选项
    combo_box = GTK_COMBO_BOX_TEXT(gtk_combo_box_text_new());
    gtk_combo_box_text_append_text(combo_box, "大");
    gtk_combo_box_text_append_text(combo_box, "中");
    gtk_combo_box_text_append_text(combo_box, "小");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), 0);  // 设置初始选项为“大”
    gtk_box_pack_start(GTK_BOX(content_area), GTK_WIDGET(combo_box), TRUE, TRUE, 0);

    gtk_widget_show_all(dialog);

    // 等待用户响应
    response_id = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response_id == GTK_RESPONSE_OK) {
        const char *scaleValue = gtk_combo_box_text_get_active_text(combo_box);

        snprintf(filename, sizeof(filename), "groups/%s.csv", groupName);
        createGroup(groupName);  // 创建分组文件

        // 模拟添加数据到分组文件的逻辑
        copyLine("customers.csv", filename, "Scale", scaleValue);

        // 显示成功消息
        char message[MAX_LENGTH * 3];
        snprintf(message, sizeof(message), "已将规模为 '%s' 的客户添加到分组 '%s'.", scaleValue, groupName);
        GtkWidget *info_dialog = gtk_message_dialog_new(NULL,
                                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                        GTK_MESSAGE_INFO,
                                                        GTK_BUTTONS_OK,
                                                        "%s", message);
        gtk_dialog_run(GTK_DIALOG(info_dialog));
        gtk_widget_destroy(info_dialog);
    }

    gtk_widget_destroy(dialog);
}

void contactGroup(const char *groupName) {
    GtkWidget *dialog, *content_area;
    GtkComboBoxText *combo_box;
    GtkTextBuffer *buffer;
    int response_id;
    char filename[MAX_LENGTH + 20];

    // 创建带有下拉菜单的对话框
    dialog = gtk_dialog_new_with_buttons("选择联系程度",
                                         NULL,  // 无父窗口
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "_OK", GTK_RESPONSE_OK,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    combo_box = GTK_COMBO_BOX_TEXT(gtk_combo_box_text_new());
    gtk_combo_box_text_append_text(combo_box, "高");
    gtk_combo_box_text_append_text(combo_box, "中");
    gtk_combo_box_text_append_text(combo_box, "低");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), 0);  // 设置初始选项为“高”
    gtk_box_pack_start(GTK_BOX(content_area), GTK_WIDGET(combo_box), TRUE, TRUE, 0);

    gtk_widget_show_all(dialog);

    // 等待用户响应
    response_id = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response_id == GTK_RESPONSE_OK) {
        const char *contactLevel = gtk_combo_box_text_get_active_text(combo_box);

        snprintf(filename, sizeof(filename), "groups/%s.csv", groupName);
        createGroup(groupName);  // 创建分组文件

        // 模拟添加数据到分组文件的逻辑
        copyLine("customers.csv", filename, "BusinessContactLevel", contactLevel);

        // 显示成功消息
        char message[MAX_LENGTH * 3];
        snprintf(message, sizeof(message), "已将联系程度为 '%s' 的客户添加到分组 '%s'.", contactLevel, groupName);
        GtkWidget *info_dialog = gtk_message_dialog_new(NULL,
                                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                        GTK_MESSAGE_INFO,
                                                        GTK_BUTTONS_OK,
                                                        "%s", message);
        gtk_dialog_run(GTK_DIALOG(info_dialog));
        gtk_widget_destroy(info_dialog);
    }

    gtk_widget_destroy(dialog);
}

void changeGroup() {
    char oldGroupName[MAX_LENGTH];
    char newGroupName[MAX_LENGTH];
    char oldFilename[MAX_LENGTH + 12];
    char newFilename[MAX_LENGTH + 12];

    if(!infoInput(oldGroupName, sizeof(oldGroupName),"请输入要修改的分组名称")) return;
    snprintf(oldFilename, sizeof(oldFilename), "groups/%s.csv", oldGroupName); // 构建原始文件名

    // 检查原始文件是否存在
    if (ACCESS(oldFilename, F_OK) != -1) {
        if(!infoInput(newGroupName, sizeof(newGroupName),"请输入新的分组名称")) return;
        snprintf(newFilename, sizeof(newFilename), "groups/%s.csv", newGroupName); // 构建新文件名

        // 重命名文件
        if (rename(oldFilename, newFilename) == 0) {
            char message[MAX_LENGTH*3];
            snprintf(message,sizeof(message),"分组 '%s' 已成功重命名为 '%s'",oldGroupName, newGroupName);
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "%s",message);
            gtk_window_set_title(GTK_WINDOW(dialog), "重命名成功");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        } else {
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "重命名文件失败");
            gtk_window_set_title(GTK_WINDOW(dialog), "重命名失败");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    } else {
        char message[MAX_LENGTH*2];
        snprintf(message,sizeof(message),"分组 '%s' 不存在",oldGroupName);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "%s",message);
        gtk_window_set_title(GTK_WINDOW(dialog), "原始文件不存在");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void removeGroup() {
    char groupName[MAX_LENGTH];
    char filename[MAX_LENGTH + 12];

    if(!infoInput(groupName, sizeof(groupName),"请输入要删除的分组名称")) return;
    snprintf(filename, sizeof(filename), "groups/%s.csv", groupName); // 构建完整的文件路径

    // 检查文件是否存在
    if (ACCESS(filename, F_OK) != -1) {
        // 文件存在，尝试删除
        if (remove(filename) == 0) {
            char message[MAX_LENGTH*2];
            snprintf(message,sizeof(message),"分组 '%s' 已成功删除",groupName);
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "%s",message);
            gtk_window_set_title(GTK_WINDOW(dialog), "删除成功");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        } else {
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "删除文件失败");
            gtk_window_set_title(GTK_WINDOW(dialog), "删除失败");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    } else {    // 文件不存在
        char message[MAX_LENGTH*2];
        snprintf(message,sizeof(message),"分组 '%s' 不存在",groupName);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "%s",message);
        gtk_window_set_title(GTK_WINDOW(dialog), "文件不存在");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void showGroups() {
    GtkWidget *window, *scrolled_window, *text_view;
    GtkTextBuffer *buffer;

    char groupName[MAX_LENGTH];
    char filename[MAX_LENGTH + 20];  // 留足空间以存放路径和文件名
    char line[MAX_LENGTH];
    char header[MAX_LENGTH + 50];

    if(!infoInput(groupName, sizeof(groupName),"请输入要查看的分组名称："))return;

    snprintf(filename, sizeof(filename), "groups/%s.csv", groupName);

    // 检查文件是否存在
    if (ACCESS(filename, F_OK) == -1) {
        char message[MAX_LENGTH*2];
        snprintf(message,sizeof(message),"分组 '%s' 不存在",groupName);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "%s",message);
        gtk_window_set_title(GTK_WINDOW(dialog), "文件不存在");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开文件失败");
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "打开文件失败");
        gtk_window_set_title(GTK_WINDOW(dialog), "显示失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // 创建窗口
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "查看分组信息");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 创建滚动窗口和文本视图
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    // 设置并插入头部信息
    snprintf(header, sizeof(header), "\n分组 '%s' 的成员如下：\n", groupName);
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(buffer, &iter);
    gtk_text_buffer_insert(buffer, &iter, header, -1);

    // 读取文件内容并显示
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;  // 去除可能的换行符

        // 分割行并格式化输出
        char *token = strtok(line, "|||");
        gtk_text_buffer_get_end_iter(buffer, &iter);

        while (token != NULL) {
            gtk_text_buffer_insert(buffer, &iter, token, -1);
            token = strtok(NULL, "|||");
            if (token != NULL) {
                gtk_text_buffer_insert(buffer, &iter, " - ", -1);
            }
        }
        gtk_text_buffer_insert(buffer, &iter, "\n", -1);
    }

    fclose(file);

    // 显示所有窗口和控件
    gtk_widget_show_all(window);
    gtk_main();
}

void divideCustomer() {
    char customerName[MAX_LENGTH];
    char groupName[MAX_LENGTH];
    char groupFilename[MAX_LENGTH + 12];

    if(!infoInput(customerName, sizeof(customerName), "请输入客户名以进行分组："))return;

    if (!alreadyExists("customers.csv", customerName)) {
        char message[MAX_LENGTH*2];
        snprintf(message,sizeof(message),"客户 '%s' 不存在!",groupName);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "%s",message);
        gtk_window_set_title(GTK_WINDOW(dialog), "客户不存在");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    if(!infoInput(groupName, sizeof(groupName), "请输入目标分组名称："))return;
    snprintf(groupFilename, sizeof(groupFilename), "groups/%s.csv", groupName);

    if (ACCESS(groupFilename, F_OK) == -1) {
        char message[MAX_LENGTH*2];
        snprintf(message,sizeof(message),"分组 '%s' 不存在",groupName);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "%s",message);
        gtk_window_set_title(GTK_WINDOW(dialog), "文件不存在");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // 复制符合条件的行到分组文件
    copyLine("customers.csv", groupFilename, "Name", customerName);
    char message[MAX_LENGTH*3];
    snprintf(message,sizeof(message),"已将名为 '%s' 的客户添加到分组 '%s'.",customerName, groupName);
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                GTK_MESSAGE_INFO,
                                GTK_BUTTONS_OK,
                                "%s",message);
    gtk_window_set_title(GTK_WINDOW(dialog), "添加成功");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void adjustCustomer() {
    char oldGroupName[MAX_LENGTH], newGroupName[MAX_LENGTH];
    char customerName[MAX_LENGTH];
    char oldGroupFilename[MAX_LENGTH + 12], newGroupFilename[MAX_LENGTH + 12];

    if(!infoInput(oldGroupName, sizeof(oldGroupName), "请输入原分组名称："))return;
    snprintf(oldGroupFilename, sizeof(oldGroupFilename), "groups/%s.csv", oldGroupName);
    if(!infoInput(customerName, sizeof(customerName), "请输入客户名称："))return;
    if (!alreadyExists(oldGroupFilename, customerName)) {
        char message[MAX_LENGTH*3];
        snprintf(message,sizeof(message),"客户 '%s' 不存在于原分组 '%s' 中。",customerName, oldGroupName);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "%s",message);
        gtk_window_set_title(GTK_WINDOW(dialog), "调整失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    if (ACCESS(oldGroupFilename, F_OK) == -1) {
        char message[MAX_LENGTH*2];
        snprintf(message,sizeof(message),"分组 '%s' 不存在该文件夹中。",oldGroupName);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "%s",message);
        gtk_window_set_title(GTK_WINDOW(dialog), "文件不存在");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    char action[MAX_LENGTH];
    if(!infoInput(action, sizeof(action),"请选择操作：1. 复制客户 2. 移动客户 3. 删除客户 请输入选择（1-3）："))return;

    if (!isOneChar(action)) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "无效的操作选择。");
        gtk_window_set_title(GTK_WINDOW(dialog), "调整失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    GtkWidget * dialog;
    switch (action[0]) {
    case '1':  // 复制客户
    case '2':  // 移动客户
        if(!infoInput(newGroupName, sizeof(newGroupName), "请输入目标分组名称："))return;
        snprintf(newGroupFilename, sizeof(newGroupFilename), "groups/%s.csv", newGroupName);
        if (ACCESS(newGroupFilename, F_OK) == -1) {
            char message[MAX_LENGTH*2];
            snprintf(message,sizeof(message),"目标分组 '%s' 不存在。",newGroupName);
            dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "%s",message);
            gtk_window_set_title(GTK_WINDOW(dialog), "目标分组不存在");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }
        copyLine(oldGroupFilename, newGroupFilename, "Name", customerName);
        if (action[0] == '2') {  // 如果是移动，还需要从原分组中删除
            if (removeEntry(oldGroupFilename, customerName)) {
                char message[MAX_LENGTH*2];
                snprintf(message,sizeof(message),"客户 '%s' 移动成功。",customerName);
                dialog = gtk_message_dialog_new(NULL,
                                            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_INFO,
                                            GTK_BUTTONS_OK,
                                            "%s",message);
                gtk_window_set_title(GTK_WINDOW(dialog), "移动成功");
                gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
            } else {
                char message[MAX_LENGTH*2];
                snprintf(message,sizeof(message),"移动客户 '%s' 失败。",customerName);
                dialog = gtk_message_dialog_new(NULL,
                                            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_ERROR,
                                            GTK_BUTTONS_OK,
                                            "%s",message);
                gtk_window_set_title(GTK_WINDOW(dialog), "移动失败");
                gtk_dialog_run(GTK_DIALOG(dialog));
                gtk_widget_destroy(dialog);
            }
        }
        break;
    case '3':  // 删除客户
        if (removeEntry(oldGroupFilename, customerName)) {
            char message[MAX_LENGTH*2];
            snprintf(message,sizeof(message),"客户 '%s' 删除成功。",customerName);
            dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "%s",message);
            gtk_window_set_title(GTK_WINDOW(dialog), "删除成功");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        } else {
            char message[MAX_LENGTH*2];
            snprintf(message,sizeof(message),"删除客户 '%s' 失败。",customerName);
            dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "%s",message);
            gtk_window_set_title(GTK_WINDOW(dialog), "删除失败");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
        break;
    default:
        dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "无效的操作选择。");
        gtk_window_set_title(GTK_WINDOW(dialog), "无效的操作选择。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    dialog = gtk_message_dialog_new(NULL,
                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                GTK_MESSAGE_INFO,
                                GTK_BUTTONS_OK,
                                "操作成功完成。");
    gtk_window_set_title(GTK_WINDOW(dialog), "操作成功完成。");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void on_addGroup_clicked(GtkWidget *widget, gpointer data) {
    addGroup();
}
static void on_changeGroup_clicked(GtkWidget *widget, gpointer data) {
    changeGroup();
}
static void on_removeGroup_clicked(GtkWidget *widget, gpointer data) {
    removeGroup();
}
static void on_showGroups_clicked(GtkWidget *widget, gpointer data) {
    showGroups();
}
static void on_divideCustomer_clicked(GtkWidget *widget, gpointer data) {
    divideCustomer();
}
static void on_adjustCustomer_clicked(GtkWidget *widget, gpointer data) {
    adjustCustomer();
}

// end widgets/group_manage.c