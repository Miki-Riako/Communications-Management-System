// support.h

// 全局函数
bool isEmpty(const char *input);
bool isOneChar(const char *input);
void clearBuffer();
void getInput(char *input, int buffer_size);
void infoInput(char *input, int buffer_size, const char *prompt);
bool isSameString(const char *str1, const char *str2);
void inputTheName(char *name, int buffer_size, const char *prompt);
bool alreadyExists(const char *filename, const char *username);
void initializeInfoFile(const char *path, const char *header);
void removeRecord(const char *filename, const char *prompt);
void xorEncryptDecrypt(const char *input, size_t length, char *output);
bool matchRegex(const char *password);
bool matchMail(const char *email);
bool matchPhone(const char *phone);

// 检验输入是否为空
bool isEmpty(const char *input) { return (input[0] == '\0'); }

// 检验输入是否为单个字符
bool isOneChar(const char *input) { return (strlen(input) == 1); }

// 清除缓冲区
void clearBuffer() { while (getchar() != '\n'); }

// 获取字符串
void getInput(char *input, int buffer_size) {
    if (fgets(input, buffer_size, stdin) != NULL) {
        input[strcspn(input, "\n")] = 0; // 去除 fgets 捕获的换行符
    } else {
        fprintf(stderr, "Error reading input.\n");
    }
}

// 信息写入
void infoInput(char *input, int buffer_size, const char *prompt) {
    printf("%s", prompt);
    if (fgets(input, buffer_size, stdin) == NULL) {
        printf("错误：无法读取输入。\n");
        strcpy(input, " "); // 安全处理
        return;
    }
    input[strcspn(input, "\n")] = 0;  // 移除尾部的换行符
    if (input[0] == '\0') strcpy(input, " ");
}

// 是相同的字符串
bool isSameString(const char *str1, const char *str2) { return (strcmp(str1, str2) == 0); }

// 输入非空姓名
void inputTheName(char *name, int buffer_size, const char *prompt) {
    while (true) {
        infoInput(name, buffer_size, prompt);
        if (!isSameString(name, " ")) {
            break;
        } else {
            printf("请输入一个有效的名字。\n");
        }
    }
}

// 用户是否已经存在
bool alreadyExists(const char *filename, const char *name) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开文件失败");
        return false;
    }

    char line[MAX_LENGTH * 4];
    bool exists = false;
    while (fgets(line, sizeof(line), file)) {
        char file_username[MAX_LENGTH];
        sscanf(line, "%254[^|||]", file_username);
        if (strcmp(name, file_username) == 0) {
            exists = true;
            break;
        }
    }
    fclose(file);
    return exists;
}

// 初始化创建文件
void initializeInfoFile(const char *path, const char *header) {
    FILE *file = fopen(path, "r");
    if (!file) {
        file = fopen(path, "w");
        if (file) {
            if (!isEmpty(header)) fprintf(file, "%s\n", header);
            fclose(file);
        } else {
            fprintf(stderr, "Error creating file %s\n", path);
        }
    } else {
        fclose(file);
    }
}

// 删除头标题的行
void removeRecord(const char *filename, const char *prompt) {
    char delName[MAX_LENGTH];
    char buffer[MAX_LENGTH];
    FILE *fp, *fp_temp;

    while (true) {
        printf("%s", prompt); // 显示删除提示信息
        getInput(delName, sizeof(delName));
        if (!isEmpty(delName)) {
            if (alreadyExists(filename, delName)) {
                break;
            } else {
                printf("记录不存在！\n");
            }
        } else {
            printf("请输入一个有效的名字。\n");
        }
    }

    fp = fopen(filename, "r");
    if (!fp) {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    fp_temp = fopen("temp.csv", "w");
    if (!fp_temp) {
        printf("无法创建临时文件\n");
        fclose(fp);
        return;
    }

    while (fgets(buffer, MAX_LENGTH, fp) != NULL) {
        // 检查是否包含要删除的用户名
        char* found = strstr(buffer, delName);
        if (found != buffer) { // 确保是从行首开始匹配用户名
            fprintf(fp_temp, "%s", buffer);
        }
    }

    fclose(fp);
    fclose(fp_temp);

    remove(filename);
    rename("temp.csv", filename);

    printf("记录删除成功。\n");
}


// XOR 加密/解密算法
void xorEncryptDecrypt(const char *input, size_t length, char *output) {
    if (input == NULL || output == NULL) {
        fprintf(stderr, "Null pointer passed to xorEncryptDecrypt function.\n");
        return;
    }

    char encryptionKey[MAX_LENGTH];
    strcpy(encryptionKey, SECRET_KEY);
    size_t key_length = strlen(encryptionKey);

    if (key_length == 0) {
        fprintf(stderr, "Encryption key is empty.\n");
        return;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char encrypted_char = input[i] ^ encryptionKey[i % key_length];
        sprintf(output + 2 * i, "%02x", encrypted_char);
    }
    output[2 * length] = '\0'; // 确保输出字符串是以null结尾的
}

// 检验密码的正则表达式
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
        ++password;
    }

    // 检查至少包含两种字符类型
    int count = hasUpper + hasLower + hasDigit + hasPunct;
    return (count >= 2);
}

// 检查邮箱的正则表达式
bool matchMail(const char *email) {
    regex_t regex;
    int ret;
    char msgbuf[100];

    // 编译正则表达式
    ret = regcomp(&regex, "^[A-Za-z0-9]+([.-_][A-Za-z0-9]+)*@[A-Za-z0-9]+([-.][A-Za-z0-9]+)*\\.[A-Za-z]{2,5}$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    // 执行匹配
    ret = regexec(&regex, email, 0, NULL, 0);
    if (!ret) {
        regfree(&regex);
        return true;
    } else if (ret == REG_NOMATCH) {
        regfree(&regex);
        return false;
    } else {
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        regfree(&regex);
        return false;
    }
}

// 检查电话的正则表达式
bool matchPhone(const char *phone) {
    if (phone == NULL) return false;

    while (*phone != '\0') {
        if (!isdigit((unsigned char)*phone) && *phone != '-' && *phone != '+' && *phone != ',') {
            return false;  // 如果字符不是数字也不是连字符，则返回false
        }
        ++phone;
    }
    return true;  // 所有字符都是数字或连字符
}

