// widgets/info_statistics.c
#include "../header.h"

void infoStatisticsWidget(GtkWidget *parent) {
    initializeAll();

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoStatisticsWidgets.window),
                                                GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "正在加载中，请您耐心等待。");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    head_node *head = (head_node *)malloc(sizeof(head_node));  // 分配内存
    if (!head) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoStatisticsWidgets.window),
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
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoStatisticsWidgets.window),
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_OK,
                                                    "没有加载到任何数据。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoStatisticsWidgets.window),
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "数据加载成功！");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    infoStatisticsWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(infoStatisticsWidgets.window), "通信管理系统 - 信息统计系统");
    gtk_window_set_default_size(GTK_WINDOW(infoStatisticsWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(infoStatisticsWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(infoStatisticsWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(infoStatisticsWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    infoStatisticsWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(infoStatisticsWidgets.window), infoStatisticsWidgets.grid);
    gtk_widget_set_halign(infoStatisticsWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(infoStatisticsWidgets.grid, GTK_ALIGN_CENTER);

    infoStatisticsWidgets.simpleStatistics_btn = gtk_button_new_with_label("简单统计");
    g_signal_connect(infoStatisticsWidgets.simpleStatistics_btn, "clicked", G_CALLBACK(on_simpleStatistics_clicked), head);
    gtk_grid_attach(GTK_GRID(infoStatisticsWidgets.grid), infoStatisticsWidgets.simpleStatistics_btn, 0, 0, 2, 1);

    infoStatisticsWidgets.combinedStatistics_btn = gtk_button_new_with_label("组合统计");
    g_signal_connect(infoStatisticsWidgets.combinedStatistics_btn, "clicked", G_CALLBACK(on_combinedStatistics_clicked), head);
    gtk_grid_attach(GTK_GRID(infoStatisticsWidgets.grid), infoStatisticsWidgets.combinedStatistics_btn, 0, 1, 2, 1);

    infoStatisticsWidgets.presetStatistics_btn = gtk_button_new_with_label("预设统计");
    g_signal_connect(infoStatisticsWidgets.presetStatistics_btn, "clicked", G_CALLBACK(on_presetStatistics_clicked), head);
    gtk_grid_attach(GTK_GRID(infoStatisticsWidgets.grid), infoStatisticsWidgets.presetStatistics_btn, 0, 2, 2, 1);

    infoStatisticsWidgets.conditionalStatistics_btn = gtk_button_new_with_label("条件统计");
    g_signal_connect(infoStatisticsWidgets.conditionalStatistics_btn, "clicked", G_CALLBACK(on_conditionalStatistics_clicked), head);
    gtk_grid_attach(GTK_GRID(infoStatisticsWidgets.grid), infoStatisticsWidgets.conditionalStatistics_btn, 0, 2, 2, 1);

    infoStatisticsWidgets.back_btn = gtk_button_new_with_label("返回");
    WidgetPair *widgetPair = g_slice_new(WidgetPair);
    widgetPair->parentWindow = parent;
    widgetPair->currentWindow = infoStatisticsWidgets.window;

    g_signal_connect(infoStatisticsWidgets.back_btn, "clicked", G_CALLBACK(show_info_dialog), "正在返回，请稍等。");
    g_signal_connect(infoStatisticsWidgets.back_btn, "clicked", G_CALLBACK(freeAll), head);
    g_signal_connect(infoStatisticsWidgets.back_btn, "clicked", G_CALLBACK(on_infoStatisticsBack_clicked), widgetPair);

    gtk_grid_attach(GTK_GRID(infoStatisticsWidgets.grid), infoStatisticsWidgets.back_btn, 0, 3, 2, 1);
    
    gtk_widget_show_all(infoStatisticsWidgets.window);
    gtk_main();
}

void simpleStatistics(head_node *head) {
    if (head->is_empty) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoStatisticsWidgets.window),
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_OK,
                                                    "没有可统计的数据。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    int which = beforeInfo(head, "统计");
    if (which == -1) return;  // 无效的选择

    int attrIndex = selectSearchAttribute(which);
    if (attrIndex == -1) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(infoStatisticsWidgets.window),
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_OK,
                                                    "无效的属性选择。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    countAttributes(head, attrIndex, which);
}

void combinedStatistics(head_node *head) {
    if (head->is_empty) {
        show_info_dialog(NULL,"没有可统计的数据。");
        return;
    }

    int which = beforeInfo(head, "统计");
    if (which == -1) return;

    int attrIndexes[32];
    int numAttrs = 0;
    show_info_dialog(NULL,"请输入属性索引，输入-1结束");

    while (true) {
        int attrIndex = selectSearchAttribute(which);
        attrIndexes[numAttrs++] = attrIndex;
        if (attrIndex == -1) break;
        else if (numAttrs >= 32) {
            printf("属性索引数量超过限制。\n");
            break;
        }
    }

    countCombinedAttributes(head, attrIndexes, numAttrs, which);
}

void presetStatistics(head_node *head) {
    if (head->is_empty) {
        show_info_dialog(NULL,"没有可统计的数据。");
        return;
    }
    char choice[MAX_LENGTH];
    infoInput(choice, sizeof(choice),"预设统计选项：\n1. 按区域统计客户\n2. 按区域和地址统计客户\n3. 按规模与联系程度统计客户\n4. 按性别统计联络员\n5. 按性别统计业务员\n请选择一个操作（1-5）：");

    int attrIndexes[3];  // 最多两个属性

    if (!isOneChar(choice)) {
        show_info_dialog(NULL,"无效的选择。");
        return;
    }
    switch (choice[0]) {
    case '1':
        // 按区域统计客户
        countAttributes(head, 1, 0); // 1 是区域属性索引，0 是客户类型
        break;
    case '2':
        // 按区域和地址统计客户
        attrIndexes[0] = 1;
        attrIndexes[1] = 2;
        attrIndexes[2] = -1;
        countCombinedAttributes(head, attrIndexes, 3, 0); // 0 是客户类型
        break;
    case '3':
        // 按规模与联系程度统计客户
        attrIndexes[0] = 4; // 规模
        attrIndexes[1] = 5; // 联系程度
        attrIndexes[2] = -1;
        countCombinedAttributes(head, attrIndexes, 3, 0); // 0 是客户类型
        break;
    case '4':
        // 按性别统计联络员
        if (IsManager) {
            countAttributes(head, 1, 1); // 1 是性别属性索引，1 是联络人类型
        } else {
            show_info_dialog(NULL,"您不是经理，没有权限执行此操作。");
        }
        break;
    case '5':
        // 按性别统计业务员
        if (IsManager) {
            countAttributes(head, 1, 2); // 1 是性别属性索引，2 是业务员类型
        } else {
            show_info_dialog(NULL,"您不是经理，没有权限执行此操作。");
        }
        break;
    default:
        show_info_dialog(NULL,"无效的选择。");
        break;
    }
}

void conditionalStatistics(head_node *head) {
    if (head->is_empty) {
        show_info_dialog(NULL,"没有可统计的数据。");
        return;
    }

    int which = beforeInfo(head, "统计");
    if (which == -1) return;  // 无效的选择

    int attrIndexes[32]; // 存储属性索引
    char conditionValues[32][MAX_LENGTH]; // 存储每个属性的条件值
    int numConditions = 0; // 条件数量
    bool print = false;

    show_info_dialog(NULL,"请输入属性索引和条件值，输入-1结束索引输入");
    while (true) {
        show_info_dialog(NULL,"输入属性索引");
        int attrIndex = selectSearchAttribute(which);
        if (attrIndex == -1) break;
        attrIndexes[numConditions] = attrIndex;
        print = true;

        infoInput(conditionValues[numConditions], sizeof(conditionValues[numConditions]),"输入条件值");
        ++numConditions;

        if (numConditions >= 32) {
            show_info_dialog(NULL,"条件数量超过限制。");
            break;
        }
    }

    if (print) countAttributesByConditions(head, attrIndexes, conditionValues, numConditions, which);
}


void on_simpleStatistics_clicked(GtkWidget *widget, gpointer data) {
    simpleStatistics(data);
}
void on_combinedStatistics_clicked(GtkWidget *widget, gpointer data) {
    combinedStatistics(data);
}
void on_presetStatistics_clicked(GtkWidget *widget, gpointer data) {
    presetStatistics(data);
}
void on_conditionalStatistics_clicked(GtkWidget *widget, gpointer data) {
    conditionalStatistics(data);
}
static void on_infoStatisticsBack_clicked(GtkWidget *widget, gpointer data) {
    on_back_clicked(widget,data);
    show_info_dialog(NULL,"返回成功！");
}

// end widgets/info_statistics.c