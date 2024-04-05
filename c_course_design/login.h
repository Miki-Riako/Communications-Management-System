#ifndef LOGIN_H
#define LOGIN_H
#include <gtk/gtk.h>
// 声明登录界面创建函数
void create_login_window();

// 登录按钮的回调函数
static void on_login_clicked(GtkWidget *widget, gpointer data);


#endif