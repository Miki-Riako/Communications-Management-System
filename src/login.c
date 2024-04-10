#include "header.h"

#define CREDENTIALS_FILE "credentials.ini"
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50
#define MAX_CREDENTIALS_LENGTH (MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2)

#define MANAGER_SECTION "Manager"
#define EMPLOYEE_SECTION "Employee"

const unsigned char encryptionKey[] = "secret_key_secret_key_secret_key_secret_key_secret_key";


void promptLogin();
void initializeCredentialsFile();
int verifyLogin(const char* username, const char* encryptedPassword, const char* section);
void xorEncryptDecrypt(unsigned char *input, size_t length, unsigned char *output);
bool login();

void promptLogin() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char encryptedPassword[MAX_PASSWORD_LENGTH + 1];
    int role;

    printf("请选择角色：\n");
    printf("1. 公司经理\n");
    printf("2. 公司业务员\n");
    printf("3. 退出程序\n");
    printf("请输入选择的角色数字（1-3）：");
    scanf("%d", &role);

    if (role == 3) {
        printf("程序已退出。\n");
        exit(0);  // 直接退出程序
    }
    
    const char* section = (role == 1) ? MANAGER_SECTION : EMPLOYEE_SECTION;

    printf("请输入用户名：");
    scanf("%49s", username);
    printf("请输入密码：");
    scanf("%49s", password);

    xorEncryptDecrypt((unsigned char*)password, strlen(password), encryptedPassword);

    if (verifyLogin(username, (const char*)encryptedPassword, section)) {
        printf("登录成功！\n");
    } else {
        printf("登录失败，用户名或密码错误。\n");
    }
}

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

int verifyLogin(const char* username, const char* encryptedPassword, const char* section) {
    char line[MAX_CREDENTIALS_LENGTH];
    char sectionHeader[50];
    sprintf(sectionHeader, "[%s]", section); // 格式化section头字符串
    int isInSection = 0;
    int userFound = 0;

    FILE *file = fopen(CREDENTIALS_FILE, "r");
    if (!file) {
        initializeCredentialsFile();
        file = fopen(CREDENTIALS_FILE, "r"); // 重新打开新创建的文件
        if (!file) {
            perror("无法打开新创建的凭据文件");
            return 0;
        }
    }

    while (fgets(line, sizeof(line), file)) {
        // 去除换行符
        line[strcspn(line, "\n")] = 0;

        // 检查是否是我们需要的section头
        if (strncmp(line, sectionHeader, strlen(sectionHeader)) == 0) {
            isInSection = 1;
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
                // 使用异或加密对文件中的密码进行解密
                unsigned char decryptedPassword[MAX_PASSWORD_LENGTH + 1];
                xorEncryptDecrypt((unsigned char*)file_password, strlen(file_password), decryptedPassword);

                // 比较用户名和密码
                if (strcmp(username, file_username) == 0 && strcmp(encryptedPassword, (char*)decryptedPassword) == 0) {
                    userFound = 1;
                    break;
                }
            }
        }
    }

    fclose(file);
    return userFound;
}


void xorEncryptDecrypt(unsigned char *input, size_t length, unsigned char *output) {
    size_t key_length = strlen((const char *)encryptionKey);
    for (size_t i = 0; i < length; ++i) {
        output[i] = input[i] ^ encryptionKey[i % key_length];
    }
    output[length] = '\0'; // 确保输出是以null结尾的字符串
}

bool login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    unsigned char encryptedPassword[MAX_PASSWORD_LENGTH + 1];
    int role;

    printf("请选择角色：\n");
    printf("1. 公司经理\n");
    printf("2. 公司业务员\n");
    printf("3. 退出程序\n");
    printf("请输入选择的角色数字（1-3）：");
    scanf("%d", &role);

    if (role == 3) {
        printf("程序已退出。\n");
        exit(0);  // 直接退出程序
    }
    
    const char* section = (role == 1) ? MANAGER_SECTION : EMPLOYEE_SECTION;
    
    // 清空缓冲区以防止输入问题
    while (getchar() != '\n');

    // 确定角色对应的部分名称
    section = (role == 1) ? MANAGER_SECTION : EMPLOYEE_SECTION;

    // 获取用户输入
    printf("请输入用户名：");
    fgets(username, MAX_USERNAME_LENGTH, stdin);
    // 去除fgets捕获的换行符
    username[strcspn(username, "\n")] = 0;

    printf("请输入密码：");
    // 密码应该隐藏起来，这里为了演示简便就直接输入了
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    // 去除fgets捕获的换行符
    password[strcspn(password, "\n")] = 0;

    // 加密用户密码
    xorEncryptDecrypt((unsigned char*)password, strlen(password), encryptedPassword);

    // 验证登录
    if (verifyLogin(username, (const char*)encryptedPassword, section)) {
        printf("登录成功！欢迎, %s!\n", username);
        return true;
    } else {
        printf("登录失败，用户名或密码错误。\n");
        return false;
    }
}


