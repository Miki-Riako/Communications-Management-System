#include "manager.h"

// 创建并显示经理界面
void showManagerMenu() {
    GtkWidget *manager_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(manager_window), "经理界面");
    gtk_window_set_default_size(GTK_WINDOW(manager_window), 300, 200);
    g_signal_connect(manager_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 创建一个垂直盒子来放置标签和按钮
    GtkWidget *vbox = gtk_vbox_new(FALSE, 5);

    // 创建一个标签并添加到垂直盒子中
    GtkWidget *label = gtk_label_new("登录成功,进入经理界面！");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    // 创建管理报告的按钮
    GtkWidget *report_button = gtk_button_new_with_label("管理报告");
    g_signal_connect(report_button, "clicked", G_CALLBACK(on_report_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), report_button, FALSE, FALSE, 0);

    // 创建用户管理的按钮
    GtkWidget *user_button = gtk_button_new_with_label("用户管理");
    g_signal_connect(user_button, "clicked", G_CALLBACK(on_user_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), user_button, FALSE, FALSE, 0);

    // 创建审批流程的按钮
    GtkWidget *approval_button = gtk_button_new_with_label("审批流程");
    g_signal_connect(approval_button, "clicked", G_CALLBACK(on_approval_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), approval_button, FALSE, FALSE, 0);

    // 将垂直盒子添加到窗口中
    gtk_container_add(GTK_CONTAINER(manager_window), vbox);

    // 显示所有组件
    gtk_widget_show_all(manager_window);
}

// 以下是按钮的回调函数的占位符，您需要根据实际的功能实现它们
void on_report_button_clicked(GtkWidget *widget, gpointer data) {
    // 处理报告管理的逻辑
    return;
}

void on_user_button_clicked(GtkWidget *widget, gpointer data) {
    // 处理用户管理的逻辑
    return;
}

void on_approval_button_clicked(GtkWidget *widget, gpointer data) {
    // 处理审批流程的逻辑
    return;
}
