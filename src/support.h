// support.h

// 全局函数
bool isEmpty(const char *input);
void clearBuffer();
void getInput(char *input, int buffer_size);
void xorEncryptDecrypt(const char *input, size_t length, char *output);
bool matchRegex(const char *password);

// 检验输入是否为空
bool isEmpty(const char *input) {
    return (strlen(input) == 0);
}

bool isOneChar(const char *input) {
    return (strlen(input) == 1);
}

// 清除缓冲区
void clearBuffer() {
    while (getchar() != '\n');
}

// 获取字符串
void getInput(char *input, int buffer_size) {
    if (fgets(input, buffer_size, stdin) != NULL) {
        input[strcspn(input, "\n")] = 0; // 去除 fgets 捕获的换行符
    } else {
        fprintf(stderr, "Error reading input.\n");
    }
}

// 是相同的字符串
bool isSameString(const char *str1, const char *str2) {
    return (strcmp(str1, str2) == 0);
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
