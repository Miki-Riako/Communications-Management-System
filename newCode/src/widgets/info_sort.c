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

    infoSortWidgets.recordSort_btn = gtk_button_new_with_label("通信记录排序");
    g_signal_connect(infoSortWidgets.recordSort_btn, "clicked", G_CALLBACK(on_recordSort_clicked), head);
    gtk_grid_attach(GTK_GRID(infoSortWidgets.grid), infoSortWidgets.recordSort_btn, 0, 3, 2, 1);

    infoSortWidgets.back_btn = gtk_button_new_with_label("返回");
    WidgetPair *widgetPair = g_slice_new(WidgetPair);
    widgetPair->parentWindow = parent;
    widgetPair->currentWindow = infoSortWidgets.window;

    g_signal_connect(infoSortWidgets.back_btn, "clicked", G_CALLBACK(show_info_dialog), "正在返回，请稍等。");
    g_signal_connect(infoSortWidgets.back_btn, "clicked", G_CALLBACK(freeAll), head);
    g_signal_connect(infoSortWidgets.back_btn, "clicked", G_CALLBACK(on_infoSortBack_clicked), widgetPair);

    gtk_grid_attach(GTK_GRID(infoSortWidgets.grid), infoSortWidgets.back_btn, 0, 4, 2, 1);
    
    gtk_widget_show_all(infoSortWidgets.window);
    gtk_main();
}

void defaultSort(head_node *head) {
    int which = beforeInfo(head, "展示");
    if (which == -1) return;  // 如果选择无效或不允许展示，则返回

    switch (which) {
    case 0:
        printf("客户信息列表：\n");
        break;
    case 1:
        printf("联络人信息列表：\n");
        break;
    case 2:
        printf("业务员信息列表：\n");
        break;
    }
    printNodeList(head, which);
}
    // case 3:
    //     printf("通信记录列表：\n");
    //     printf("管理用户 - 公司名称 - 联络人 - 日期 - 时间 - 时长 - 通信内容\n");
    //     break;




void on_defaultSort_clicked(GtkWidget *widget, gpointer data) {
    defaultSort(data);
}
void on_simpleSort_clicked(GtkWidget *widget, gpointer data) {

}
void on_combinedSort_clicked(GtkWidget *widget, gpointer data) {

}
void on_recordSort_clicked(GtkWidget *widget, gpointer data) {

}
static void on_infoSortBack_clicked(GtkWidget *widget, gpointer data) {
    on_back_clicked(widget,data);
    show_info_dialog(NULL,"返回成功！");
}

// end widgets/info_sort.c