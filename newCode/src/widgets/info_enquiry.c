// widgets/info_enquiry.c
#include "../header.h"

void infoEnquiryWidget(GtkWidget *parent) {
    initializeAll();
    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoEnquiryWidgets.window),
                                                GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "正在加载中，请您耐心等待。");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    head_node *head = (head_node *)malloc(sizeof(head_node));  // 分配内存
    if (!head) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoEnquiryWidgets.window),
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_OK,
                                                    "内存分配失败！");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        gtk_widget_show(employeeMenuWidgets.window);
        return;
    }
    loadFile(head);  // 加载数据
    if (head->is_empty) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoEnquiryWidgets.window),
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_OK,
                                                    "没有加载到任何数据。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        gtk_widget_show(employeeMenuWidgets.window);
        return;
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoEnquiryWidgets.window),
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "数据加载成功！");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    infoEnquiryWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(infoEnquiryWidgets.window), "通信管理系统 - 经理菜单 - 信息查询系统");
    gtk_window_set_default_size(GTK_WINDOW(infoEnquiryWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(infoEnquiryWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(infoEnquiryWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(infoEnquiryWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    infoEnquiryWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(infoEnquiryWidgets.window), infoEnquiryWidgets.grid);
    gtk_widget_set_halign(infoEnquiryWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(infoEnquiryWidgets.grid, GTK_ALIGN_CENTER);

    infoEnquiryWidgets.simpleQuery_btn = gtk_button_new_with_label("简单查询");
    g_signal_connect(infoEnquiryWidgets.simpleQuery_btn, "clicked", G_CALLBACK(on_simpleQuery_clicked), head);
    gtk_grid_attach(GTK_GRID(infoEnquiryWidgets.grid), infoEnquiryWidgets.simpleQuery_btn, 0, 0, 2, 1);

    infoEnquiryWidgets.combinedQuery_btn = gtk_button_new_with_label("组合查询");
    g_signal_connect(infoEnquiryWidgets.combinedQuery_btn, "clicked", G_CALLBACK(on_combinedQuery_clicked), head);
    gtk_grid_attach(GTK_GRID(infoEnquiryWidgets.grid), infoEnquiryWidgets.combinedQuery_btn, 0, 1, 2, 1);

    infoEnquiryWidgets.fuzzyQuery_btn = gtk_button_new_with_label("模糊查询");
    g_signal_connect(infoEnquiryWidgets.fuzzyQuery_btn, "clicked", G_CALLBACK(on_fuzzyQuery_clicked), head);
    gtk_grid_attach(GTK_GRID(infoEnquiryWidgets.grid), infoEnquiryWidgets.fuzzyQuery_btn, 0, 2, 2, 1);

    infoEnquiryWidgets.back_btn = gtk_button_new_with_label("返回");

    WidgetPair *widgetPair = g_slice_new(WidgetPair);
    widgetPair->parentWindow = parent;
    widgetPair->currentWindow = infoEnquiryWidgets.window;
    g_signal_connect(infoEnquiryWidgets.back_btn, "clicked", G_CALLBACK(on_back_clicked), widgetPair);
    gtk_grid_attach(GTK_GRID(infoEnquiryWidgets.grid), infoEnquiryWidgets.back_btn, 0, 3, 2, 1);
    
    gtk_widget_show_all(infoEnquiryWidgets.window);
    gtk_main();
    
}

void simpleQuery(head_node *head) {
    if (head == NULL || head->is_empty) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "没有可查询的数据。");
        gtk_window_set_title(GTK_WINDOW(dialog), "查询失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    int which = beforeInfo(head, "查询");
    if (which == -1) return;  // 无效的查询类型或无数据类型被选中

    char queryValue[MAX_LENGTH];
    bool found = false;
    int attributeIndex = selectSearchAttribute(which);
    if (attributeIndex == -1) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "无效的属性选择。");
        gtk_window_set_title(GTK_WINDOW(dialog), "查询失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    // 获取用户想要搜索的值
    if(!infoInput(queryValue, sizeof(queryValue), "请输入搜索值："))return;


    GtkWidget *window, *scrolled_window, *text_view;
    GtkTextBuffer *buffer;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "搜索结果");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // 根据用户选择决定查询内容和显示格式
    printHeading(buffer,which);
    found = searchOnes(buffer,head, NULL, queryValue, attributeIndex, which, 0);
    if (!found) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "没有找到匹配的信息。");
        gtk_window_set_title(GTK_WINDOW(dialog), "查询失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    gtk_widget_show_all(window);
}

void combinedQuery(head_node *head) {
    // 多一个链表，A链表符合条件的放到B链表，还搜的话就B链表变A链表，继续以此类推
    if (head == NULL || head->is_empty) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "没有可查询的数据。");
        gtk_window_set_title(GTK_WINDOW(dialog), "查询失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    int which = beforeInfo(head, "查询");
    if (which == -1) return;  // 无效的查询类型或无数据类型被选中
    
    bool first = true;
    head_node *headA = (head_node *)malloc(sizeof(head_node));  // 分配内存
    head_node *headB = (head_node *)malloc(sizeof(head_node));  // 分配内存
    if (!headA || !headB) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "内存分配失败！");
        gtk_window_set_title(GTK_WINDOW(dialog), "查询失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    initializeHeadNode(headA);
    initializeHeadNode(headB);

    while (true) {
        if (!performQueryIteration(head, &headA, &headB, which, &first)) break;
    }

    freeAll(NULL,headA);
    freeAll(NULL,headB);
}

void fuzzyQuery(head_node *head) {
    if (head == NULL || head->is_empty) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "没有可查询的数据。");
        gtk_window_set_title(GTK_WINDOW(dialog), "查询失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    int which = beforeInfo(head, "查询");
    if (which == -1) return;

    char queryValue[MAX_LENGTH];
    bool found = false;
    int attributeIndex = selectSearchAttribute(which);
    if (attributeIndex == -1) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "无效的属性选择。");
        gtk_window_set_title(GTK_WINDOW(dialog), "查询失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // 获取用户想要搜索的值
    if(!infoInput(queryValue, sizeof(queryValue), "请输入搜索值："))return;

    GtkWidget *window, *scrolled_window, *text_view;
    GtkTextBuffer *buffer;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "搜索结果");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // 根据用户选择决定查询内容和显示格式
    printHeading(buffer,which);
    found = searchOnes(buffer,head, NULL, queryValue, attributeIndex, which, 1);
    if (!found) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "没有找到匹配的信息。");
        gtk_window_set_title(GTK_WINDOW(dialog), "查询失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }
    gtk_widget_show_all(window);
}

static void on_simpleQuery_clicked(GtkWidget *widget, gpointer data) {
    simpleQuery(data);
}
static void on_combinedQuery_clicked(GtkWidget *widget, gpointer data) {
    combinedQuery(data);
}
static void on_fuzzyQuery_clicked(GtkWidget *widget, gpointer data) {
    fuzzyQuery(data);
}

// end widgets/info_enquiry.c