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

// 添加新的用户实例
void addEntry(int section, const char *filename, const char *prompt, Employee *employee, Customer *customer, ContactPerson *contact) {
    char userName[MAX_LENGTH];
    char gender[MAX_LENGTH];
    char birthday[MAX_LENGTH];
    char email[MAX_LENGTH];
    char phone[MAX_LENGTH];

    while (true) {
        inputTheName(userName, sizeof(userName), prompt);
        if (!alreadyExists(filename, userName)) {
            break;
        } else {
            printf("姓名已存在，请重新输入。\n");
        }
    }

    if (section == 2) {
        infoInput(customer->region, sizeof(customer->region), "输入客户所在区域: ");
        infoInput(customer->address, sizeof(customer->address), "输入客户地址: ");
        infoInput(customer->legalRepresentative, sizeof(customer->legalRepresentative), "输入客户公司法人: ");
        infoInput(customer->scale, sizeof(customer->scale), "输入客户规模（大、中、小）: ");
        infoInput(customer->businessContactLevel, sizeof(customer->businessContactLevel), "输入与本公司业务联系程度（高、中、低）: ");
    } else { // section == 1 || section == 3
        infoInput(gender, sizeof(gender), "输入业性别: ");
        infoInput(birthday, sizeof(birthday), "输入生日: ");
    }

    while (true) {
        infoInput(email, sizeof(email), "输入客户电子邮件: ");
        if (isSameString(email, " ") || matchMail(email)) {
            break;
        } else {
            printf("电子邮件格式不正确，请重新输入。\n");
        }
    }

    while (true) {
        infoInput(phone, sizeof(phone), "输入客户电话: ");
        if (isSameString(phone, " ") || matchPhone(phone)) {
            break;
        } else {
            printf("电话号码格式不正确，请重新输入。\n");
        }
    }

    switch (section) {
    case 1:
        strcpy(employee->name, userName);
        strcpy(employee->email, email);
        strcpy(employee->phone, phone);
        infoInput(employee->representative, sizeof(employee->representative), "输入业务员代表的公司: ");
        system(SYSTEM_CLEAR);
        break;
    case 2:
        strcpy(customer->name, userName);
        strcpy(customer->email, email);
        strcpy(customer->phone, phone);
        system(SYSTEM_CLEAR);
        break;
    case 3:
        strcpy(contact->name, userName);
        strcpy(contact->email, email);
        strcpy(contact->phone, phone);
        infoInput(contact->representative, sizeof(contact->representative), "输入联络员代表的公司: ");
        system(SYSTEM_CLEAR);
        break;
    default:
        return;
    }
}

// 不输出内容的remove
bool removeEntry(const char *filename, const char *delName) {
    char buffer[MAX_LENGTH];
    FILE *fp, *fp_temp;

    fp = fopen(filename, "r");
    if (!fp) {
        printf("无法打开文件 %s\n", filename);
        return false;
    }

    fp_temp = fopen("temp.csv", "w");
    if (!fp_temp) {
        printf("无法创建临时文件\n");
        fclose(fp);
        return false;
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
    return true;
}

// 删除头标题的行
void removeRecord(const char *filename, const char *prompt) {
    char delName[MAX_LENGTH];

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

    if (removeEntry(filename, delName)) {
        printf("记录删除成功。\n");
    } else {
        printf("记录删除失败。\n");
    }
}

