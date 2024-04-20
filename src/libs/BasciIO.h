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

// 某行是否存在
bool lineExists(const char *filename, const char *lineToCheck) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开文件失败");
        return false;
    }

    char line[MAX_LENGTH * 4];
    bool exists = false;
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(lineToCheck, line) == 0) {
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
            fprintf(stderr, "创建文件 %s 出现错误。\n", path);
        }
    } else {
        fclose(file);
    }
}

// 不输出内容的remove
bool removeEntry(const char *filename, const char *delName) {
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

    char buffer[MAX_LENGTH];
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

// 将一行写入一个文件
void writeLineToFile(const char *filename, const char *data) {
    FILE *file = fopen(filename, "a"); // 以追加模式打开文件
    if (!file) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s\n", data);
    fclose(file);
}

// 将一行删除
bool removeLineInFile(const char *filename, const char *data) {
    bool found = false;
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开文件失败");
        return false;
    }

    // 创建一个临时文件
    FILE *tempFile = fopen("temp.csv", "w");
    if (!tempFile) {
        perror("创建临时文件失败");
        fclose(file);
        return false;
    }

    char buffer[8 * MAX_LENGTH];
    while (fgets(buffer, sizeof(buffer), file)) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strcmp(buffer, data) != 0) {
            fprintf(tempFile, "%s\n", buffer);
        } else {
            found = true;
        }
    }

    fclose(file);
    fclose(tempFile);

    if (remove(filename) != 0) {
        perror("删除原始文件失败");
        return false;
    }

    if (rename("temp.csv", filename) != 0) {
        perror("重命名临时文件失败");
        return false;
    }

    return found;
}

// 从文件中复制行
void copyLine(const char *sourceFilename, const char *destinationFilename, const char *columnName, const char *targetValue) {
    FILE *source = fopen(sourceFilename, "r");
    FILE *destination = fopen(destinationFilename, "a"); // 追加模式打开或创建文件

    if (!source || !destination) {
        perror("文件打开失败");
        if (source) fclose(source);
        if (destination) fclose(destination);
        return;
    }

    char line[MAX_LENGTH * 8];
    int columnIndex = -1;
    char header[MAX_LENGTH * 8];
    if (fgets(line, sizeof(line), source)) { // 读取标题行
        char *token = strtok(line, "|||");
        int currentColumn = 0;
        while (token) {
            if (strcmp(token, columnName) == 0) {
                columnIndex = currentColumn;
                break;
            }
            ++currentColumn;
            token = strtok(NULL, "|||");
        }
    }

    if (columnIndex == -1) {
        // printf("列 '%s' 在文件中未找到。\n", columnName);
    } else {
        while (fgets(line, sizeof(line), source)) {
            char copyOfLine[1024];
            strcpy(copyOfLine, line);  // 复制整行以备后用
            char *values[10];  // 假设列不超过10列
            char *token = strtok(line, "|||");
            int currentColumn = 0;
            while (token && currentColumn < 10) {
                values[currentColumn++] = token;
                token = strtok(NULL, "|||");
            }
            if (currentColumn > columnIndex && strcmp(values[columnIndex], targetValue) == 0) {
                fputs(copyOfLine, destination);  // 将整行写入目标文件
            }
        }
        // printf("已将匹配的行复制到 '%s'。\n", destinationFilename);
    }

    fclose(source);
    fclose(destination);
}

// 复制文件
bool copyFile(const char *sourcePath, const char *destinationPath) {
    FILE *src = fopen(sourcePath, "rb");
    if (!src) {
        perror("打开源文件失败");
        return false;
    }

    FILE *dst = fopen(destinationPath, "wb");
    if (!dst) {
        perror("创建备份文件失败");
        fclose(src);
        return false;
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dst);
    }

    fclose(src);
    fclose(dst);
    return true;
}

// 加载文件至内存层
void loadFile(head_node *head) {
    head->is_empty = true;
    head->is_cus = false;
    head->is_ctp = false;
    head->is_emp = false;
    head->is_rec = false;
    head->next_cus = NULL;
    head->next_ctp = NULL;
    head->next_emp = NULL;
    head->next_rec = NULL;
    if (IsManager) {
        loadCustomers("customers.csv", head);
        loadContactPersons("contacts.csv", head);
        loadEmployees("employees.csv", head);
    }
    // 非管理员只加载其负责的客户数据
    FILE *assignmentsFile = fopen("assignments.csv", "r");
    if (assignmentsFile) {
        char line[5 * MAX_LENGTH];
        while (fgets(line, sizeof(line), assignmentsFile)) {
            char *employee = splitLine(line, "|||", 0);
            char *customer = splitLine(line, "|||", 1);
            if (isSameString(employee, User)) {
                // 找到对应客户，加载其信息
                loadCustomerData("customers.csv", customer, head);
            }
            free(employee);
            free(customer);
        }
        fclose(assignmentsFile);
    }
}

// 实际加载客户数据的函数
void loadCustomerData(const char *filename, const char *customerName, head_node *head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开客户文件失败");
        return;
    }

    // 跳过标题行
    char line[5 * MAX_LENGTH];
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file)) {
        Customer customer;
        char *token = strtok(line, "|||");
        if (!token) continue; // 跳过解析失败的行
        // 解析客户信息，根据文件中的列顺序
        strcpy(customer.name, token);
        if (strcmp(customer.name, customerName) == 0) {
            if (!(token = strtok(NULL, "|||"))) break;
            strcpy(customer.region, token);
            if (!(token = strtok(NULL, "|||"))) break;
            strcpy(customer.address, token);
            if (!(token = strtok(NULL, "|||"))) break;
            strcpy(customer.legalRepresentative, token);
            if (!(token = strtok(NULL, "|||"))) break;
            strcpy(customer.scale, token);
            if (!(token = strtok(NULL, "|||"))) break;
            strcpy(customer.businessContactLevel, token);
            if (!(token = strtok(NULL, "|||"))) break;
            strcpy(customer.email, token);

            // 处理电话号码，确保去除后续所有非必要字符
            token = strtok(NULL, "|||\n\r"); // 修改这里以处理可能的多余分隔符
            if (token) {
                cleanField(token); // 一个新的函数用来清除字段中多余的分隔符和空白字符
                strcpy(customer.phone, token);
            }

            appendNode_cus(head, customer);
            break;  // 找到后立即退出循环
        }
    }
    fclose(file);
}

// 加载客户的所有数据
void loadCustomers(const char *filename, head_node *head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开客户文件失败");
        return;
    }
    char line[1024];
    fgets(line, sizeof(line), file); // 跳过标题行
    while (fgets(line, sizeof(line), file)) {
        Customer customer;
        char *token = strtok(line, "|||");
        if (!token) continue;
        strcpy(customer.name, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(customer.region, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(customer.address, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(customer.legalRepresentative, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(customer.scale, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(customer.businessContactLevel, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(customer.email, token);

        // 处理电话号码，确保去除后续所有非必要字符
        token = strtok(NULL, "|||\n\r"); // 修改这里以处理可能的多余分隔符
        if (token) {
            cleanField(token); // 一个新的函数用来清除字段中多余的分隔符和空白字符
            strcpy(customer.phone, token);
        }
        
        appendNode_cus(head, customer);
    }
    fclose(file);
}
void loadContactPersons(const char *filename, head_node *head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开联系人文件失败");
        return;
    }
    char line[1024];
    fgets(line, sizeof(line), file); // 跳过标题行
    while (fgets(line, sizeof(line), file)) {
        ContactPerson contact;
        char *token = strtok(line, "|||");
        if (!token) continue;
        strcpy(contact.name, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(contact.gender, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(contact.birthday, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(contact.email, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(contact.phone, token);

        token = strtok(NULL, "|||\n\r");
        if (token) {
            cleanField(token);
            strcpy(contact.representative, token);
        }

        appendNode_ctp(head, contact);
    }
    fclose(file);
}
void loadEmployees(const char *filename, head_node *head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开员工文件失败");
        return;
    }

    char line[1024];
    fgets(line, sizeof(line), file); // 跳过标题行

    while (fgets(line, sizeof(line), file)) {
        Employee employee;
        char *token = strtok(line, "|||");
        if (!token) continue;
        strcpy(employee.name, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(employee.gender, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(employee.birthday, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(employee.email, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(employee.phone, token);

        token = strtok(NULL, "|||\n\r");
        if (token) {
            cleanField(token);
            strcpy(employee.representative, token);
        }

        appendNode_emp(head, employee);
    }
}
void loadRecords(const char *filename, head_node *head) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开记录文件失败");
        return;
    }
    char line[1024];
    fgets(line, sizeof(line), file); // 跳过标题行
    while (fgets(line, sizeof(line), file)) {
        Record record;
        char *token = strtok(line, "|||");
        if (!token) continue;
        strcpy(record.user, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(record.companyName, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(record.contactName, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(record.date, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(record.time, token);
        if (!(token = strtok(NULL, "|||"))) continue;
        strcpy(record.duration, token);

        token = strtok(NULL, "|||\n\r");
        if (token) {
            cleanField(token);
            strcpy(record.content, token);
        }

        appendNode_rec(head, record);
    }
}

// 初始化所有文件
void initializeAll() {
    initializeInfoFile("assignments.csv", "Employee|||Customer");
    initializeInfoFile("employees.csv", "Name|||Gender|||Birthday|||Email|||Phone|||Representative");
    initializeInfoFile("customers.csv", "Name|||Region|||Address|||LegalRepresentative|||Scale|||BusinessContactLevel|||Email|||Phone");
    initializeInfoFile("contacts.csv", "Name|||Gender|||Birthday|||Email|||Phone|||Representative");
}


