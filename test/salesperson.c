#include "salesperson.h"

// 创建并显示业务员界面
void showSalespersonMenu() {
    GtkWidget *salesperson_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(salesperson_window), "业务员界面");
    gtk_window_set_default_size(GTK_WINDOW(salesperson_window), 200, 100);
    g_signal_connect(salesperson_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *label = gtk_label_new("登录成功，进入业务员界面！");
    gtk_container_add(GTK_CONTAINER(salesperson_window), label);

    gtk_widget_show_all(salesperson_window);
}