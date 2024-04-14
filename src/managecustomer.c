
void addContactPerson() {
    ContactPerson newContact;

    while (getchar() != '\n'); // 清空缓冲区

    printf("输入联络员姓名: ");
    fgets(newContact.name, sizeof(newContact.name), stdin);
    newContact.name[strcspn(newContact.name, "\n")] = 0;
    if (newContact.name[0] == '\0') strcpy(newContact.name, " ");

    printf("输入联络员性别: ");
    fgets(newContact.gender, sizeof(newContact.gender), stdin);
    newContact.gender[strcspn(newContact.gender, "\n")] = 0;
    if (newContact.gender[0] == '\0') strcpy(newContact.gender, " ");

    printf("输入联络员生日: ");
    fgets(newContact.birthday, sizeof(newContact.birthday), stdin);
    newContact.birthday[strcspn(newContact.birthday, "\n")] = 0;
    if (newContact.birthday[0] == '\0') strcpy(newContact.birthday, " ");

    while (true) {
        printf("输入联络员电子邮件: ");
        fgets(newContact.email, sizeof(newContact.email), stdin);
        newContact.email[strcspn(newContact.email, "\n")] = 0;
        if (newContact.email[0] == '\0') {
            strcpy(newContact.email, " ");
            break;
        } else if (matchMail(newContact.email)) {
            break;
        } else {
            printf("电子邮件格式不正确，请重新输入。\n");
        }
    }

    while (true) {
        printf("输入联络员电话: ");
        fgets(newContact.phone, sizeof(newContact.phone), stdin);
        newContact.phone[strcspn(newContact.phone, "\n")] = 0;
        if (newContact.phone[0] == '\0') {
            strcpy(newContact.phone, " ");
            break;
        } else if (matchPhone(newContact.phone)) {
            break;
        } else {
            printf("电话号码格式不正确，请重新输入。\n");
        }
    }

    printf("输入联络员代表业务员: ");
    fgets(newContact.representative, sizeof(newContact.representative), stdin);
    newContact.representative[strcspn(newContact.representative, "\n")] = 0;

    system(SYSTEM_CLEAR); // 清屏
    saveContactPersonToFile(newContact);
    displayContactPerson(newContact);
    printf("联络员信息已添加.\n");
}

void addEmployee() {
    Employee newEmployee;

    while (getchar() != '\n'); // 清空缓冲区

    printf("输入业务员姓名: ");
    fgets(newEmployee.name, sizeof(newEmployee.name), stdin);
    newEmployee.name[strcspn(newEmployee.name, "\n")] = 0;
    if (newEmployee.name[0] == '\0') strcpy(newEmployee.name, " ");

    printf("输入业务员性别: ");
    fgets(newEmployee.gender, sizeof(newEmployee.gender), stdin);
    newEmployee.gender[strcspn(newEmployee.gender, "\n")] = 0;
    if (newEmployee.gender[0] == '\0') strcpy(newEmployee.gender, " ");

    printf("输入业务员生日: ");
    fgets(newEmployee.birthday, sizeof(newEmployee.birthday), stdin);
    newEmployee.birthday[strcspn(newEmployee.birthday, "\n")] = 0;
    if (newEmployee.birthday[0] == '\0') strcpy(newEmployee.birthday, " ");

    while (true) {
        printf("输入业务员电子邮件: ");
        fgets(newEmployee.email, sizeof(newEmployee.email), stdin);
        newEmployee.email[strcspn(newEmployee.email, "\n")] = 0;
        if (newEmployee.email[0] == '\0') {
            strcpy(newEmployee.email, " ");
            break;
        } else if (matchMail(newEmployee.email)) {
            break;
        } else {
            printf("电子邮件格式不正确，请重新输入。\n");
        }
    }

    while (true) {
        printf("输入业务员电话: ");
        fgets(newEmployee.phone, sizeof(newEmployee.phone), stdin);
        newEmployee.phone[strcspn(newEmployee.phone, "\n")] = 0;
        if (newEmployee.phone[0] == '\0') {
            strcpy(newEmployee.phone, " ");
            break;
        } else if (matchPhone(newEmployee.phone)) {
            break;
        } else {
            printf("电话号码格式不正确，请重新输入。\n");
        }
    }

    printf("输入业务员代表联络员: ");
    fgets(newEmployee.representative, sizeof(newEmployee.representative), stdin);
    newEmployee.representative[strcspn(newEmployee.representative, "\n")] = 0;

    system(SYSTEM_CLEAR); // 清屏
    saveEmployeeToFile(newEmployee);
    displayEmployee(newEmployee);
    printf("业务员信息已添加.\n");
}

void viewCustomers() {
    FILE *file = fopen("customers.csv", "r");
    if (!file) {
        perror("无法打开文件");
        return;
    }

    char line[MAX_LENGTH * 8];
    printf("客户列表:\n");
    printf("\t%-20s %-20s %-20s %-20s %-20s %-20s %-20s %-20s\n", 
            "姓名",
            "区域",
            "地址",
            "法人",
            "规模",
            "业务联系程度",
            "电子邮件",
            "电话"
        );

    fgets(line, sizeof(line), file);  // 跳过标题行

    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, "|||");
        char *region = strtok(NULL, "|||");
        char *address = strtok(NULL, "|||");
        char *legalRepresentative = strtok(NULL, "|||");
        char *scale = strtok(NULL, "|||");
        char *businessContactLevel = strtok(NULL, "|||");
        char *email = strtok(NULL, "|||");
        char *phone = strtok(NULL, "|||");

        if (phone) phone[strcspn(phone, "\n")] = 0;

        printf("%-20s %-20s %-20s %-20s %-20s %-20s %-20s %-20s\n",
            name,
            region,
            address,
            legalRepresentative,
            scale,
            businessContactLevel,
            email,
            phone
        );
    }

    fclose(file);
}

void viewContactPerson() {
    FILE *file = fopen("contactpersons.csv", "r");
    if (!file) {
        perror("无法打开文件");
        return;
    }

    char line[MAX_LENGTH * 8];
    printf("联络员列表:\n");
    printf("\t%-20s %-10s %-15s %-25s %-15s %-20s\n", 
        "姓名",
        "性别",
        "生日",
        "电子邮件",
        "电话",
        "代表业务员"
    );

    fgets(line, sizeof(line), file);  // 跳过标题行

    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, "|||");
        char *gender = strtok(NULL, "|||");
        char *birthday = strtok(NULL, "|||");
        char *email = strtok(NULL, "|||");
        char *phone = strtok(NULL, "|||");
        char *representative = strtok(NULL, "|||");

        if (representative) representative[strcspn(representative, "\n")] = 0;

        printf("%-20s %-10s %-15s %-25s %-15s %-20s\n",
            name,
            gender,
            birthday,
            email,
            phone,
            representative
        );
    }

    fclose(file);
}

void viewEmployee() {
    FILE *file = fopen("employeeInfo.csv", "r");
    if (!file) {
        perror("无法打开文件");
        return;
    }

    char line[MAX_LENGTH * 8];
    printf("业务员列表:\n");
    printf("\t%-20s %-10s %-15s %-25s %-15s %-20s\n", 
        "姓名",
        "性别",
        "生日",
        "电子邮件",
        "电话",
        "代表联络员"
    );

    fgets(line, sizeof(line), file);  // 跳过标题行

    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, "|||");
        char *gender = strtok(NULL, "|||");
        char *birthday = strtok(NULL, "|||");
        char *email = strtok(NULL, "|||");
        char *phone = strtok(NULL, "|||");
        char *representative = strtok(NULL, "|||");
        if (representative) representative[strcspn(representative, "\n")] = 0;

        printf("%-20s %-10s %-15s %-25s %-15s %-20s\n",
            name,
            gender,
            birthday,
            email,
            phone,
            representative
        );
    }
    
    fclose(file);
}

void removeCustomer() {
    char delName[MAX_LENGTH];
    char buffer[MAX_LENGTH];
    FILE *fp, *fp_temp;
    
    while (getchar() != '\n'); // 清空缓冲区
    
    printf("输入要删除的客户姓名: ");
    fgets(delName, sizeof(delName), stdin);
    delName[strcspn(delName, "\n")] = 0;  // Remove newline character

    // 打开原始文件和临时文件
    fp = fopen("customers.csv", "r");
    if (fp == NULL) {
        printf("无法打开文件 %s\n", "customers.csv");
        return;
    }
    fp_temp = fopen("temp.csv", "w");
    if (fp_temp == NULL) {
        printf("无法创建临时文件\n");
        fclose(fp);
        return;
    }

    // 逐行读取和处理数据
    while (fgets(buffer, MAX_LENGTH, fp) != NULL) {
        // 检查是否包含要删除的用户名
        char* found = strstr(buffer, delName);
        if (found != buffer) { // 确保是从行首开始匹配用户名
            fprintf(fp_temp, "%s", buffer);
        }
    }

    // 关闭文件
    fclose(fp);
    fclose(fp_temp);

    // 替换原始文件
    remove("customers.csv");
    rename("temp.csv", "customers.csv");

    printf("用户删除成功\n");
}

void removeContactPerson() {
    char delName[MAX_LENGTH];
    char buffer[MAX_LENGTH];
    FILE *fp, *fp_temp;

    while (getchar() != '\n'); // 清空缓冲区

    printf("输入要删除的联络员姓名: ");
    fgets(delName, sizeof(delName), stdin);
    delName[strcspn(delName, "\n")] = 0;

    fp = fopen("contactpersons.csv", "r");
    if (!fp) {
        printf("无法打开文件 %s\n", "contactpersons.csv");
        return;
    }
    fp_temp = fopen("temp.csv", "w");
    if (!fp_temp) {
        printf("无法创建临时文件\n");
        fclose(fp);
        return;
    }

    while (fgets(buffer, MAX_LENGTH, fp) != NULL) {
        if (!strstr(buffer, delName)) {
            fprintf(fp_temp, "%s", buffer);
        }
    }

    fclose(fp);
    fclose(fp_temp);

    remove("contactpersons.csv");
    rename("temp.csv", "contactpersons.csv");

    printf("联络员删除成功\n");
}

void removeEmployee() {
    char delName[MAX_LENGTH];
    char buffer[MAX_LENGTH];
    FILE *fp, *fp_temp;
    while (getchar() != '\n'); // 清空缓冲区

    printf("输入要删除的业务员姓名: ");
    fgets(delName, sizeof(delName), stdin);
    delName[strcspn(delName, "\n")] = 0;

    fp = fopen("employeeInfo.csv", "r");
    if (!fp) {
        printf("无法打开文件 %s\n", "employeeInfo.csv");
        return;
    }
    fp_temp = fopen("temp.csv", "w");
    if (!fp_temp) {
        printf("无法创建临时文件\n");
        fclose(fp);
        return;
    }

    while (fgets(buffer, MAX_LENGTH, fp) != NULL) {
        if (!strstr(buffer, delName)) {
            fprintf(fp_temp, "%s", buffer);
        }
    }

    fclose(fp);
    fclose(fp_temp);

    remove("employeeInfo.csv");
    rename("temp.csv", "employeeInfo.csv");

    printf("业务员删除成功\n");
}


// 将客户信息保存到文件
void saveCustomerToFile(Customer customer) {
    FILE *file = fopen("customers.csv", "a");
    if (!file) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s|||%s|||%s|||%s|||%s|||%s|||%s|||%s\n",
        customer.name,
        customer.region,
        customer.address,
        customer.legalRepresentative,
        customer.scale,
        customer.businessContactLevel,
        customer.email,
        customer.phone
    );
    fclose(file);
}

void saveContactPersonToFile(ContactPerson contact) {
    FILE *file = fopen("contactpersons.csv", "a");
    if (!file) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s|||%s|||%s|||%s|||%s|||%s\n",
        contact.name,
        contact.gender,
        contact.birthday,
        contact.email,
        contact.phone,
        contact.representative
    );
    fclose(file);
}

void saveEmployeeToFile(Employee employee) {
    FILE *file = fopen("employeeInfo.csv", "a");
    if (!file) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s|||%s|||%s|||%s|||%s|||%s\n",
        employee.name,
        employee.gender,
        employee.birthday,
        employee.email,
        employee.phone,
        employee.representative
    );
    fclose(file);
}

// 显示客户信息
void displayCustomer(Customer customer) {
    printf("\n显示客户信息:\n");
    printf("姓名: %-20s\n", customer.name);
    printf("区域: %-20s\n", customer.region);
    printf("地址: %-30s\n", customer.address);
    printf("法人: %-20s\n", customer.legalRepresentative);
    printf("规模: %-10s\n", customer.scale);
    printf("业务联系程度: %-15s\n", customer.businessContactLevel);
    printf("电子邮件: %-25s\n", customer.email);
    printf("电话: %-15s\n", customer.phone);
}

void displayContactPerson(ContactPerson contact) {
    printf("\n显示联络员信息:\n");
    printf("姓名: %-20s\n", contact.name);
    printf("性别: %-10s\n", contact.gender);
    printf("生日: %-15s\n", contact.birthday);
    printf("电子邮件: %-25s\n", contact.email);
    printf("电话: %-15s\n", contact.phone);
    printf("代表业务员: %-20s\n", contact.representative);
}

void displayEmployee(Employee employee) {
    printf("\n显示业务员信息:\n");
    printf("姓名: %-20s\n", employee.name);
    printf("性别: %-10s\n", employee.gender);
    printf("生日: %-15s\n", employee.birthday);
    printf("电子邮件: %-25s\n", employee.email);
    printf("电话: %-15s\n", employee.phone);
    printf("代表联络员: %-20s\n", employee.representative);
}
