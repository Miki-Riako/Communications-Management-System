#include <gtk/gtk.h>

// 定义activate函数
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;

    // 创建一个新窗口
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

    // 显示窗口
    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    // 创建一个新的GtkApplication
    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // 运行应用程序，传入argc和argv
    status = g_application_run(G_APPLICATION(app), argc, argv);
    
    // 清理
    g_object_unref(app);

    return status;
}




