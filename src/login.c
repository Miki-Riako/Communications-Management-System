// login.c
#include "header.h"
#include "menu.c"

void startWidget();
void loginManagerWidget();
void loginEmployeeWidget();
void registerWidget();
bool verify(const char *username, const char *password);

void startWidget() {
    initializeInfoFile("user.csv", "");
    while (true) {
        printf("登入中...\n");
        printf("请选择角色：\n");
        printf("1. 公司经理\n");
        printf("2. 公司业务员\n");
        printf("3. 注册业务员\n");
        printf("4. 退出程序\n");
        printf("请输入选择的角色数字（1-4）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);

        if (!isOneChar(get)) {
            printf("无效的选项，请重新选择。\n");
            continue;  // 继续循环等待有效输入
        }
        switch (get[0]) {
        case '1':
            loginManagerWidget();
            break;
        case '2':
            loginEmployeeWidget();
            break;
        case '3':
            registerWidget();
            break;
        case '4':
            printf("程序已退出。\n");
            exit(0);
        default:
            printf("无效的选项，请重新选择。\n");
        }
    }
}

void loginManagerWidget() {
    for (int i = 0; i < 3; ++i) {
        char password[MAX_LENGTH];

        printf("请输入公司密钥：");
        getInput(password, sizeof(password));

        system(SYSTEM_CLEAR);
        if (isSameString(password, SECRET_KEY) || DEBUG_MODE) {
            printf("登录成功！欢迎, 经理!\n");
            strcpy(User, "Manager");
            IsManager = true;
            managerMenuWidget();
            return;
        } else {
            printf("登录失败，密码错误。还剩下%d次机会。\n", 3 - i);
        }
    }
    printf("尝试使用密钥登录失败，系统关闭。\n");
    exit(0);
}

void loginEmployeeWidget() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char encryptedPassword[MAX_LENGTH * 2];

    // 获取用户输入
    printf("请输入用户名：");
    getInput(username, sizeof(username));

    printf("请输入密码：");
    getInput(password, sizeof(password));
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

void registerWidget() {
    FILE *file;
    char line[MAX_LENGTH * 3];
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    char encryptedPassword[MAX_LENGTH * 2];
    char role[MAX_LENGTH];

    printf("创建新用户.\n");

    while (true) {
        printf("请输入用户名：");
        getInput(username, sizeof(username));

        if (isEmpty(username)) {
            printf("用户名不能为空。\n");
            continue;
        } else {
            break;
        }
    }

    while (true) {
        printf("请输入密码：");
        getInput(password, sizeof(password));

        if (matchRegex(password)) {
            xorEncryptDecrypt(password, strlen(password), encryptedPassword);
            break;
        } else {
            printf("密码不符合要求。必须至少8个字符且包含大写字母、小写字母、数字、标点符号中的两种。\n");
        }
    }

    file = fopen("user.csv", "r");
    if (!file) {
        perror("打开文件失败");
        return;
    }

    // 检查用户名是否已存在
    bool userExists = false;
    while (fgets(line, sizeof(line), file)) {
        char file_username[MAX_LENGTH];
        sscanf(line, "%254[^|||]", file_username);
        if (strcmp(username, file_username) == 0) {
            userExists = true;
            break;
        }
    }
    fclose(file);

    if (userExists) {
        printf("用户已存在.\n");
        return;
    }

    // 用户不存在，添加新用户
    file = fopen("user.csv", "a");
    if (!file) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s|||%s\n", username, encryptedPassword); // 写入新的用户信息
    fclose(file);

    printf("用户注册成功.\n");
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

// end login.c