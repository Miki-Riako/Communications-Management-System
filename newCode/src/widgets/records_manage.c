// widgets/record_manage.c
#include "../header.h"


void recordsManageWidget(GtkWidget *parent) {
    initializeInfoFile("records.csv", "User|||CompanyName|||ContactName|||Date|||Time|||Duration|||Content");
    recordsManageWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(recordsManageWidgets.window), "通信管理系统 - 通信记录管理系统");
    gtk_window_set_default_size(GTK_WINDOW(recordsManageWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(recordsManageWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(recordsManageWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间

    recordsManageWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(recordsManageWidgets.window), recordsManageWidgets.grid);
    gtk_widget_set_halign(recordsManageWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(recordsManageWidgets.grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(recordsManageWidgets.grid), 10);  // 设置行间距
    gtk_grid_set_column_spacing(GTK_GRID(recordsManageWidgets.grid), 10);  // 设置列间距


    recordsManageWidgets.addRecord_btn = gtk_button_new_with_label("增加通信记录");
    g_signal_connect(recordsManageWidgets.addRecord_btn, "clicked", G_CALLBACK(on_addRecord_clicked), NULL);
    gtk_grid_attach(GTK_GRID(recordsManageWidgets.grid), recordsManageWidgets.addRecord_btn, 0, 0, 2, 1);

    recordsManageWidgets.changeRecord_btn = gtk_button_new_with_label("修改通信记录");
    g_signal_connect(recordsManageWidgets.changeRecord_btn, "clicked", G_CALLBACK(on_changeRecord_clicked), NULL);
    gtk_grid_attach(GTK_GRID(recordsManageWidgets.grid), recordsManageWidgets.changeRecord_btn, 0, 1, 2, 1);

    recordsManageWidgets.showRecord_btn = gtk_button_new_with_label("显示通信记录");
    g_signal_connect(recordsManageWidgets.showRecord_btn, "clicked", G_CALLBACK(on_showRecord_clicked), NULL);
    gtk_grid_attach(GTK_GRID(recordsManageWidgets.grid), recordsManageWidgets.showRecord_btn, 0, 2, 2, 1);

    WidgetPair *widgetPair = g_slice_new(WidgetPair);
    widgetPair->parentWindow = parent;
    widgetPair->currentWindow = recordsManageWidgets.window;
    recordsManageWidgets.back_btn = gtk_button_new_with_label("返回");
    g_signal_connect(recordsManageWidgets.back_btn, "clicked", G_CALLBACK(on_back_clicked), widgetPair);
    gtk_grid_attach(GTK_GRID(recordsManageWidgets.grid), recordsManageWidgets.back_btn, 0, 3, 2, 1);
    
    gtk_widget_show_all(recordsManageWidgets.window);
    gtk_main();
}

void addRecord() {
    Record record;
    strcpy(record.user, User);

    inputTheName(record.companyName, sizeof(record.companyName), "请输入客户公司名称：");
    inputTheName(record.contactName, sizeof(record.contactName), "请输入客户联络员名称：");

    while (true) {
        if(infoInput(record.date, sizeof(record.date), "请输入日期 (YYYY-MM-DD)：")) {
            if (isSameString(record.date, " ") || matchDate(record.date)) {
                break;
            } else {
                show_info_dialog(NULL,"无效的日期格式，请重新输入。");
            }
        } else {
            return;
        }
        
    }
    while (true) {
        if(infoInput(record.time, sizeof(record.time), "请输入时间 (HH:MM:SS)：")) {
            if (isSameString(record.time, " ") || matchTime(record.time)) {
                break;
            } else {
                show_info_dialog(NULL,"无效的时间格式，请重新输入。");
            }
        } else {
            return;
        }
        
    }
    while (true) {
        if(infoInput(record.duration, sizeof(record.duration), "请输入通信时长（分钟）：")) {
            if (isSameString(record.duration, " ") || matchDuration(record.duration)) {
                break;
            } else {
                show_info_dialog(NULL,"无效的通信时长，请重新输入。");
            }
        } else {
            return;
        }
        
    }
    if(!infoInput(record.content, sizeof(record.content), "请输入通信内容："))
        return;

    // 构建完整的记录字符串
    char fullLine[MAX_LENGTH * 7 + 18];
    strcpy(fullLine, User);
    addColumn(fullLine, record.companyName);
    addColumn(fullLine, record.contactName);
    addColumn(fullLine, record.date);
    addColumn(fullLine, record.time);
    addColumn(fullLine, record.duration);
    addColumn(fullLine, record.content);

    // 写入文件
    writeLineToFile("records.csv", fullLine);
    displayRecord(record);
    show_info_dialog(NULL,"通信记录已成功添加。");
}

void changeRecord() {
    char companyName[MAX_LENGTH], contactName[MAX_LENGTH];
    char newCompanyName[MAX_LENGTH], newContactName[MAX_LENGTH], newDate[MAX_LENGTH], newTime[MAX_LENGTH], newDuration[MAX_LENGTH], newContent[MAX_LENGTH];
    char line[MAX_LENGTH * 8];
    char originalLine[MAX_LENGTH * 8]; // 保存原始行
    bool found = false;

    inputTheName(companyName, sizeof(companyName), "请输入要修改的客户公司名称：");
    inputTheName(contactName, sizeof(contactName), "请输入要修改的客户联络员名称：");

    FILE *file = fopen("records.csv", "r");
    FILE *tempFile = fopen("records_backup.csv", "w");
    if (!file || !tempFile) {
        show_info_dialog(NULL,"文件打开失败");
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        strcpy(originalLine, line); // 保存原始行
        char *fields[7], *token;
        int i = 0;
        token = strtok(line, "|||");
        while (token != NULL && i < 7) {
            fields[i++] = token;
            token = strtok(NULL, "|||");
        }
        if (i == 7 && strcmp(fields[0], User) == 0 && strcmp(fields[1], companyName) == 0 && strcmp(fields[2], contactName) == 0) {
            found = true;
            show_info_dialog(NULL,"找到记录，输入新的值");
            inputTheName(newCompanyName, sizeof(newCompanyName), "请输入新的客户公司名称：");
            inputTheName(newContactName, sizeof(newContactName), "请输入新的客户联络员名称：");
            while (true) {
                if(!infoInput(newDate, sizeof(newDate), "请输入新的日期 (YYYY-MM-DD)："))return;
                if (isSameString(newDate, " ") || matchDate(newDate)) {
                    break;
                } else {
                    show_info_dialog(NULL,"无效的日期格式，请重新输入。");
                }
            }
            while (true) {
                if(!infoInput(newTime, sizeof(newTime), "请输入新的时间 (HH:MM:SS)："))return;
                if (isSameString(newTime, " ") || matchTime(newTime)) {
                    break;
                } else {
                    show_info_dialog(NULL,"无效的时间格式，请重新输入。");
                }
            }
            while (true) {
                if(!infoInput(newDuration, sizeof(newDuration), "请输入新的通信时长（分钟）："))return;
                if (isSameString(newDuration, " ") || matchDuration(newDuration)) {
                    break;
                } else {
                    show_info_dialog(NULL,"无效的通信时长，请重新输入。");
                }
            }
            if(!infoInput(newContent, sizeof(newDuration), "请输入新的通信内容："))return;

            snprintf(originalLine, sizeof(originalLine), "%s|||%s|||%s|||%s|||%s|||%s|||%s\n", User, newCompanyName, newContactName, newDate, newTime, newDuration, newContent);
        }
        fputs(originalLine, tempFile); // 总是写回临时文件
    }
    fclose(file);
    fclose(tempFile);

    // 替换原文件
    remove("records.csv");
    rename("records_backup.csv", "records.csv");

    if (!found) {
        show_info_dialog(NULL,"没有找到相应的记录。");
    } else {
        show_info_dialog(NULL,"记录已成功更新。");
    }
}

void showRecord() {
    GtkWidget *dialog, *content_area, *scrolled_window, *text_view;
    GtkTextBuffer *buffer;
    FILE *file;
    char line[MAX_LENGTH]; 
    // 使用 GString 来动态构建字符串，并利用 g_strdup_printf 为了更安全地格式化字符串。
    GString *info = g_string_new("");  // 初始化一个空的GString
    // 添加当前用户信息
    g_string_append_printf(info, "当前用户 %s 的通信记录如下：\n", User);
    g_string_append(info, "公司客户名 - 联络员 - 日期 - 时间 - 时长 - 内容\n");

    // 打开文件
    file = fopen("records.csv", "r");
    if (!file) {
        perror("无法打开记录文件");
        g_string_free(info, TRUE);
        return;
    }

    // 读取文件内容并添加到文本缓冲区
    while (fgets(line, sizeof(line), file)) {
        char *currentUser = strtok(line, "|||");
        if (currentUser != NULL && strcmp(currentUser, User) == 0) {
            char *field1 = strtok(NULL, "|||");
            char *field2 = strtok(NULL, "|||");
            char *field3 = strtok(NULL, "|||");
            char *field4 = strtok(NULL, "|||");
            char *field5 = strtok(NULL, "|||");
            char *field6 = strtok(NULL, "|||");

            // 检查每个字段是否为NULL，避免使用NULL指针
            if (field1 && field2 && field3 && field4 && field5 && field6) {
                g_string_append_printf(info, "%s - %s - %s - %s - %s - %s\n",
                                    field1, field2, field3, field4, field5, field6);
            } else {
                // 可以记录错误或处理字段缺失的情况
                fprintf(stderr, "Error: Not enough fields in line for user %s\n", currentUser);
            }
        }
    }
    fclose(file);

    // 创建对话框
    dialog = gtk_dialog_new_with_buttons("通信记录详情",
                                         NULL,  // 没有父窗口
                                         GTK_DIALOG_MODAL,
                                         "_OK", GTK_RESPONSE_OK,
                                         NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    
    // 创建滚动窗口和文本视图
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scrolled_window, 600, 400);  // 设置滚动窗口的大小
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);  // 设置为不可编辑
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);  // 设置自动换行
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    
    gtk_text_buffer_set_text(buffer, info->str, -1);

    // 组装和显示
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    gtk_container_add(GTK_CONTAINER(content_area), scrolled_window);
    gtk_widget_show_all(dialog);

    // 运行对话框
    gtk_dialog_run(GTK_DIALOG(dialog));

    // 清理
    gtk_widget_destroy(dialog);
    g_string_free(info, TRUE);  // 清理 GString 对象
}

void displayRecord(Record record) {
    GtkWidget *dialog;
    GString *info = g_string_new("");

    // 使用 GString 安全地构建字符串
    g_string_append_printf(info, "客户公司名称: %s\n联络员名称: %s\n日期: %s\n时间: %s\n通信时长: %s\n通信内容: %s",
                           record.companyName, record.contactName, record.date, record.time, record.duration, record.content);

    // 创建一个消息对话框
    dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "%s", info->str);  // 使用 GString 的 str 成员
    gtk_window_set_title(GTK_WINDOW(dialog), "通信记录详情");

    // 显示对话框，等待用户响应
    gtk_dialog_run(GTK_DIALOG(dialog));

    // 清理和销毁
    gtk_widget_destroy(dialog);
    g_string_free(info, TRUE);  // 释放 GString 对象
}

void on_addRecord_clicked(GtkWidget *widget, gpointer data) {
    addRecord();
}
void on_changeRecord_clicked(GtkWidget *widget, gpointer data) {
    changeRecord();
}
void on_showRecord_clicked(GtkWidget *widget, gpointer data) {
    showRecord();
}

// end widgets/record_manage.c