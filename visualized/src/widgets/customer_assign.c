// widgets/customer_assign.c
#include "../header.h"

// Main widget for customer assignment management
void customerAssignWidget(GtkWidget *parent) {
    initializeInfoFile("assignments.csv", "Employee|||Customer");
    
    customerAssignWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(customerAssignWidgets.window), "通信管理系统 - 经理菜单 - 客户分配管理");
    gtk_window_set_default_size(GTK_WINDOW(customerAssignWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(customerAssignWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(customerAssignWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间

    customerAssignWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(customerAssignWidgets.window), customerAssignWidgets.grid);
    gtk_widget_set_halign(customerAssignWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(customerAssignWidgets.grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(customerAssignWidgets.grid), 10);  // 设置行间距
    gtk_grid_set_column_spacing(GTK_GRID(customerAssignWidgets.grid), 10);  // 设置列间距


    customerAssignWidgets.addAssignment_btn = gtk_button_new_with_label("分配客户");
    g_signal_connect(customerAssignWidgets.addAssignment_btn, "clicked", G_CALLBACK(on_addAssignment_clicked), NULL);
    gtk_grid_attach(GTK_GRID(customerAssignWidgets.grid), customerAssignWidgets.addAssignment_btn, 0, 0, 2, 1);

    customerAssignWidgets.changeAssignment_btn = gtk_button_new_with_label("修改客户分配");
    g_signal_connect(customerAssignWidgets.changeAssignment_btn, "clicked", G_CALLBACK(on_changeAssignment_clicked), NULL);
    gtk_grid_attach(GTK_GRID(customerAssignWidgets.grid), customerAssignWidgets.changeAssignment_btn, 0, 1, 2, 1);

    customerAssignWidgets.removeAssignment_btn = gtk_button_new_with_label("删除客户分配");
    g_signal_connect(customerAssignWidgets.removeAssignment_btn, "clicked", G_CALLBACK(on_removeAssignment_clicked), NULL);
    gtk_grid_attach(GTK_GRID(customerAssignWidgets.grid), customerAssignWidgets.removeAssignment_btn, 0, 2, 2, 1);

    customerAssignWidgets.displayAssignment_btn = gtk_button_new_with_label("查看分配的客户");
    g_signal_connect(customerAssignWidgets.displayAssignment_btn, "clicked", G_CALLBACK(on_displayAssignment_clicked), NULL);
    gtk_grid_attach(GTK_GRID(customerAssignWidgets.grid), customerAssignWidgets.displayAssignment_btn, 0, 3, 2, 1);

    WidgetPair *widgetPair = g_slice_new(WidgetPair);
    widgetPair->parentWindow = parent;
    widgetPair->currentWindow = customerAssignWidgets.window;
    customerAssignWidgets.backToManagerMenu_btn = gtk_button_new_with_label("返回");
    g_signal_connect(customerAssignWidgets.backToManagerMenu_btn, "clicked", G_CALLBACK(on_back_clicked), widgetPair);
    gtk_grid_attach(GTK_GRID(customerAssignWidgets.grid), customerAssignWidgets.backToManagerMenu_btn, 0, 4, 2, 1);
    
    gtk_widget_show_all(customerAssignWidgets.window);
    gtk_main();
}

void addAssignment() {
    char employeeName[MAX_LENGTH], customerName[MAX_LENGTH];
    char fullLine[MAX_LENGTH * 2 + 4];

    inputTheName(employeeName, sizeof(employeeName), "请输入业务员的名称：");
    if(isSameString(employeeName," ")) {
        printf("取消分配\n");
        return;
    }
    inputTheName(customerName, sizeof(customerName), "请输入客户的名称：");
    if(isSameString(customerName," ")) {
        printf("取消分配\n");
        return;
    }
    strcpy(fullLine, employeeName);
    addColumn(fullLine, customerName);

    // 检查是否已经存在这个分配
    if (lineExists("assignments.csv", fullLine)) {
        char message[MAX_LENGTH*3];
        snprintf(message, sizeof(message), "这个分配已经存在：%s -> %s\n", employeeName, customerName);

        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "%s",message);
        gtk_window_set_title(GTK_WINDOW(dialog), "分配失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        writeLineToFile("assignments.csv", fullLine);
        char message[MAX_LENGTH*3];
        snprintf(message, sizeof(message), "客户分配成功：%s -> %s\n", employeeName, customerName);
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "%s",message);
        gtk_window_set_title(GTK_WINDOW(dialog), "分配成功");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void changeAssignment() {
    char oldEmployeeName[MAX_LENGTH], oldCustomerName[MAX_LENGTH];
    char newEmployeeName[MAX_LENGTH], newCustomerName[MAX_LENGTH];
    char oldLine[MAX_LENGTH * 2 + 4];
    char newLine[MAX_LENGTH * 2 + 4];

    // 获取原始业务员和客户的名称
    inputTheName(oldEmployeeName, sizeof(oldEmployeeName), "请输入原始业务员的名称：");
    inputTheName(oldCustomerName, sizeof(oldCustomerName), "请输入原始客户的名称：");

    strcpy(oldLine, oldEmployeeName);
    addColumn(oldLine, oldCustomerName);

    // 检查原始组合是否存在
    if (!lineExists("assignments.csv", oldLine)) {
        char message[MAX_LENGTH*3];
        snprintf(message, sizeof(message), "分配不存在：%s -> %s\n", oldEmployeeName, oldCustomerName);

        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "%s",message);
        gtk_window_set_title(GTK_WINDOW(dialog), "修改分配失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // 获取新业务员和客户的名称
    inputTheName(newEmployeeName, sizeof(newEmployeeName), "请输入新的业务员的名称：");
    inputTheName(newCustomerName, sizeof(newCustomerName), "请输入新的客户的名称：");

    strcpy(newLine, newEmployeeName);
    addColumn(newLine, newCustomerName);

    // 删除原始组合
    if (removeLineInFile("assignments.csv", oldLine)) {
        // 添加新组合
        writeLineToFile("assignments.csv", newLine);
        char message[MAX_LENGTH*3];
        snprintf(message, sizeof(message), "成功更新分配：%s -> %s\n", newEmployeeName, newCustomerName);

        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "%s",message);
        gtk_window_set_title(GTK_WINDOW(dialog), "修改分配成功");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "更新分配失败。");
        gtk_window_set_title(GTK_WINDOW(dialog), "修改分配失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
}

void removeAssignment() {
    char employeeName[MAX_LENGTH], customerName[MAX_LENGTH];
    char fullLine[MAX_LENGTH * 2 + 4];

    inputTheName(employeeName, sizeof(employeeName), "请输入业务员的名称：");
    inputTheName(customerName, sizeof(customerName), "请输入客户的名称：");

    strcpy(fullLine, employeeName);
    addColumn(fullLine, customerName);

    if (!lineExists("assignments.csv", fullLine)) {
        char message[MAX_LENGTH*3];
        snprintf(message, sizeof(message), "未找到该分配：%s -> %s\n", employeeName, customerName);

        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "%s",message);
        gtk_window_set_title(GTK_WINDOW(dialog), "删除分配失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        // 删除分配
        if (removeLineInFile("assignments.csv", fullLine)) {
            char message[MAX_LENGTH*3];
            snprintf(message, sizeof(message), "客户分配删除成功：%s -> %s\n", employeeName, customerName);

            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK,
                                        "%s",message);
            gtk_window_set_title(GTK_WINDOW(dialog), "删除分配成功");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);

        } else {
            GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "客户分配删除失败。");
            gtk_window_set_title(GTK_WINDOW(dialog), "删除分配失败");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    }
}

void displayAssignment() {
    GtkWidget *window, *scrolled_window, *text_view;
    GtkTextBuffer *buffer;
    char line[MAX_LENGTH];
    FILE *file = fopen("assignments.csv", "r");
    
    if (!file) {
        perror("打开文件失败");
        return;
    }

    // 创建窗口
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "业务员和客户配对");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);

    // 创建滚动窗口
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    // 创建文本视图和文本缓冲区
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE);
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    // 读取文件并添加到文本视图
    while (fgets(line, sizeof(line), file)) {
        char *delimiter = strstr(line, "|||");
        if (delimiter != NULL) {
            *delimiter = '\0';
            GtkTextIter end;
            gtk_text_buffer_get_end_iter(buffer, &end);
            gtk_text_buffer_insert(buffer, &end, line, -1);
            gtk_text_buffer_insert(buffer, &end, " -> ", -1);
            gtk_text_buffer_insert(buffer, &end, delimiter + 3, -1);
            gtk_text_buffer_insert(buffer, &end, "\n", -1);
        } else {
            GtkTextIter end;
            gtk_text_buffer_get_end_iter(buffer, &end);
            gtk_text_buffer_insert(buffer, &end, "格式错误： ", -1);
            gtk_text_buffer_insert(buffer, &end, line, -1);
            gtk_text_buffer_insert(buffer, &end, "\n", -1);
        }
    }

    fclose(file);

    // 显示所有窗口和控件
    gtk_widget_show_all(window);
    gtk_main();
}

static void on_addAssignment_clicked(GtkWidget *widget, gpointer data) {
    addAssignment();
}
static void on_changeAssignment_clicked(GtkWidget *widget, gpointer data) {
    changeAssignment();
}
static void on_removeAssignment_clicked(GtkWidget *widget, gpointer data) {
    removeAssignment();
}
static void on_displayAssignment_clicked(GtkWidget *widget, gpointer data) {
    displayAssignment();
}

// end widgets/customer_assign.c