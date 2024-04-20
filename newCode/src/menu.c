// menu.c
#include "header.h"

void managerMenuWidget() {
    gtk_init(NULL,NULL);

    managerMenuWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(managerMenuWidgets.window), "通信管理系统 - 经理菜单");
    gtk_window_set_default_size(GTK_WINDOW(managerMenuWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(managerMenuWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(managerMenuWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(managerMenuWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    managerMenuWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(managerMenuWidgets.window), managerMenuWidgets.grid);
    gtk_widget_set_halign(managerMenuWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(managerMenuWidgets.grid, GTK_ALIGN_CENTER);

    managerMenuWidgets.infoManage_btn = gtk_button_new_with_label("信息管理");
    g_signal_connect(managerMenuWidgets.infoManage_btn, "clicked", G_CALLBACK(on_infoManager_clicked), NULL);
    gtk_grid_attach(GTK_GRID(managerMenuWidgets.grid), managerMenuWidgets.infoManage_btn, 0, 0, 2, 1);

    managerMenuWidgets.customerAssign_btn = gtk_button_new_with_label("客户分配");
    g_signal_connect(managerMenuWidgets.customerAssign_btn, "clicked", G_CALLBACK(on_customerAssign_clicked), NULL);
    gtk_grid_attach(GTK_GRID(managerMenuWidgets.grid), managerMenuWidgets.customerAssign_btn, 0, 1, 2, 1);

    managerMenuWidgets.groupManage_btn = gtk_button_new_with_label("分组管理");
    g_signal_connect(managerMenuWidgets.groupManage_btn, "clicked", G_CALLBACK(on_groupManage_clicked), NULL);
    gtk_grid_attach(GTK_GRID(managerMenuWidgets.grid), managerMenuWidgets.groupManage_btn, 0, 2, 2, 1);

    managerMenuWidgets.infoInquiry_btn = gtk_button_new_with_label("信息查询");
    g_signal_connect(managerMenuWidgets.infoInquiry_btn, "clicked", G_CALLBACK(on_infoInquiry_clicked), NULL);
    gtk_grid_attach(GTK_GRID(managerMenuWidgets.grid), managerMenuWidgets.infoInquiry_btn, 0, 3, 2, 1);

    managerMenuWidgets.sortedInfoDisplay_btn = gtk_button_new_with_label("信息排序显示");
    g_signal_connect(managerMenuWidgets.sortedInfoDisplay_btn, "clicked", G_CALLBACK(on_sortedInfoDisplay_clicked), NULL);
    gtk_grid_attach(GTK_GRID(managerMenuWidgets.grid), managerMenuWidgets.sortedInfoDisplay_btn, 0, 4, 2, 1);

    managerMenuWidgets.infoStatistic_btn = gtk_button_new_with_label("信息统计");
    g_signal_connect(managerMenuWidgets.infoStatistic_btn, "clicked", G_CALLBACK(on_infoStatistic_clicked), NULL);
    gtk_grid_attach(GTK_GRID(managerMenuWidgets.grid), managerMenuWidgets.infoStatistic_btn, 0, 5, 2, 1);

    managerMenuWidgets.analysisRecord_btn = gtk_button_new_with_label("通信记录分析");
    g_signal_connect(managerMenuWidgets.analysisRecord_btn, "clicked", G_CALLBACK(on_analysisRecord_clicked), NULL);
    gtk_grid_attach(GTK_GRID(managerMenuWidgets.grid), managerMenuWidgets.analysisRecord_btn, 0, 6, 2, 1);

    managerMenuWidgets.systemSetting_btn = gtk_button_new_with_label("系统维护");
    g_signal_connect(managerMenuWidgets.systemSetting_btn, "clicked", G_CALLBACK(on_systemSetting_clicked), NULL);
    gtk_grid_attach(GTK_GRID(managerMenuWidgets.grid), managerMenuWidgets.systemSetting_btn, 0, 7, 2, 1);

    managerMenuWidgets.exit_btn = gtk_button_new_with_label("退出系统");
    g_signal_connect(managerMenuWidgets.exit_btn, "clicked", G_CALLBACK(on_exit_clicked), NULL);
    gtk_grid_attach(GTK_GRID(managerMenuWidgets.grid), managerMenuWidgets.exit_btn, 0, 8, 2, 1);
    
    gtk_widget_show_all(managerMenuWidgets.window);
    gtk_main();
}

void employeeMenuWidget() {
    gtk_init(NULL,NULL);

    employeeMenuWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(employeeMenuWidgets.window), "通信管理系统 - 业务员菜单");
    gtk_window_set_default_size(GTK_WINDOW(employeeMenuWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(employeeMenuWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(employeeMenuWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(employeeMenuWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    employeeMenuWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(employeeMenuWidgets.window), employeeMenuWidgets.grid);
    gtk_widget_set_halign(employeeMenuWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(employeeMenuWidgets.grid, GTK_ALIGN_CENTER);

    employeeMenuWidgets.recordsManage_btn = gtk_button_new_with_label("记录管理");
    g_signal_connect(employeeMenuWidgets.recordsManage_btn, "clicked", G_CALLBACK(on_recordManage_clicked), NULL);
    gtk_grid_attach(GTK_GRID(employeeMenuWidgets.grid), employeeMenuWidgets.recordsManage_btn, 0, 1, 2, 1);

    employeeMenuWidgets.exit_btn = gtk_button_new_with_label("退出系统");
    g_signal_connect(employeeMenuWidgets.exit_btn, "clicked", G_CALLBACK(on_exit_clicked), NULL);
    gtk_grid_attach(GTK_GRID(employeeMenuWidgets.grid), employeeMenuWidgets.exit_btn, 0, 3, 2, 1);

    gtk_widget_show_all(employeeMenuWidgets.window);
    gtk_main();
}

void exitSystem() {
    printf("感谢使用，再见！\n");
    exit(0);
}

static void on_infoManager_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(managerMenuWidgets.window); 
    infoManageWidget();
}

static void on_customerAssign_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(managerMenuWidgets.window); 
    customerAssignWidget();
}

static void on_groupManage_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(managerMenuWidgets.window); 
    groupManageWidget();
}

static void on_infoInquiry_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(managerMenuWidgets.window); 
    infoEnquiryWidget();
}
static void on_sortedInfoDisplay_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(managerMenuWidgets.window); 
    infoSortWidget();
}
static void on_infoStatistic_clicked(GtkWidget *widget, gpointer data) {

}
static void on_analysisRecord_clicked(GtkWidget *widget, gpointer data) {

}
static void on_systemSetting_clicked(GtkWidget *widget, gpointer data) {
    systemSettingWidget();
}

static void on_exit_clicked(GtkWidget *widget, gpointer data) {
    exitSystem();
}

static void on_recordManage_clicked(GtkWidget *widget, gpointer data) {
    recordsManageWidget();
}

// end menu.c