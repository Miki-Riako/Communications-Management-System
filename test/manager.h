#ifndef MANAGER_H
#define MANAGER_H
#include <gtk/gtk.h>
#include "login.h"
// 创建并显示经理界面
void showManagerMenu();
void on_approval_button_clicked(GtkWidget *widget, gpointer data);
void on_user_button_clicked(GtkWidget *widget, gpointer data);
void on_report_button_clicked(GtkWidget *widget, gpointer data);
#endif