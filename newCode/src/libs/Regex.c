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

// 检查程度的正则表达式
bool matchScale(const char *scale) {
    // 检查是否为空字符串，因为输入不能是空的
    if (scale == NULL || scale[0] == '\0') return false;

    // 比较输入是否为 "大"、"中" 或 "小"
    return (strcmp(scale, "大") == 0 || strcmp(scale, "中") == 0 || strcmp(scale, "小") == 0);
}

// 检查等级的正则表达式
bool matchContactLevel(const char *contactLevel) {
    // 检查是否为空字符串，因为输入不能是空的
    if (contactLevel == NULL || contactLevel[0] == '\0') return false;

    // 比较输入是否为 "高"、"中" 或 "低"
    return (strcmp(contactLevel, "高") == 0 || strcmp(contactLevel, "中") == 0 || strcmp(contactLevel, "低") == 0);
}

// 检查日期的正则表达式
bool matchDate(const char *date) {
    regex_t regex;
    int ret;
    char msgbuf[100];

    // YYYY-MM-DD
    ret = regcomp(&regex, "^[0-9]{4}-[0-9]{2}-[0-9]{2}$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    ret = regexec(&regex, date, 0, NULL, 0);
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

// 检查日期时间的正则表达式
bool matchTime(const char *time) {
    regex_t regex;
    int ret;
    char msgbuf[100];

    // HH:MM:SS
    ret = regcomp(&regex, "^[0-2][0-9]:[0-5][0-9]:[0-5][0-9]$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex for time\n");
        return false;
    }

    ret = regexec(&regex, time, 0, NULL, 0);
    regfree(&regex);  // 释放正则表达式
    if (!ret) {
        if (atoi(time) < 24) { // 验证小时部分是否小于24
            return true;
        }
        return false;
    } else if (ret == REG_NOMATCH) {
        return false;
    } else {
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return false;
    }
}

// 检查持续时间的正则表达式
bool matchDuration(const char *duration) {
    regex_t regex;
    int ret;
    char msgbuf[100];

    // 编译正则表达式
    ret = regcomp(&regex, "^[0-9]+(\\.[0-9]+)?$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex for duration\n");
        return false;
    }

    // 执行匹配
    ret = regexec(&regex, duration, 0, NULL, 0);
    regfree(&regex);  // 释放正则表达式
    if (ret == 0) {
        return true; // 匹配成功
    } else {
        return false; // 匹配失败
    }
}
