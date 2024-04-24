// widgets/records_analysis.c
#include "../header.h"

void recordsAnalysisWidget(GtkWidget *parent) {
    initializeAll();

    GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(recordsAnalysisWidgets.window),
                                                GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "正在加载中，请您耐心等待。");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);

    head_node *head = (head_node *)malloc(sizeof(head_node));  // 分配内存
    if (!head) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(recordsAnalysisWidgets.window),
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
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(recordsAnalysisWidgets.window),
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_ERROR,
                                                    GTK_BUTTONS_OK,
                                                    "没有加载到任何数据。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(recordsAnalysisWidgets.window),
                                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "数据加载成功！");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    recordsAnalysisWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(recordsAnalysisWidgets.window), "通信管理系统 - 通信记录分析系统");
    gtk_window_set_default_size(GTK_WINDOW(recordsAnalysisWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(recordsAnalysisWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(recordsAnalysisWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    
    recordsAnalysisWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(recordsAnalysisWidgets.window), recordsAnalysisWidgets.grid);
    gtk_widget_set_halign(recordsAnalysisWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(recordsAnalysisWidgets.grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(recordsAnalysisWidgets.grid), 10);  // 设置行间距
    gtk_grid_set_column_spacing(GTK_GRID(recordsAnalysisWidgets.grid), 10);  // 设置列间距


    recordsAnalysisWidgets.enquiryRecords_btn = gtk_button_new_with_label("查询通信记录");
    g_signal_connect(recordsAnalysisWidgets.enquiryRecords_btn, "clicked", G_CALLBACK(on_enquiryRecords_clicked), head);
    gtk_grid_attach(GTK_GRID(recordsAnalysisWidgets.grid), recordsAnalysisWidgets.enquiryRecords_btn, 0, 0, 2, 1);

    recordsAnalysisWidgets.sortRecords_btn = gtk_button_new_with_label("排序通信记录");
    g_signal_connect(recordsAnalysisWidgets.sortRecords_btn, "clicked", G_CALLBACK(on_sortRecords_clicked), head);
    gtk_grid_attach(GTK_GRID(recordsAnalysisWidgets.grid), recordsAnalysisWidgets.sortRecords_btn, 0, 1, 2, 1);

    recordsAnalysisWidgets.statisticsRecords_btn = gtk_button_new_with_label("统计通信情况");
    g_signal_connect(recordsAnalysisWidgets.statisticsRecords_btn, "clicked", G_CALLBACK(on_statisticsRecords_clicked), head);
    gtk_grid_attach(GTK_GRID(recordsAnalysisWidgets.grid), recordsAnalysisWidgets.statisticsRecords_btn, 0, 2, 2, 1);

    recordsAnalysisWidgets.back_btn = gtk_button_new_with_label("返回");
    WidgetPair *widgetPair = g_slice_new(WidgetPair);
    widgetPair->parentWindow = parent;
    widgetPair->currentWindow = recordsAnalysisWidgets.window;

    g_signal_connect(recordsAnalysisWidgets.back_btn, "clicked", G_CALLBACK(show_info_dialog), "正在返回，请稍等。");
    g_signal_connect(recordsAnalysisWidgets.back_btn, "clicked", G_CALLBACK(freeAll), head);
    g_signal_connect(recordsAnalysisWidgets.back_btn, "clicked", G_CALLBACK(on_recordAnalysisBack_clicked), widgetPair);

    gtk_grid_attach(GTK_GRID(recordsAnalysisWidgets.grid), recordsAnalysisWidgets.back_btn, 0, 3, 2, 1);
    
    gtk_widget_show_all(recordsAnalysisWidgets.window);
    gtk_main();
}

void enquiryRecords(head_node *head) {
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

    GtkWidget *window, *scrolled_window, *text_view;
    GtkTextBuffer *buffer;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "查询结果");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    
    char queryValue[MAX_LENGTH];
    bool found = false;
    bool first = true;
    int attributeIndex = -1;
    head_node *headA;  // 分配内存
    head_node *headB;  // 分配内存

    while (true) {
        const char* message = "信息查询(1. 简单查询 2. 组合查询 3. 模糊查询 4. 返回)";
        
        char get[MAX_LENGTH];
        if(!infoInput(get, sizeof(get),message))return;
        
        if (!isOneChar(get)) {
            GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK_CANCEL,
                                        "无效的选择，请重新输入。");
            gtk_window_set_title(GTK_WINDOW(dialog), "查询失败");
            if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_CANCEL) {
                gtk_widget_destroy(dialog);
                return;
            }
            gtk_widget_destroy(dialog);
            continue;
        }
        GtkWidget* dialog;
        switch (get[0]) {
        case '1':
            attributeIndex = selectSearchAttribute(3);
            if (attributeIndex == -1 || -2) {
                show_info_dialog(NULL,"无效的属性选择。");
                return;
            }
            if(!infoInput(queryValue, sizeof(queryValue), "请输入搜索值："))return;
            printHeading(buffer,3);
            found = searchOnes(buffer,head, NULL, queryValue, attributeIndex, 3, 0);
            if (!found) {
                show_info_dialog(NULL,"没有找到匹配的信息");
            }
            break;
        case '2':
            first = true;
            headA = (head_node *)malloc(sizeof(head_node));  // 分配内存
            headB = (head_node *)malloc(sizeof(head_node));  // 分配内存
            if (!headA || !headB) {
                show_info_dialog(NULL,"内存分配失败！");
                return;
            }
            initializeHeadNode(headA);
            initializeHeadNode(headB);
            while (true) {
                if (!performQueryIteration(head, &headA, &headB, 3, &first)) break;
            }
            freeAll(NULL,headA);
            freeAll(NULL,headB);
            break;
        case '3':
            attributeIndex = selectSearchAttribute(3);
            if (attributeIndex == -1 || -2) {
                show_info_dialog(NULL,"无效的属性选择。");
                return;
            }
            if(!infoInput(queryValue, sizeof(queryValue), "请输入搜索值："))return;
            printHeading(buffer,3);
            found = searchOnes(buffer,head, NULL, queryValue, attributeIndex, 3, 1);
            if (!found) {
                gtk_text_buffer_insert_at_cursor(buffer, "没有找到匹配的信息", -1);
            }
            break;
        case '4':
            return;
        default:
            dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK_CANCEL,
                                        "无效的选择");
            gtk_window_set_title(GTK_WINDOW(dialog), "请重新输入");
            if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_CANCEL) {
                gtk_widget_destroy(dialog);
                return;
            }
            gtk_widget_destroy(dialog);
            break;
        }
    }
    gtk_widget_show_all(window);
}

void sortRecords(head_node *head) {
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

    GtkWidget *window, *scrolled_window, *text_view;
    GtkTextBuffer *buffer;
    const char *heading;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "排序结果");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    while (true) {
        const char* message = "排序显示(1. 显示当前排序 2. 单一属性排序 3. 多属性排序 4. 返回)";
        char get[MAX_LENGTH];
        if(!infoInput(get, sizeof(get),message))return;

        int attributeIndex = 0;
        bool isAscending = false;

        if (!isOneChar(get)) {
            GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK_CANCEL,
                                        "无效的选择，请重新输入。");
            gtk_window_set_title(GTK_WINDOW(dialog), "查询失败");
            if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_CANCEL) {
                gtk_widget_destroy(dialog);
                return;
            }
            gtk_widget_destroy(dialog);
            continue;
        }
        switch (get[0]) {
        case '1':
            heading = "通信记录的信息列表：\n";
            gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
            printNodeList(buffer,head, 3);
            break;
        case '2':
            heading = "通信记录的信息列表：\n";
            gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
            beforeSort(head, 3, &attributeIndex, &isAscending);
            sort(3, head, attributeIndex, isAscending);
            printNodeList(buffer,head, 3);
            break;
        case '3':
            combinedSortHelper(head, 3);
            printNodeList(buffer,head, 3);
            break;
        case '4':
            return;
        default:
            gtk_text_buffer_insert_at_cursor(buffer, "无效的选择，请重新输入。\n", -1);
        }
    }
    gtk_widget_show_all(window);
}

void statisticsRecords(head_node *head) {
    if (head->is_empty) {
        GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "没有可统计的数据。");
        gtk_window_set_title(GTK_WINDOW(dialog), "统计失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    GtkWidget *window, *scrolled_window, *text_view;
    GtkTextBuffer *buffer;
    const char *heading;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "统计结果");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(window), scrolled_window);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    int attrIndex = -1;
    int numAttrs = 0;
    int attrIndexes[32];
    char conditionValues[32][MAX_LENGTH]; // 存储每个属性的条件值
    int numConditions = 0; // 条件数量
    while (true) {
        const char* message = "信息统计(1. 简单统计 2. 组合统计 3. 预设统计 4. 条件统计 5. 返回)";

        char get[MAX_LENGTH];
        if(!infoInput(get, sizeof(get),message))return;
        char choice[MAX_LENGTH];
        bool print = false;

        switch (get[0]) {
        case '1':
            attrIndex = selectSearchAttribute(3);
            if (attrIndex == -1 || -2) {
                GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_ERROR,
                                            GTK_BUTTONS_OK_CANCEL,
                                            "无效的属性选择。");
                gtk_window_set_title(GTK_WINDOW(dialog), "统计失败");
                if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_CANCEL) {
                    gtk_widget_destroy(dialog);
                    return;
                }
                gtk_widget_destroy(dialog);
                break;
            }
            countAttributes(head, attrIndex, 3);
            break;
        case '2':
            print = false;
            while (true) {
                attrIndex = selectSearchAttribute(3);
                attrIndexes[numAttrs++] = attrIndex;
                if (attrIndex == -1 || -2) break;
                else if (numAttrs >= 32) {
                    GtkWidget* dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_ERROR,
                                                GTK_BUTTONS_OK,
                                                "属性索引数量超过限制。");
                    gtk_window_set_title(GTK_WINDOW(dialog), "统计失败");
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy(dialog);
                    break;
                }
                print = true;
            }
            countCombinedAttributes(head, attrIndexes, numAttrs, 3);
            break;
        case '3':
            message = "预设统计选项：(1. 按客户公司统计 2. 按通信内容统计)";
            if(!infoInput(choice, sizeof(choice),message))return;

            if (!isOneChar(choice)) {
                show_info_dialog(NULL,"无效的选择。");
                break;
            }
            GtkWidget* dialog;
            switch (choice[0]) {
            case '1':
                countAttributes(head, 1, 3); // 1 是索引，3 是类型
                break;
            case '2':
                countAttributes(head, 6, 3); // 6 是索引，3 是类型
                break;
            default:
                show_info_dialog(NULL,"统计失败：无效的选择");
                break;
            }
            break;
        case '4':
            dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_INFO,
                                        GTK_BUTTONS_OK_CANCEL,
                                        "请输入属性索引和条件值，输入-1结束索引输入");
            gtk_window_set_title(GTK_WINDOW(dialog), "提示");
            if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_CANCEL) {
                gtk_widget_destroy(dialog);
                return;
            }
            gtk_widget_destroy(dialog);
            print = false;
            while (true) {
                dialog = gtk_message_dialog_new(NULL,
                                            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                            GTK_MESSAGE_INFO,
                                            GTK_BUTTONS_OK_CANCEL,
                                            "请输入属性索引");
                gtk_window_set_title(GTK_WINDOW(dialog), "提示");
                if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_CANCEL) {
                    gtk_widget_destroy(dialog);
                    return;
                }
                gtk_widget_destroy(dialog);
                int attrIndex = selectSearchAttribute(3);
                if (attrIndex == -1 || -2) break;
                attrIndexes[numConditions] = attrIndex;
                print = true;

                if(!infoInput(conditionValues[numConditions], sizeof(conditionValues[numConditions]),"请输入条件值"))return;
                ++numConditions;

                if (numConditions >= 32) {
                    show_info_dialog(NULL,"条件数量超过限制。");
                    break;
                }
            }
            if (print) countAttributesByConditions(head, attrIndexes, conditionValues, numConditions, 3);
            break;
        case '5':
            return;
        default:
            dialog = gtk_message_dialog_new(NULL,
                                        GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_OK,
                                        "无效的选择，请重新输入。");
            gtk_window_set_title(GTK_WINDOW(dialog), "统计失败");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    }
}

void on_enquiryRecords_clicked(GtkWidget *widget, gpointer data) {
    enquiryRecords(data);
}
void on_sortRecords_clicked(GtkWidget *widget, gpointer data) {
    sortRecords(data);
}
void on_statisticsRecords_clicked(GtkWidget *widget, gpointer data) {
    statisticsRecords(data);
}
static void on_recordAnalysisBack_clicked(GtkWidget *widget, gpointer data) {
    on_back_clicked(widget,data);
    show_info_dialog(NULL,"返回成功！");
}

// end widgets/records_analysis.c