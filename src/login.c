#include <gtk/gtk.h>
#include "header.h"  // 确保包含所有必要的声明和常量


#define MANAGER_SECTION "Manager"
#define EMPLOYEE_SECTION "Employee"
#define SECRET_KEY "P@ssw0rdP@ssw0rdP@ssw0rdP@ssw0rdP@ssw0rdP@ssw0rdP@ssw0rdP@ssw0rd"

bool matchRegex(const char *password);
void initializeCredentialsFile();
bool verifyLogin(string username, string password, int section);
void xorEncryptDecrypt(string input, size_t length,string output);
void registerUser();
void login();


bool matchRegex(const char *password) {
    if (strlen(password) < 8) {
        return false;  // 密码长度小于8
    }

    int hasUpper = 0, hasLower = 0, hasDigit = 0, hasPunct = 0;
    while (*password) {
        if (isupper((unsigned char)*password)) hasUpper = 1;
        if (islower((unsigned char)*password)) hasLower = 1;
        if (isdigit((unsigned char)*password)) hasDigit = 1;
        if (ispunct((unsigned char)*password)) hasPunct = 1;
        password++;
    }

    // 检查至少包含两种字符类型
    int count = hasUpper + hasLower + hasDigit + hasPunct;
    return (count >= 2);
}

void initializeCredentialsFile() {
    FILE *file;

    // 检查并初始化 managers.csv 文件
    file = fopen("managers.csv", "r");
    if (!file) {
        // 文件不存在，创建新文件
        file = fopen("managers.csv", "w");
        if (!file) {
            perror("创建 managers.csv 文件失败");
        } else {
            fprintf(file, "user|||password\n");
            fclose(file);
        }
    } else {
        // 文件已存在，只关闭文件流
        fclose(file);
    }

    // 检查并初始化 employees.csv 文件
    file = fopen("employees.csv", "r");
    if (!file) {
        // 文件不存在，创建新文件
        file = fopen("employees.csv", "w");
        if (!file) {
            perror("创建 employees.csv 文件失败");
        } else {
            fprintf(file, "user|||password\n");
            fclose(file);
        }
    } else {
        // 文件已存在，只关闭文件流
        fclose(file);
    }
}

bool verifyLogin(string username, string password, int section) {
    FILE *file;
    char line[512];
    const char *filename = (section == 1) ? "managers.csv" : "employees.csv";
    const char *delimiter = "|||";
    char *delimiter_pos;

    file = fopen(filename, "r");
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

// XOR 加密/解密算法
void xorEncryptDecrypt(string input, size_t length,string output) {
    string encryptionKey;
    strcpy(encryptionKey, SECRET_KEY);
    size_t key_length = strlen(encryptionKey);

    if (key_length == 0) {
        fprintf(stderr, "Encryption key is empty.\n");
        return;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char encrypted_char = input[i] ^ encryptionKey[i % key_length];
        sprintf(output + 2 * i, "%02x", encrypted_char);  // 将每个加密字节转换为两个十六进制字符
    }
    output[2 * length] = '\0'; // 确保输出字符串是以null结尾的
}



// 定义全局变量以方便在不同函数间共享窗口部件
typedef struct {
    GtkWidget *window;
    GtkWidget *username_entry;
    GtkWidget *password_entry;
    GtkWidget *role_combo;
} AppWidgets;

AppWidgets login_widgets, register_widgets;

static void on_login_clicked(GtkWidget *widget, gpointer data);
static void on_register_clicked(GtkWidget *widget, gpointer data);
static void on_register_user_clicked(GtkWidget *widget, gpointer data);
static void create_register_window();

// 检查用户名是否已存在
static bool checkUserExists(const char *filename, const char *username) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("无法打开文件");
        return false;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        char *delimiter_pos = strstr(line, "|||");
        if (delimiter_pos) {
            *delimiter_pos = '\0';  // 分隔用户名和密码
            if (strcmp(line, username) == 0) {
                fclose(file);
                return true;  // 用户已存在
            }
        }
    }

    fclose(file);
    return false;
}

// 存储账户信息
bool storeUserData(const char *username, const char *password, int section) {
    const char *filename = (section == 1) ? "managers.csv" : "employees.csv";
    printf("Storing encrypted password: %s\n", password); // Debug: 打印加密后的密码检查
    // 检查用户是否已存在
    if (checkUserExists(filename, username)) {
        return false;  // 用户名已存在
    }

    // 打开文件以追加新用户
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("无法打开文件进行写入");
        return false;
    }

    // 写入用户名和密码
    fprintf(file, "%s|||%s\n", username, password);
    fclose(file);
    return true;
}

// 创建登录窗口
void login() {
    gtk_init(NULL, NULL);
    initializeCredentialsFile();

    login_widgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(login_widgets.window), "登录界面");
    gtk_window_set_default_size(GTK_WINDOW(login_widgets.window), 300, 200);
    gtk_container_set_border_width(GTK_CONTAINER(login_widgets.window), 10);
    g_signal_connect(login_widgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(login_widgets.window), grid);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);
    
    GtkWidget *username_label = gtk_label_new("用户名:");
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);
    login_widgets.username_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), login_widgets.username_entry, 1, 0, 1, 1);

    GtkWidget *password_label = gtk_label_new("密码:");
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);
    login_widgets.password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(login_widgets.password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), login_widgets.password_entry, 1, 1, 1, 1);

    GtkWidget *role_label = gtk_label_new("角色:");
    gtk_grid_attach(GTK_GRID(grid), role_label, 0, 2, 1, 1);
    login_widgets.role_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(login_widgets.role_combo), "经理");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(login_widgets.role_combo), "业务员");
    gtk_combo_box_set_active(GTK_COMBO_BOX(login_widgets.role_combo), 0);
    gtk_grid_attach(GTK_GRID(grid), login_widgets.role_combo, 1, 2, 1, 1);

    GtkWidget *login_button = gtk_button_new_with_label("登录");
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), login_button, 0, 3, 2, 1);

    GtkWidget *register_button = gtk_button_new_with_label("注册新用户");
    g_signal_connect(register_button, "clicked", G_CALLBACK(on_register_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), register_button, 0, 4, 2, 1);

    gtk_widget_show_all(login_widgets.window);
    gtk_main();
}

// 登录按钮事件处理
static void on_login_clicked(GtkWidget *widget, gpointer data) {
    const char *username_const = gtk_entry_get_text(GTK_ENTRY(login_widgets.username_entry));
    const char *password_const = gtk_entry_get_text(GTK_ENTRY(login_widgets.password_entry));
    char *password = g_strdup(password_const);
    // 检查用户名和密码是否为空
    if (!username_const || !*username_const || !password_const || !*password_const) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(login_widgets.window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "用户名和密码不能为空。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    const char *role = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(login_widgets.role_combo));
    int section = g_strcmp0(role, "经理") == 0 ? 1 : 2;
    string encrypted_password;
    xorEncryptDecrypt(password, strlen(password_const),encrypted_password);  // 加密密码
    if (verifyLogin((char*)username_const, encrypted_password,section)) {
        g_print("登录成功！欢迎, %s!\n", username_const);
        gtk_widget_destroy(login_widgets.window);
        return;
    } else {
        g_print("登录失败，用户名或密码错误。\n");
    }
}

// 注册按钮事件处理
static void on_register_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_hide(login_widgets.window);
    create_register_window();
}

// 创建注册窗口
static void create_register_window() {
    register_widgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(register_widgets.window), "注册新用户");
    gtk_window_set_default_size(GTK_WINDOW(register_widgets.window), 300, 250);
    gtk_container_set_border_width(GTK_CONTAINER(register_widgets.window), 10);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(register_widgets.window), grid);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(grid, GTK_ALIGN_CENTER);

    GtkWidget *username_label = gtk_label_new("用户名:");
    gtk_grid_attach(GTK_GRID(grid), username_label, 0, 0, 1, 1);
    register_widgets.username_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), register_widgets.username_entry, 1, 0, 1, 1);

    GtkWidget *password_label = gtk_label_new("密码:");
    gtk_grid_attach(GTK_GRID(grid), password_label, 0, 1, 1, 1);
    register_widgets.password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(register_widgets.password_entry), FALSE);
    gtk_grid_attach(GTK_GRID(grid), register_widgets.password_entry, 1, 1, 1, 1);

    GtkWidget *role_label = gtk_label_new("角色:");
    gtk_grid_attach(GTK_GRID(grid), role_label, 0, 2, 1, 1);
    register_widgets.role_combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(register_widgets.role_combo), "经理");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(register_widgets.role_combo), "业务员");
    gtk_combo_box_set_active(GTK_COMBO_BOX(register_widgets.role_combo), 0);
    gtk_grid_attach(GTK_GRID(grid), register_widgets.role_combo, 1, 2, 1, 1);

    GtkWidget *register_button = gtk_button_new_with_label("完成注册");
    g_signal_connect(register_button, "clicked", G_CALLBACK(on_register_user_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), register_button, 0, 3, 2, 1);

    gtk_widget_show_all(register_widgets.window);
}

// 注册用户的事件处理
static void on_register_user_clicked(GtkWidget *widget, gpointer data) {
    const char *username_const = gtk_entry_get_text(GTK_ENTRY(register_widgets.username_entry));
    const char *password_const = gtk_entry_get_text(GTK_ENTRY(register_widgets.password_entry));
    const char *role = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(register_widgets.role_combo));
    int section = g_strcmp0(role, "经理") == 0 ? 1 : 2;

    if (!username_const || !*username_const || !password_const || !*password_const) {
        g_print("用户名和密码不能为空。\n");
        return;
    }
    
    // 创建密码的可修改副本// 创建密码的可修改副本
    char *password = g_strdup(password_const);
    if (!matchRegex(password)) {
        g_print("密码不符合要求。\n");
        return;
    }
    string encrypted_password;
    xorEncryptDecrypt(password, strlen(password),encrypted_password);  // 加密密码
    printf("Storing encrypted password: %s\n", encrypted_password); // Debug: 打印加密后的密码检查
    if (!storeUserData(username_const, encrypted_password, section)) {
        g_print("注册失败，可能是用户名已存在。\n");
    } else {
        g_print("用户注册成功。\n");
        gtk_widget_destroy(register_widgets.window);
        gtk_widget_show(login_widgets.window);
    }
}
