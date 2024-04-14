// login.c
#include "header.h"

#define MANAGER_SECTION "Manager"
#define EMPLOYEE_SECTION "Employee"
#define SECRET_KEY "secret_key_secret_key_secret_key_secret_key_secret_key"

bool matchRegex(const char *password);
void initializeCredentialsFile();
bool verifyLogin(string username, string password, int section);
void xorEncryptDecrypt(string input, size_t length, string output);
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
void xorEncryptDecrypt(string input, size_t length, string output) {
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

void registerUser() {
    FILE *file;
    char line[512];
    string username, password, role;
    int section;

    printf("创建新用户.\n");

    // 清空缓冲区以防止输入问题
    while (getchar() != '\n');

    while (true) {
        printf("请输入用户名：");
        fgets(username, MAX_LENGTH, stdin);
        username[strcspn(username, "\n")] = 0;

        if (strlen(username) = 0) {
            printf("用户名不能为空。\n");
            continue;
        } else {
            break;
        }
    }

    while (true) {
        printf("请输入密码：");
        fgets(password, MAX_LENGTH, stdin);
        password[strcspn(password, "\n")] = 0;

        if (matchRegex(password)) {
            string encryptedPassword;
            xorEncryptDecrypt(password, strlen(password), encryptedPassword); // 加密密码
            break;
        } else {
            printf("密码不符合要求。必须至少8个字符且包含大写字母、小写字母、数字、标点符号中的两种。\n");
        }
    }

    printf("请选择角色：\n");
    printf("1. 公司经理\n");
    printf("2. 公司业务员\n");
    printf("请输入角色数字（1-2）：");
    fgets(role, MAX_LENGTH, stdin);
    role[strcspn(role, "\n")] = 0;
    section = atoi(role);
    system(SYSTEM_CLEAR);

    const char *filename = (section == 1) ? "managers.csv" : "employees.csv";
    file = fopen(filename, "r");
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
    file = fopen(filename, "a");
    if (!file) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s|||%s\n", username, password); // 写入新的用户信息
    fclose(file);

    printf("用户注册成功.\n");
}

void login() {
    initializeCredentialsFile();
    while (true) {
        bool flag = false;
        string username;
        string password;
        int section = 0;

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
            section = 1;
            break;
        case '2':
            section = 2;
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

        string encryptedPassword;
        xorEncryptDecrypt(password, strlen(password), encryptedPassword); // 加密用户密码
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


