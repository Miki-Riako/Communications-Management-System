// login.c
#include "header.h"
#include "menu.c"

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *loginManager_btn;
    GtkWidget *loginEmployee_btn;
    GtkWidget *register_btn;
    GtkWidget *quit_btn;
} StartWidgets;
StartWidgets startWidgets;

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *password_entry;
    GtkWidget *confirmLoginManager_btn;
    GtkWidget *backToStart_btn;
    int chance;
} LoginManagerWidgets;
LoginManagerWidgets loginManagerWidgets;

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *username_label;
    GtkWidget *username_entry;
    GtkWidget *password_label;
    GtkWidget *password_entry;
    GtkWidget *confirmLoginManager_btn;
    GtkWidget *backToStart_btn;
}LoginEmployeeWidgets;
LoginEmployeeWidgets loginEmployeeWidgets;

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *username_label;
    GtkWidget *username_entry;
    GtkWidget *password_label;
    GtkWidget *password_entry;
    GtkWidget *confirmRegister_btn;
    GtkWidget *backToStart_btn;
}RegisterWidgets;
RegisterWidgets registerWidgets;

static void on_loginManager_clicked(GtkWidget *widget, gpointer data);
static void on_loginEmployee_clicked(GtkWidget *widget, gpointer data);
static void on_register_clicked(GtkWidget *widget, gpointer data);
static void on_quit_clicked(GtkWidget *widget, gpointer data);

static void on_confirm_loginManager_clicked(GtkWidget *widget, gpointer data);
static void on_backtoStart_clicked(GtkWidget *widget, gpointer data);

static void on_confirm_loginEmployee_clicked(GtkWidget *widget, gpointer data);

static void on_confirm_Register_clicked(GtkWidget *widget, gpointer data);

void startWidget();
void loginManagerWidget();
void loginEmployeeWidget();
void registerWidget();
bool verify(const char *username, const char *password);

void startWidget() {
    initializeInfoFile("user.csv", "");
    startWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(startWidgets.window), "开始界面");
    gtk_window_set_default_size(GTK_WINDOW(startWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(startWidgets.window), 50);
    g_signal_connect(startWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_position(GTK_WINDOW(startWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间

    startWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(startWidgets.window), startWidgets.grid);
    gtk_widget_set_halign(startWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(startWidgets.grid, GTK_ALIGN_CENTER);

    startWidgets.loginManager_btn = gtk_button_new_with_label("公司经理");
    g_signal_connect(startWidgets.loginManager_btn, "clicked", G_CALLBACK(on_loginManager_clicked), NULL);
    gtk_grid_attach(GTK_GRID(startWidgets.grid), startWidgets.loginManager_btn, 0, 0, 10, 5);
    
    startWidgets.loginEmployee_btn = gtk_button_new_with_label("公司业务员");
    g_signal_connect(startWidgets.loginEmployee_btn, "clicked", G_CALLBACK(on_loginEmployee_clicked), NULL);
    gtk_grid_attach(GTK_GRID(startWidgets.grid), startWidgets.loginEmployee_btn, 0, 20, 10, 5);
    
    startWidgets.register_btn = gtk_button_new_with_label("注册业务员");
    g_signal_connect(startWidgets.register_btn, "clicked", G_CALLBACK(on_register_clicked), NULL);
    gtk_grid_attach(GTK_GRID(startWidgets.grid), startWidgets.register_btn, 0, 30, 10, 5);
    
    startWidgets.quit_btn = gtk_button_new_with_label("退出程序");
    g_signal_connect(startWidgets.quit_btn, "clicked", G_CALLBACK(on_quit_clicked), NULL);
    gtk_grid_attach(GTK_GRID(startWidgets.grid), startWidgets.quit_btn, 0,40, 10, 5);
    
     
    gtk_widget_show_all(startWidgets.window);
}

void loginManagerWidget() {

    loginManagerWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(loginManagerWidgets.window), "经理登录界面");
    gtk_window_set_default_size(GTK_WINDOW(loginManagerWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(loginManagerWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(loginManagerWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(loginManagerWidgets.window, "destroy", G_CALLBACK(on_backtoStart_clicked), NULL);
    
    loginManagerWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(loginManagerWidgets.window), loginManagerWidgets.grid);
    gtk_widget_set_halign(loginManagerWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(loginManagerWidgets.grid, GTK_ALIGN_CENTER);

    loginManagerWidgets.chance = 3;

    loginManagerWidgets.label = gtk_label_new("请输入公司密钥：");
    gtk_grid_attach(GTK_GRID(loginManagerWidgets.grid), loginManagerWidgets.label, 0, 0, 2, 1);
    loginManagerWidgets.password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(loginManagerWidgets.password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(loginManagerWidgets.grid), loginManagerWidgets.password_entry, 0, 1, 2, 1);
    
    loginManagerWidgets.confirmLoginManager_btn = gtk_button_new_with_label("确认登录");
    g_signal_connect(loginManagerWidgets.confirmLoginManager_btn, "clicked", G_CALLBACK(on_confirm_loginManager_clicked), NULL);
    gtk_grid_attach(GTK_GRID(loginManagerWidgets.grid), loginManagerWidgets.confirmLoginManager_btn, 0, 2, 1, 1);
    
    loginManagerWidgets.backToStart_btn = gtk_button_new_with_label("返回开始界面");
    g_signal_connect(loginManagerWidgets.backToStart_btn, "clicked", G_CALLBACK(on_backtoStart_clicked), loginManagerWidgets.window);
    gtk_grid_attach(GTK_GRID(loginManagerWidgets.grid), loginManagerWidgets.backToStart_btn, 1, 2, 1, 1);
    
    gtk_widget_show_all(loginManagerWidgets.window);
}

void loginEmployeeWidget() {
    loginEmployeeWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(loginEmployeeWidgets.window), "业务员登录界面");
    gtk_window_set_default_size(GTK_WINDOW(loginEmployeeWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(loginEmployeeWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(loginEmployeeWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(loginEmployeeWidgets.window, "destroy", G_CALLBACK(on_backtoStart_clicked), NULL);
    
    loginEmployeeWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(loginEmployeeWidgets.window), loginEmployeeWidgets.grid);
    gtk_widget_set_halign(loginEmployeeWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(loginEmployeeWidgets.grid, GTK_ALIGN_CENTER);

    loginEmployeeWidgets.username_label = gtk_label_new("用户名：");
    gtk_grid_attach(GTK_GRID(loginEmployeeWidgets.grid), loginEmployeeWidgets.username_label, 0, 0, 1, 1);
    loginEmployeeWidgets.username_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(loginEmployeeWidgets.grid), loginEmployeeWidgets.username_entry, 1, 0, 1, 1);
    
    loginEmployeeWidgets.password_label = gtk_label_new("密码： ");
    gtk_grid_attach(GTK_GRID(loginEmployeeWidgets.grid),loginEmployeeWidgets.password_label,0,1,1,1);
    loginEmployeeWidgets.password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(loginEmployeeWidgets.password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(loginEmployeeWidgets.grid), loginEmployeeWidgets.password_entry, 1, 1, 2, 1);
    
    loginEmployeeWidgets.confirmLoginManager_btn = gtk_button_new_with_label("确认登录");
    g_signal_connect(loginEmployeeWidgets.confirmLoginManager_btn, "clicked", G_CALLBACK(on_confirm_loginEmployee_clicked), NULL);
    gtk_grid_attach(GTK_GRID(loginEmployeeWidgets.grid), loginEmployeeWidgets.confirmLoginManager_btn, 0, 2, 1, 1);
    
    loginEmployeeWidgets.backToStart_btn = gtk_button_new_with_label("返回开始界面");
    g_signal_connect(loginEmployeeWidgets.backToStart_btn, "clicked", G_CALLBACK(on_backtoStart_clicked), loginEmployeeWidgets.window);
    gtk_grid_attach(GTK_GRID(loginEmployeeWidgets.grid), loginEmployeeWidgets.backToStart_btn, 1, 2, 1, 1);
    
    gtk_widget_show_all(loginEmployeeWidgets.window);
    
}

void registerWidget() {
    registerWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(registerWidgets.window), "用户注册界面");
    gtk_window_set_default_size(GTK_WINDOW(registerWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(registerWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(registerWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(registerWidgets.window, "destroy", G_CALLBACK(on_backtoStart_clicked), NULL);

    registerWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(registerWidgets.window), registerWidgets.grid);
    gtk_widget_set_halign(registerWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(registerWidgets.grid, GTK_ALIGN_CENTER);

    registerWidgets.username_label = gtk_label_new("用户名：");
    gtk_grid_attach(GTK_GRID(registerWidgets.grid), registerWidgets.username_label, 0, 0, 1, 1);
    registerWidgets.username_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(registerWidgets.grid), registerWidgets.username_entry, 1, 0, 1, 1);
    
    registerWidgets.password_label = gtk_label_new("密码： ");
    gtk_grid_attach(GTK_GRID(registerWidgets.grid),registerWidgets.password_label,0,1,1,1);
    registerWidgets.password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(registerWidgets.password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(registerWidgets.grid), registerWidgets.password_entry, 1, 1, 2, 1);
    
    registerWidgets.confirmRegister_btn = gtk_button_new_with_label("确认注册");
    g_signal_connect(registerWidgets.confirmRegister_btn, "clicked", G_CALLBACK(on_confirm_Register_clicked), NULL);
    gtk_grid_attach(GTK_GRID(registerWidgets.grid), registerWidgets.confirmRegister_btn, 0, 2, 1, 1);
    
    registerWidgets.backToStart_btn = gtk_button_new_with_label("返回开始界面");
    g_signal_connect(registerWidgets.backToStart_btn, "clicked", G_CALLBACK(on_backtoStart_clicked), registerWidgets.window);
    gtk_grid_attach(GTK_GRID(registerWidgets.grid), registerWidgets.backToStart_btn, 1, 2, 1, 1);
    
    gtk_widget_show_all(registerWidgets.window);
}

bool verify(const char *username, const char *password) {
    FILE *file;
    char line[MAX_LENGTH * 3];
    const char *delimiter = "|||";
    char *delimiter_pos;

    file = fopen("user.csv", "r");
    if (!file) {
        perror("打开文件失败");
        return false;
    }

    while (fgets(line, sizeof(line), file)) {
        char file_username[MAX_LENGTH], file_password[MAX_LENGTH];

        // 找到分隔符位置
        delimiter_pos = strstr(line, delimiter);
        if (delimiter_pos) {
            // 从行中提取用户名
            *delimiter_pos = '\0';  // 切断字符串，结束用户名部分
            strncpy(file_username, line, MAX_LENGTH - 1);
            file_username[MAX_LENGTH - 1] = '\0';

            // 提取密码，跳过分隔符
            strncpy(file_password, delimiter_pos + strlen(delimiter), MAX_LENGTH - 1);
            file_password[MAX_LENGTH - 1] = '\0';

            // 删除密码末尾的可能的换行符
            file_password[strcspn(file_password, "\n")] = '\0';

            // 比较用户名和密码
            if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
                fclose(file);
                return true; // 找到匹配项
            }
        }
    }

    fclose(file);
    return false; // 未找到匹配项
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
    gtk_widget_destroy(startWidgets.window);
    printf("程序已退出。\n");
    exit(0);
}


static void on_confirm_loginManager_clicked(GtkWidget *widget, gpointer data) {
    if(!loginManagerWidgets.chance) {
        printf("尝试使用密钥登录失败，系统关闭。\n");
        exit(0);
    }
    const char *password_const = gtk_entry_get_text(GTK_ENTRY(loginManagerWidgets.password_entry));
    char password[MAX_LENGTH];
    strncpy(password,password_const,MAX_LENGTH);
    password[strcspn(password, "\n")] = 0;
    if(isSameString(password, SECRET_KEY) || DEBUG_MODE) {
        printf("登录成功！欢迎, 经理!\n");
        strcpy(User, "Manager");
        IsManager = true;
        managerMenuWidget();
    } else {
        loginManagerWidgets.chance--;
        printf("登录失败，密码错误。还剩下%d次机会。\n", loginManagerWidgets.chance);
    }
}
static void on_backtoStart_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_show(startWidgets.window);
    gtk_widget_destroy(GTK_WIDGET(data));  
}

static void on_confirm_loginEmployee_clicked(GtkWidget *widget, gpointer data) {
    char encryptedPassword[MAX_LENGTH * 2];
    const char *username_const = gtk_entry_get_text(GTK_ENTRY(registerWidgets.username_entry));
    const char *password_const = gtk_entry_get_text(GTK_ENTRY(registerWidgets.password_entry));
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];

    strncpy(username,username_const,MAX_LENGTH);
    username[strcspn(username, "\n")] = 0;
    strncpy(password,password_const,MAX_LENGTH);
    password[strcspn(password, "\n")] = 0;
    
    xorEncryptDecrypt(password, strlen(password), encryptedPassword); // 加密用户密码

    system(SYSTEM_CLEAR);

    // 验证登录
    if (verify(username, encryptedPassword) || DEBUG_MODE) {
        printf("登录成功！欢迎, %s!\n", username);
        strcpy(User, username);
        IsManager = false;
        employeeMenuWidget();
        return;
    } else {
        printf("登录失败，用户名或密码错误。\n");
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
        addEntry(1, "employees.csv", "请输入业务员姓名：", &newEmployee, NULL, NULL);
        saveEmployeeToFile(newEmployee);
        displayEmployee(newEmployee);
    }
    system(SYSTEM_CLEAR);
}

// end login.c