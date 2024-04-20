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
        fprintf(stderr, "读取字符串出错。\n");
    }
}

// 是相同的字符串
bool isSameString(const char *str1, const char *str2) { return (strcmp(str1, str2) == 0); }

// 这个函数负责去除字段末尾可能的分隔符和空白字符
void cleanField(char *field) {
    char *end = field + strlen(field) - 1;
    while (end > field && (isspace((unsigned char)*end) || *end == '|' || *end == '\n' || *end == '\r')) {
        *end = '\0';
        end--;
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
    if (isEmpty(input)) strcpy(input, " ");
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
        while (true) {
            infoInput(customer->scale, sizeof(customer->scale), "输入客户规模（大、中、小）: ");
            if (isSameString(customer->scale, " ") || matchScale(customer->scale)) {
                break;
            } else {
                printf("客户规模格式不正确，请重新输入。\n");
            }
        }
        while (true) {
            infoInput(customer->businessContactLevel, sizeof(customer->businessContactLevel), "输入与本公司业务联系程度（高、中、低）: ");
            if (isSameString(customer->businessContactLevel, " ") || matchContactLevel(customer->businessContactLevel)) {
                break;
            } else {
                printf("客户业务联系程度格式不正确，请重新输入。\n");
            }
        }
    } else { // section == 1 || section == 3
        infoInput(gender, sizeof(gender), "输入性别: ");
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
        strcpy(employee->gender, gender);
        strcpy(employee->birthday, birthday);
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
        strcpy(contact->gender, gender);
        strcpy(contact->birthday, birthday);
        strcpy(contact->email, email);
        strcpy(contact->phone, phone);
        infoInput(contact->representative, sizeof(contact->representative), "输入联络员代表的公司: ");
        system(SYSTEM_CLEAR);
        break;
    default:
        return;
    }
}

// 增加后一列
void addColumn(char *fullLine, const char *newOne) {
    strcat(fullLine, "|||");
    strcat(fullLine, newOne);
}

// 显示一个小菜单
int beforeInfo(head_node *head, const char *prompt) {
    char get[MAX_LENGTH];
    if (IsManager) {
        printf("请选择%s的数据类型：\n", prompt);
        printf("1. 客户\n");
        printf("2. 联络人\n");
        printf("3. 业务员\n");
        printf("输入选项：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);
        
        if (!isOneChar(get)) {
            printf("无效的选择\n");
            return -1;
        }
    } else {
        get[0] = '1';
    }

    switch (get[0]) {
    case '1':
        if (head->is_cus) {
            return 0;
        } else {
            printf("无法%s客户信息。\n", prompt);
            return -1;
        }
    case '2':
        if (IsManager && head->is_ctp) {
            return 1;
        } else {
            printf("无法%s联络人信息。\n", prompt);
            return -1;
        }
    case '3':
        if (IsManager && head->is_emp) {
            return 2;
        } else {
            printf("无法%s业务员信息。\n", prompt);
            return -1;
        }
    // case '4':
    //     if (IsManager && head->is_rec) {
    //         return 3;
    //     } else {
    //         printf("无法%s记录信息。\n", prompt);
    //         return -1;
    //     }
    default:
        printf("无效的选择。\n");
        return -1;
    }
}
