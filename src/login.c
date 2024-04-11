#include "header.h"

#define CREDENTIALS_FILE "credentials.ini"

#define MANAGER_SECTION "Manager"
#define EMPLOYEE_SECTION "Employee"
#define SECRET_KEY "secret_key_secret_key_secret_key_secret_key_secret_key"

void initializeCredentialsFile();
bool verifyLogin(string username, string password, string section);
void xorEncryptDecrypt(string input, size_t length);
void registerUser();
void login();

void initializeCredentialsFile() {
    FILE *file = fopen(CREDENTIALS_FILE, "r");
    if (!file) {
        // 文件不存在，创建新文件
        printf("凭据文件未找到，将创建新文件。\n");
        file = fopen(CREDENTIALS_FILE, "w");
        if (!file) {
            perror("创建新凭据文件失败");
            exit(EXIT_FAILURE);
        }
        // 可以选择在这里写入一些初始数据
        fprintf(file, "[Manager]\n");
        fprintf(file, "[Employee]\n");
        fclose(file);
    } else {
        // 文件已存在，只关闭文件流
        fclose(file);
    }
}

bool verifyLogin(string username, string password, string section) {
    string line;
    string sectionHeader;
    sprintf(sectionHeader, "[%s]", section); // 格式化section头字符串
    bool isInSection = false;
    bool userFound = false;

    initializeCredentialsFile();

    FILE *file = fopen(CREDENTIALS_FILE, "r");
    if (!file) {
        perror("无法打开新创建的凭据文件");
        return false;
    }

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; // 去除换行符

        // 检查是否是我们需要的section头
        if (strncmp(line, sectionHeader, strlen(sectionHeader)) == 0) {
            isInSection = true;
            continue;
        }

        // 检查是否是其他section的头，如果是则跳出循环
        if (isInSection && line[0] == '[') {
            break;
        }

        if (isInSection) {
            char *file_username = strtok(line, "=");
            char *file_password = strtok(NULL, "\n");

            if (file_username && file_password) {
                if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
                    userFound = true;
                    break;
                }
            }
        }
    }

    fclose(file);
    return userFound;
}


void xorEncryptDecrypt(string input, size_t length) {
    string encryptionKey;
    strcpy(encryptionKey, SECRET_KEY);
    size_t key_length = strlen(encryptionKey);
    for (size_t i = 0; i < length; ++i) {
        input[i] ^= encryptionKey[i % key_length];
    }
    input[length] = '\0'; // 确保输出是以null结尾的字符串
}

void registerUser() {
    string username, password, role;
    string section = "";  // 初始化为空字符串
    FILE *file;

    printf("创建新用户.\n");
    while (getchar() != '\n'); // 清空缓冲区

    printf("请输入用户名：");
    fgets(username, MAX_LENGTH, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("请输入密码：");
    fgets(password, MAX_LENGTH, stdin);
    password[strcspn(password, "\n")] = 0;
    xorEncryptDecrypt(password, strlen(password)); // 加密密码

    printf("请选择角色：\n");
    printf("1. 公司经理\n");
    printf("2. 公司业务员\n");
    printf("请输入角色数字（1-2）：");
    fgets(role, MAX_LENGTH, stdin);
    role[strcspn(role, "\n")] = 0;
    system(SYSTEM_CLEAR);

    if (strcmp(role, "1") == 0) {
        strcpy(section, "[Manager]");
    } else if (strcmp(role, "2") == 0) {
        strcpy(section, "[Employee]");
    } else {
        printf("无效角色. 返回登录菜单.\n");
        return;
    }

    file = fopen(CREDENTIALS_FILE, "a"); // 以追加模式打开文件
    if (!file) {
        perror("无法打开凭据文件进行写入");
        return;
    }

    fprintf(file, "%s=%s\n", username, password); // 写入新的用户信息
    fclose(file);

    printf("用户注册成功.\n");
}



void login() {
    while (true) {
        bool flag = false;
        string username;
        string password;
        string section;

        printf("请选择角色：\n");
        printf("1. 公司经理\n");
        printf("2. 公司业务员\n");
        printf("3. 注册用户\n");
        printf("4. 退出程序\n");
        printf("请输入选择的角色数字（1-4）：");
        string role;
        scanf("%254s", role);
        system(SYSTEM_CLEAR);

        if (strlen(role) != 1) {
            printf("无效的选项，请重新选择。\n");
            continue;  // 继续循环等待有效输入
        }
        switch (role[0]) {
        case '1':
            strcpy(section, "Manager");
            break;
        case '2':
            strcpy(section, "Employee");
            break;
        case '3':
            registerUser();
            flag = true;
            break;
        case '4':
            printf("程序已退出。\n");
            exit(0);
        default:
            printf("无效的选项，请重新选择。\n");
            flag = true;
        }
        if (flag) {
            continue;
        }

        while (getchar() != '\n');

        // 获取用户输入
        printf("请输入用户名：");
        fgets(username, MAX_LENGTH, stdin);
        username[strcspn(username, "\n")] = 0; // 去除fgets捕获的换行符

        printf("请输入密码：");
        fgets(password, MAX_LENGTH, stdin);
        password[strcspn(password, "\n")] = 0; // 去除fgets捕获的换行符
        xorEncryptDecrypt(password, strlen(password)); // 加密用户密码
        system(SYSTEM_CLEAR);

        // 验证登录
        if (verifyLogin(username, password, section)) {
            printf("登录成功！欢迎, %s!\n", username);
            return;
        } else {
            printf("登录失败，用户名或密码错误。\n");
        }
    }
}


