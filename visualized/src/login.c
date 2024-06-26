// login.c
#include "header.h"

void startWidget() {
    gtk_init(NULL, NULL);
    initializeInfoFile("user.csv", "");
    startWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(startWidgets.window), "开始界面");
    gtk_window_set_default_size(GTK_WINDOW(startWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(startWidgets.window), 50);
    g_signal_connect(startWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_position(GTK_WINDOW(startWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间

    // gtk_window_maximize(GTK_WINDOW(startWidgets.window));

    startWidgets.grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(startWidgets.grid), 10);  // 设置行间距
    gtk_grid_set_column_spacing(GTK_GRID(startWidgets.grid), 10);  // 设置列间距
    gtk_container_add(GTK_CONTAINER(startWidgets.window), startWidgets.grid);
    gtk_widget_set_halign(startWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(startWidgets.grid, GTK_ALIGN_CENTER);

    startWidgets.loginManager_btn = gtk_button_new_with_label("公司经理");
    g_signal_connect(startWidgets.loginManager_btn, "clicked", G_CALLBACK(on_loginManager_clicked), NULL);
    gtk_grid_attach(GTK_GRID(startWidgets.grid), startWidgets.loginManager_btn, 0, 0, 1, 1);

    startWidgets.loginEmployee_btn = gtk_button_new_with_label("公司业务员");
    g_signal_connect(startWidgets.loginEmployee_btn, "clicked", G_CALLBACK(on_loginEmployee_clicked), NULL);
    gtk_grid_attach(GTK_GRID(startWidgets.grid), startWidgets.loginEmployee_btn, 0, 1, 1, 1);

    startWidgets.register_btn = gtk_button_new_with_label("注册业务员");
    g_signal_connect(startWidgets.register_btn, "clicked", G_CALLBACK(on_register_clicked), NULL);
    gtk_grid_attach(GTK_GRID(startWidgets.grid), startWidgets.register_btn, 0, 2, 1, 1);

    startWidgets.quit_btn = gtk_button_new_with_label("退出程序");
    g_signal_connect(startWidgets.quit_btn, "clicked", G_CALLBACK(on_quit_clicked), NULL);
    gtk_grid_attach(GTK_GRID(startWidgets.grid), startWidgets.quit_btn, 0, 3, 1, 1);
    
    
    gtk_widget_show_all(startWidgets.window);
    gtk_main();
}

void loginManagerWidget() {
    gtk_init(NULL, NULL);
    loginManagerWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(loginManagerWidgets.window), "经理登录界面");
    gtk_window_set_default_size(GTK_WINDOW(loginManagerWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(loginManagerWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(loginManagerWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(loginManagerWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // gtk_window_maximize(GTK_WINDOW(loginManagerWidgets.window));

    loginManagerWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(loginManagerWidgets.window), loginManagerWidgets.grid);
    gtk_widget_set_halign(loginManagerWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(loginManagerWidgets.grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(loginManagerWidgets.grid), 10);  // 设置行间距
    gtk_grid_set_column_spacing(GTK_GRID(loginManagerWidgets.grid), 10);  // 设置列间距

    loginManagerWidgets.chance = 3;

    loginManagerWidgets.label = gtk_label_new("请输入公司密钥：");
    gtk_grid_attach(GTK_GRID(loginManagerWidgets.grid), loginManagerWidgets.label, 0, 0, 2, 1);
    loginManagerWidgets.password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(loginManagerWidgets.password_entry), TRUE);
    gtk_grid_attach(GTK_GRID(loginManagerWidgets.grid), loginManagerWidgets.password_entry, 0, 1, 2, 1);
    
    loginManagerWidgets.confirmLoginManager_btn = gtk_button_new_with_label("确认登录");
    g_signal_connect(loginManagerWidgets.confirmLoginManager_btn, "clicked", G_CALLBACK(on_confirm_loginManager_clicked), NULL);
    gtk_grid_attach(GTK_GRID(loginManagerWidgets.grid), loginManagerWidgets.confirmLoginManager_btn, 0, 2, 1, 1);
    
    loginManagerWidgets.backToStart_btn = gtk_button_new_with_label("返回开始界面");
    g_signal_connect(loginManagerWidgets.backToStart_btn, "clicked", G_CALLBACK(on_backtoStart_clicked), loginManagerWidgets.window);
    gtk_grid_attach(GTK_GRID(loginManagerWidgets.grid), loginManagerWidgets.backToStart_btn, 1, 2, 1, 1);
    
    gtk_widget_show_all(loginManagerWidgets.window);
    gtk_main();
}

void loginEmployeeWidget() {
    gtk_init(NULL, NULL);
    loginEmployeeWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(loginEmployeeWidgets.window), "业务员登录界面");
    gtk_window_set_default_size(GTK_WINDOW(loginEmployeeWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(loginEmployeeWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(loginEmployeeWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(loginEmployeeWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // gtk_window_maximize(GTK_WINDOW(loginEmployeeWidgets.window));

    loginEmployeeWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(loginEmployeeWidgets.window), loginEmployeeWidgets.grid);
    gtk_widget_set_halign(loginEmployeeWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(loginEmployeeWidgets.grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(loginEmployeeWidgets.grid), 10);  // 设置行间距
    gtk_grid_set_column_spacing(GTK_GRID(loginEmployeeWidgets.grid), 10);  // 设置列间距

    loginEmployeeWidgets.username_label = gtk_label_new("用户名：");
    gtk_grid_attach(GTK_GRID(loginEmployeeWidgets.grid), loginEmployeeWidgets.username_label, 0, 0, 1, 1);
    loginEmployeeWidgets.username_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(loginEmployeeWidgets.grid), loginEmployeeWidgets.username_entry, 1, 0, 1, 1);
    
    loginEmployeeWidgets.password_label = gtk_label_new("密码： ");
    gtk_grid_attach(GTK_GRID(loginEmployeeWidgets.grid),loginEmployeeWidgets.password_label,0,1,1,1);
    loginEmployeeWidgets.password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(loginEmployeeWidgets.password_entry), TRUE);
    gtk_grid_attach(GTK_GRID(loginEmployeeWidgets.grid), loginEmployeeWidgets.password_entry, 1, 1, 2, 1);
    
    loginEmployeeWidgets.confirmLoginManager_btn = gtk_button_new_with_label("确认登录");
    g_signal_connect(loginEmployeeWidgets.confirmLoginManager_btn, "clicked", G_CALLBACK(on_confirm_loginEmployee_clicked), NULL);
    gtk_grid_attach(GTK_GRID(loginEmployeeWidgets.grid), loginEmployeeWidgets.confirmLoginManager_btn, 0, 2, 1, 1);
    
    loginEmployeeWidgets.backToStart_btn = gtk_button_new_with_label("返回开始界面");
    g_signal_connect(loginEmployeeWidgets.backToStart_btn, "clicked", G_CALLBACK(on_backtoStart_clicked), loginEmployeeWidgets.window);
    gtk_grid_attach(GTK_GRID(loginEmployeeWidgets.grid), loginEmployeeWidgets.backToStart_btn, 1, 2, 1, 1);
    
    gtk_widget_show_all(loginEmployeeWidgets.window);
    gtk_main();
}

void registerWidget() {
    gtk_init(NULL, NULL);
    registerWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(registerWidgets.window), "用户注册界面");
    gtk_window_set_default_size(GTK_WINDOW(registerWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(registerWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(registerWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间

    // gtk_window_maximize(GTK_WINDOW(registerWidgets.window));

    g_signal_connect(registerWidgets.window, "destroy", G_CALLBACK(on_backtoStart_clicked), registerWidgets.window);

    registerWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(registerWidgets.window), registerWidgets.grid);
    gtk_widget_set_halign(registerWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(registerWidgets.grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(registerWidgets.grid), 10);  // 设置行间距
    gtk_grid_set_column_spacing(GTK_GRID(registerWidgets.grid), 10);  // 设置列间距

    registerWidgets.username_label = gtk_label_new("用户名：");
    gtk_grid_attach(GTK_GRID(registerWidgets.grid), registerWidgets.username_label, 0, 0, 1, 1);
    registerWidgets.username_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(registerWidgets.grid), registerWidgets.username_entry, 1, 0, 1, 1);
    
    registerWidgets.password_label = gtk_label_new("密码： ");
    gtk_grid_attach(GTK_GRID(registerWidgets.grid),registerWidgets.password_label,0,1,1,1);
    registerWidgets.password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(registerWidgets.password_entry), TRUE);
    gtk_grid_attach(GTK_GRID(registerWidgets.grid), registerWidgets.password_entry, 1, 1, 2, 1);
    
    registerWidgets.confirmRegister_btn = gtk_button_new_with_label("确认注册");
    g_signal_connect(registerWidgets.confirmRegister_btn, "clicked", G_CALLBACK(on_confirm_Register_clicked), NULL);
    gtk_grid_attach(GTK_GRID(registerWidgets.grid), registerWidgets.confirmRegister_btn, 0, 2, 1, 1);
    
    registerWidgets.backToStart_btn = gtk_button_new_with_label("返回开始界面");
    g_signal_connect(registerWidgets.backToStart_btn, "clicked", G_CALLBACK(on_backtoStart_clicked), registerWidgets.window);
    gtk_grid_attach(GTK_GRID(registerWidgets.grid), registerWidgets.backToStart_btn, 1, 2, 1, 1);
    
    gtk_widget_show_all(registerWidgets.window);
    gtk_main();
}

static void on_loginManager_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(startWidgets.window);
    loginManagerWidget();
}
static void on_loginEmployee_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(startWidgets.window);
    loginEmployeeWidget();
}
static void on_register_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(startWidgets.window);
    registerWidget();
}
static void on_quit_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(startWidgets.window);
    printf("程序已退出。\n");
    exit(0);
}


static void on_confirm_loginManager_clicked(GtkWidget *widget, gpointer data) {
    if(!loginManagerWidgets.chance) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(loginEmployeeWidgets.window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "尝试使用密钥登录失败，系统关闭。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        exit(0);
    }
    const char *password_const = gtk_entry_get_text(GTK_ENTRY(loginManagerWidgets.password_entry));
    char password[MAX_LENGTH];
    strncpy(password,password_const,MAX_LENGTH);
    password[strcspn(password, "\n")] = 0;
    if(isSameString(password, SECRET_KEY) || DEBUG_MODE) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(loginEmployeeWidgets.window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "登录成功！欢迎, 经理!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        strcpy(User, "Manager");
        IsManager = true;
        gtk_widget_destroy(loginManagerWidgets.window);
        managerMenuWidget();
        return;  
    } else {
        loginManagerWidgets.chance--;
        // 创建消息对话框，先不设置具体的消息内容
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_ERROR,
                                                GTK_BUTTONS_OK,
                                                "登录失败");

        // 设置带格式的次级文本
        gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog),
                                                "密码错误。还剩下 %d 次机会。", loginManagerWidgets.chance);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        if(loginManagerWidgets.chance == 0) exit(0);
        return;
    }
}
static void on_backtoStart_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_show(startWidgets.window);
    gtk_widget_destroy(data);  
}

static void on_confirm_loginEmployee_clicked(GtkWidget *widget, gpointer data) {
    char encryptedPassword[MAX_LENGTH * 2];
    const char *username_const = gtk_entry_get_text(GTK_ENTRY(loginEmployeeWidgets.username_entry));
    const char *password_const = gtk_entry_get_text(GTK_ENTRY(loginEmployeeWidgets.password_entry));
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    strncpy(username,username_const,MAX_LENGTH);
    username[strcspn(username, "\n")] = 0;
    if (isEmpty(username)) strcpy(username, " ");
    strncpy(password,password_const,MAX_LENGTH);
    password[strcspn(password, "\n")] = 0;
    if (isEmpty(password)) strcpy(password, " ");
    
    xorEncryptDecrypt(password, strlen(password), encryptedPassword); // 加密用户密码
    
    // 验证登录
    if (verify(username, encryptedPassword) || DEBUG_MODE) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(loginEmployeeWidgets.window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_INFO,
                                                   GTK_BUTTONS_OK,
                                                   "登录成功！");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        strcpy(User, username);
        IsManager = false;
        gtk_widget_destroy(loginEmployeeWidgets.window);
        employeeMenuWidget();    
        return;
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(loginEmployeeWidgets.window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "登录失败，用户名或密码错误。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
}

static void on_confirm_Register_clicked(GtkWidget *widget, gpointer data) {
    FILE *file;
    char line[MAX_LENGTH * 3];
    char encryptedPassword[MAX_LENGTH * 2];
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char role[MAX_LENGTH];

    const char *username_const = gtk_entry_get_text(GTK_ENTRY(registerWidgets.username_entry));
    const char *password_const = gtk_entry_get_text(GTK_ENTRY(registerWidgets.password_entry));
    strncpy(username,username_const,MAX_LENGTH);
    username[strcspn(username, "\n")] = 0;
    if (isEmpty(username)) strcpy(username, " ");
    strncpy(password,password_const,MAX_LENGTH);
    password[strcspn(password, "\n")] = 0;
    if (isEmpty(password)) strcpy(password, " ");

    if (isEmpty(username)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(registerWidgets.window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "用户名不能为空。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    } else if (alreadyExists("user.csv", username)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(registerWidgets.window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "用户名已存在。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    } 

    
    if (matchRegex(password)) {
        xorEncryptDecrypt(password, strlen(password), encryptedPassword);
    } else {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(registerWidgets.window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "密码不符合要求。必须至少8个字符且包含大写字母、小写字母、数字、标点符号中的两种。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    file = fopen("user.csv", "r");
    if (!file) {
        perror("打开文件失败");
        return;
    }

    char fullLine[MAX_LENGTH * 3 + 4];
    strcpy(fullLine, username);
    addColumn(fullLine, encryptedPassword);
    writeLineToFile("user.csv", fullLine);
    fclose(file);

    GtkWidget *confirm_dialog = gtk_message_dialog_new(GTK_WINDOW(registerWidgets.window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_QUESTION,
                                                   GTK_BUTTONS_YES_NO,
                                                   "用户注册成功,要现在就添加用户的信息吗？");
    gint response = gtk_dialog_run(GTK_DIALOG(confirm_dialog));
    gtk_widget_destroy(confirm_dialog);

    if (response == GTK_RESPONSE_YES) {
        Employee newEmployee;
        addEntry(1, "employees.csv", "请输入业务员信息：", &newEmployee, NULL, NULL);
        
    }
    system(SYSTEM_CLEAR);
}

// end login.c