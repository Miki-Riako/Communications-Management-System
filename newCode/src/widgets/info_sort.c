// widgets/info_sort.c
#include "../header.h"

void infoSortWidget(GtkWidget *parent) {
    initializeAll();
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoSortWidgets.window),
                                                GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "正在加载中，请您耐心等待。");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    head_node *head = (head_node *)malloc(sizeof(head_node));  // 分配内存
    if (!head) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoSortWidgets.window),
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_OK,
                                                    "内存分配失败！");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    loadFile(head);  // 加载数据
    if (head->is_empty) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoSortWidgets.window),
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_OK,
                                                    "没有加载到任何数据。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoSortWidgets.window),
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "数据加载成功！");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    infoSortWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(infoSortWidgets.window), "通信管理系统 - 信息排序显示系统");
    gtk_window_set_default_size(GTK_WINDOW(infoSortWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(infoSortWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(infoSortWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(infoSortWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    infoSortWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(infoSortWidgets.window), infoSortWidgets.grid);
    gtk_widget_set_halign(infoSortWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(infoSortWidgets.grid, GTK_ALIGN_CENTER);

    infoSortWidgets.defaultSort_btn = gtk_button_new_with_label("默认排序");
    g_signal_connect(infoSortWidgets.defaultSort_btn, "clicked", G_CALLBACK(on_defaultSort_clicked), head);
    gtk_grid_attach(GTK_GRID(infoSortWidgets.grid), infoSortWidgets.defaultSort_btn, 0, 0, 2, 1);

    infoSortWidgets.simpleSort_btn = gtk_button_new_with_label("单一属性排序");
    g_signal_connect(infoSortWidgets.simpleSort_btn, "clicked", G_CALLBACK(on_simpleSort_clicked), head);
    gtk_grid_attach(GTK_GRID(infoSortWidgets.grid), infoSortWidgets.simpleSort_btn, 0, 1, 2, 1);

    infoSortWidgets.combinedSort_btn = gtk_button_new_with_label("多属性排序");
    g_signal_connect(infoSortWidgets.combinedSort_btn, "clicked", G_CALLBACK(on_combinedSort_clicked), head);
    gtk_grid_attach(GTK_GRID(infoSortWidgets.grid), infoSortWidgets.combinedSort_btn, 0, 2, 2, 1);

    infoSortWidgets.back_btn = gtk_button_new_with_label("返回");
    WidgetPair *widgetPair = g_slice_new(WidgetPair);
    widgetPair->parentWindow = parent;
    widgetPair->currentWindow = infoSortWidgets.window;

    g_signal_connect(infoSortWidgets.back_btn, "clicked", G_CALLBACK(show_info_dialog), "正在返回，请稍等。");
    g_signal_connect(infoSortWidgets.back_btn, "clicked", G_CALLBACK(freeAll), head);
    g_signal_connect(infoSortWidgets.back_btn, "clicked", G_CALLBACK(on_infoSortBack_clicked), widgetPair);

    gtk_grid_attach(GTK_GRID(infoSortWidgets.grid), infoSortWidgets.back_btn, 0, 3, 2, 1);
    
    gtk_widget_show_all(infoSortWidgets.window);
    gtk_main();
}

void defaultSort(head_node *head) {
    GtkWidget *window, *scrolled_window, *text_view;
    GtkTextBuffer *buffer;
    const char *heading;
    if (head == NULL || head->is_empty) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "没有可排序的数据。");
        gtk_window_set_title(GTK_WINDOW(dialog), "排序失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    int which = beforeInfo(head, "排序");
    if (which == -1) return;  // 选择无效

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "排序结果");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    switch (which) {
    case 0:
        heading = "客户信息列表：\n";
        break;
    case 1:
        heading = "联络人信息列表：\n";
        break;
    case 2:
        heading = "业务员信息列表：\n";
        break;
    }
    gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
    printNodeList(buffer,head, which);

    gtk_widget_show_all(window);
    gtk_main();
}

void simpleSort(head_node *head) {
    GtkWidget *window, *scrolled_window, *text_view;
    GtkTextBuffer *buffer;
    const char *heading;
    if (head == NULL || head->is_empty) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "没有可排序的数据。");
        gtk_window_set_title(GTK_WINDOW(dialog), "排序失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    int which = beforeInfo(head, "排序");
    if (which == -1) return;  // 如果选择无效或不允许展示，则返回

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "排序结果");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));


    switch (which) {
    case 0:
        heading = "客户信息列表：\n";
        break;
    case 1:
        heading = "联络人信息列表：\n";
        break;
    case 2:
        heading = "业务员信息列表：\n";
        break;
    }
    gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
    int attributeIndex = 0;
    bool isAscending = false;

    beforeSort(head, which, &attributeIndex, &isAscending);
    
    sort(which, head, attributeIndex, isAscending);
    printNodeList(buffer,head, which);

    gtk_widget_show_all(window);
}

void combinedSort(head_node *head) {
    GtkWidget *window, *scrolled_window, *text_view;
    GtkTextBuffer *buffer;
    const char *heading;
    if (head == NULL || head->is_empty) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "没有可排序的数据。");
        gtk_window_set_title(GTK_WINDOW(dialog), "排序失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                GTK_MESSAGE_INFO,
                                GTK_BUTTONS_OK,
                                "开始进行组合排序。");
    gtk_window_set_title(GTK_WINDOW(dialog), "开始排序");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    int which = beforeInfo(head, "排序");
    if (which == -1) return;  // 如果选择无效或不允许展示，则返回

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "排序结果");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    switch (which) {
    case 0:
        heading = "客户信息列表：\n";
        break;
    case 1:
        heading = "联络人信息列表：\n";
        break;
    case 2:
        heading = "业务员信息列表：\n";
        break;
    }
    combinedSortHelper(head, which);
    printNodeList(buffer,head, which);
}

void on_defaultSort_clicked(GtkWidget *widget, gpointer data) {
    defaultSort(data);
}
void on_simpleSort_clicked(GtkWidget *widget, gpointer data) {
    simpleSort(data);
}
void on_combinedSort_clicked(GtkWidget *widget, gpointer data) {
    combinedSort(data);
}
static void on_infoSortBack_clicked(GtkWidget *widget, gpointer data) {
    on_back_clicked(widget,data);
    show_info_dialog(NULL,"返回成功！");
}

// end widgets/info_sort.c