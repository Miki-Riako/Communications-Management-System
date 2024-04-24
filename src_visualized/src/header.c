#include "header.h"

void on_back_clicked(GtkWidget *widget, WidgetPair *pair) {
    gtk_widget_destroy(GTK_WIDGET(pair->currentWindow));
    gtk_widget_show(GTK_WIDGET(pair->parentWindow));
}

void show_info_dialog(GtkWidget *widget, const gchar *message) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_INFO,
                                                GTK_BUTTONS_OK,
                                                "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog)); // 显示对话框并等待按钮被点击
    gtk_widget_destroy(dialog); // 销毁对话框
}