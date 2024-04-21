// 检验输入是否为空
bool isEmpty(const char *input) { return (input[0] == '\0'); }

// 检验输入是否为单个字符
bool isOneChar(const char *input) { return (strlen(input) == 1); }

// 清除缓冲区
void clearBuffer() { while (getchar() != '\n'); }

// 字符变数字
int charToInt(char c) { return (int)(c - '0'); }

// 获取字符串
void getInput(char *input, int buffer_size) {
    if (fgets(input, buffer_size, stdin) != NULL) {
        input[strcspn(input, "\n")] = 0; // 去除 fgets 捕获的换行符
    } else {
        fprintf(stderr, "读取字符串出错。\n");
    }
}

// 函数用于检查并去除字符串末尾的换行符
void stripNewline(char *str) {
    if (str == NULL) return; // 如果字符串为空，直接返回
    size_t len = strlen(str); // 获取字符串的长度
    if (len > 0 && str[len - 1] == '\n') { // 如果字符串的最后一个字符是换行符
        str[len - 1] = '\0'; // 替换为字符串结束符
    }
}

// 切割函数但是会手动分配内存（少用）
char *splitLine(char *input, const char *delim, int num) {
    int count = 0;
    const char *start = input;
    const char *end = input;

    // 遍历整个字符串
    while (*end != '\0') {
        if (strncmp(end, delim, strlen(delim)) == 0) {
            if (count == num) {
                // 在找到的分割点处截断，返回起始部分
                int length = end - start;
                char *result = malloc(length + 1); // 分配内存
                if (result == NULL) return NULL; // 检查内存分配是否成功
                memcpy(result, start, length); // 复制内容
                result[length] = '\0'; // 设置结束符
                return result;
            }
            ++count; // 增加计数器
            end += strlen(delim); // 跳过分隔符
            start = end; // 更新开始位置
        } else {
            ++end; // 移动到下一个字符
        }
    }

    // 处理最后一段
    if (count == num) {
        return strdup(start); // 返回剩余部分的副本
    }

    return "";
}

// 是相同的字符串
bool isSameString(const char *str1, const char *str2) { return (strcmp(str1, str2) == 0); }

// 这个函数负责去除字段末尾可能的分隔符和空白字符
void cleanField(char *field) {
    char *end = field + strlen(field) - 1;
    while (end > field && (isspace((unsigned char)*end) || *end == '|' || *end == '\n' || *end == '\r')) {
        *end = '\0';
        --end;
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
        while (true) {
            infoInput(gender, sizeof(gender), "输入性别: ");
            if (isSameString(gender, " ") || matchGender(gender)) {
                break;
            } else {
                printf("性别格式不正确，请重新输入。\n");
            }
        }
        while (true) {
            infoInput(birthday, sizeof(birthday), "输入生日（YYYY-MM-DD）: ");
            if (isSameString(birthday, " ") || matchDate(birthday)) {
                break;
            } else {
                printf("日期格式不正确，请重新输入。\n");
            }
        }
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
    default:
        printf("无效的选择。\n");
        return -1;
    }
}

// 打印客户信息
void printNode_cus(node_cus *node) {
    printf("%s - %s - %s - %s - %s - %s - %s - %s\n", 
        node->customer.name,
        node->customer.region,
        node->customer.address, 
        node->customer.legalRepresentative,
        node->customer.scale, 
        node->customer.businessContactLevel,
        node->customer.email,
        node->customer.phone
    );
}

// 打印联络人信息
void printNode_ctp(node_ctp *node) {
    printf("%s - %s - %s - %s - %s - %s\n", 
        node->contactPerson.name,
        node->contactPerson.gender,
        node->contactPerson.birthday, 
        node->contactPerson.email,
        node->contactPerson.phone,
        node->contactPerson.representative
    );
}

// 打印业务员信息
void printNode_emp(node_emp *node) {
    printf("%s - %s - %s - %s - %s - %s\n", 
        node->employee.name,
        node->employee.gender,
        node->employee.birthday, 
        node->employee.email,
        node->employee.phone,
        node->employee.representative
    );
}

// 打印通信记录信息
void printNode_rec(node_rec *node) {
    printf("%s - %s - %s - %s - %s - %s - %s\n", 
        node->record.user,
        node->record.companyName,
        node->record.contactName,
        node->record.date, 
        node->record.time,
        node->record.duration,
        node->record.content
    );
}

void printHeading(int which) {
    switch (which) {
    case 0:
        printf("客户名 - 地区 - 地址 - 法人 - 规模 - 联系等级 - 邮箱 - 电话\n");
        break;
    case 1:
        printf("联络人名称 - 性别 - 生日 - 邮箱 - 电话 - 代表公司\n");
        break;
    case 2:
        printf("业务员名称 - 性别 - 生日 - 邮箱 - 电话 - 代表公司\n");
        break;
    case 3:
        printf("管理用户 - 公司名称 - 联络人 - 日期 - 时间 - 时长 - 通信内容\n");
        break;
    default:
        break;
    }
}

// 打印需要的链表内容
void printNodeList(head_node *head, int choice) {
    if (head == NULL || head->is_empty) {
        printf("没有可显示的数据。\n");
        return;
    }

    switch (choice) {
    case 0:  // 客户信息
        if (head->is_cus) {
            node_cus *current = head->next_cus;
            printHeading(choice);
            while (current != NULL) {
                printNode_cus(current);
                current = current->next;
            }
        } else {
            printf("没有可显示的客户信息。\n");
        }
        break;
    case 1:  // 联络人信息
        if (head->is_ctp) {
            node_ctp *current = head->next_ctp;
            printHeading(choice);
            while (current != NULL) {
                printNode_ctp(current);
                current = current->next;
            }
        } else {
            printf("没有可显示的联络人信息。\n");
        }
        break;
    case 2:  // 业务员信息
        if (head->is_emp) {
            node_emp *current = head->next_emp;
            printHeading(choice);
            while (current != NULL) {
                printNode_emp(current);
                current = current->next;
            }
        } else {
            printf("没有可显示的业务员信息。\n");
        }
        break;
    case 3:  // 通信记录
        if (head->is_rec) {
            node_rec *current = head->next_rec;
            printHeading(choice);
            while (current != NULL) {
                printNode_rec(current);
                current = current->next;
            }
        } else {
            printf("没有可显示的通信记录信息。\n");
        }
        break;
    default:
        printf("无效的选项。\n");
        break;
    }
}

int selectSearchAttribute(int which) {
    char index = '0';
    switch (which) {
    case 0: // 客户
        printf("1. 名称\n2. 地区\n3. 地址\n4. 法人\n5. 规模\n6. 联系等级\n7. 邮箱\n8. 电话\n");
        index = '8';
        break;
    case 1: // 联络人
    case 2: // 业务员
        printf("1. 名称\n2. 性别\n3. 生日\n4. 邮箱\n5. 电话\n6. 代表公司\n");
        index = '6';
        break;
    case 3: // 通信记录
        printf("1. 管理用户\n2. 公司名称\n3. 联络人\n4. 日期\n5. 时间\n6. 时长\n7. 通信内容\n");
        index = '7';
    default: break;
    }
    char get[MAX_LENGTH];
    infoInput(get, sizeof(get), "请选择属性：\n");
    if (!isOneChar(get) || get[0] < '1' || get[0] > index) {
        printf("无效的选择\n");
        return -1;
    } else {
        return charToInt(get[0]) - 1;
    }
}
