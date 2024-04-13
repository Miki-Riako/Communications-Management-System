#include "login.h"

// 创建登录窗口的函数
void create_login_window() {
    gtk_init(NULL,NULL);
    // 创建登录窗口
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "登录界面");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_container_add(GTK_CONTAINER(window), vbox);

     // 创建并添加用户名标签和输入框
    GtkWidget *username_label = gtk_label_new("Username:");
    GtkWidget *username_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(vbox), username_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), username_entry, FALSE, FALSE, 0);

    // 创建并添加密码标签和输入框
    GtkWidget *password_label = gtk_label_new("Password:");
    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE);
    gtk_box_pack_start(GTK_BOX(vbox), password_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), password_entry, FALSE, FALSE, 0);

    // 创建身份选择下拉菜单
    GtkWidget *role_label = gtk_label_new("Role:");
    GtkWidget *role_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(role_combo), NULL, "经理");
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT(role_combo), NULL, "业务员");
    gtk_combo_box_set_active(GTK_COMBO_BOX(role_combo), 0); // 设置默认选择
    gtk_box_pack_start(GTK_BOX(vbox), role_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), role_combo, FALSE, FALSE, 0);

    // 创建并添加登录按钮
    GtkWidget *login_button = gtk_button_new_with_label("Login");
    gtk_box_pack_start(GTK_BOX(vbox), login_button, FALSE, FALSE, 0);

    GtkWidget *entries[4] = {username_entry, password_entry, window, role_combo};
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_clicked), entries);

    gtk_widget_show_all(window);
    gtk_main();
}

// 登录按钮的回调函数
static void on_login_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget **widgets = (GtkWidget **)data;
    if (!GTK_IS_ENTRY(widgets[0]) || !GTK_IS_ENTRY(widgets[1])) {
        g_print("Error: Invalid entry widget\n");
        return;
    }
    const char *username = gtk_entry_get_text(GTK_ENTRY(widgets[0]));
    const char *password = gtk_entry_get_text(GTK_ENTRY(widgets[1]));
    const char *role = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(widgets[3]));

    if (strcmp(username, "admin") == 0 && strcmp(password, "password") == 0) {
        // 隐藏登录窗口
        gtk_widget_hide(widgets[2]);

        // 根据角色显示不同的窗口
        if (strcmp(role, "经理") == 0) {
            // 显示经理窗口
            showManagerMenu();
        } else if (strcmp(role, "业务员") == 0) {
            // 显示业务员窗口
            showSalespersonMenu();
        }
    } else {
        printf("用户名或密码错误\n");
    }

    g_free((gpointer)role); // 释放由 gtk_combo_box_text_get_active_text 返回的字符串
}