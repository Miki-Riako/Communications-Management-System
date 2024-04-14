// managecustomer.c
#include "initialize.h"

void manageCustomer();
bool matchMail(const char *email);
bool matchPhone(const char *phone);
void initializeCustomerFile();
void initializeContactPersonFile();
void initializeEmployeeFile();
void addCustomer();
void addContactPerson();
void addEmployee();
void viewCustomers();
void viewContactPerson();
void viewEmployee();
void removeCustomer();
void removeContactPerson();
void removeEmployee();
void saveCustomerToFile(Customer customer);
void saveContactPersonToFile(ContactPerson customer);
void saveEmployeeToFile(Employee employee);
void displayCustomer(Customer customer);
void displayContactPerson(ContactPerson customer);
void displayEmployee(Employee employee);

// 管理客户信息界面
void manageCustomer() {
    initializeCustomerFile();
    initializeContactPersonFile();
    initializeEmployeeFile();
    while (true) {
        int choice;
        printf("\n管理客户信息\n");
        printf("1. 添加客户信息\n");
        printf("2. 查看客户信息\n");
        printf("3. 删除客户信息\n");
        printf("4. 添加客户联络员信息\n");
        printf("5. 查看客户联络员信息\n");
        printf("6. 删除客户联络员信息\n");
        printf("7. 添加业务员员信息\n");
        printf("8. 查看业务员信息\n");
        printf("9. 删除业务员信息\n");
        printf("10. 返回\n");
        printf("请选择操作（1-10）：");
        scanf("%d", &choice);
        system(SYSTEM_CLEAR);

        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                viewCustomers();
                break;
            case 3:
                removeCustomer();
                break;
            case 4:
                addContactPerson();
                break;
            case 5:
                viewContactPerson();
                break;
            case 6:
                removeContactPerson();
                break;
            case 7:
                if (IsManager) {
                    addEmployee();
                } else {
                    printf("您不是管理员，无法添加业务员信息。\n");
                }
                break;
            case 8:
                viewEmployee();
                break;
            case 9:
                if (IsManager) {
                    removeEmployee();
                } else {
                    printf("您不是管理员，无法删除业务员信息。\n");
                }
                break;
            case 10:
                return;  // 返回主菜单
            default:
                printf("无效的选项，请重新输入。\n");
        }
    }
}

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

void initializeCustomerFile() {
    FILE *file = fopen("customers.csv", "r");
    if (!file) { // 文件不存在，创建新文件
        file = fopen("customers.csv", "w");
        if (!file) {
            perror("创建客户文件失败");
        } else {
            fprintf(file, "Name|||Region|||Address|||LegalRepresentative|||Scale|||BusinessContactLevel|||Email|||Phone\n");
            fclose(file);
        }
    } else {
        fclose(file); // 文件已存在，关闭文件
    }
}

void initializeContactPersonFile() {
    FILE *file = fopen("contactpersons.csv", "r");
    if (!file) {
        file = fopen("contactpersons.csv", "w");
        if (!file) {
            perror("创建联系人文件失败");
        } else {
            fprintf(file, "Name|||Gender|||Birthday|||Email|||Phone|||Representative\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }
}

void initializeEmployeeFile() {
    FILE *file = fopen("employeeInfo.csv", "r");
    if (!file) {
        file = fopen("employeeInfo.csv", "w");
        if (!file) {
            perror("创建业务员文件失败");
        } else {
            fprintf(file, "Name|||Gender|||Birthday|||Email|||Phone|||Representative\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }
}

void addCustomer() {
    Customer newCustomer;

    while (getchar() != '\n'); // 清空缓冲区

    printf("输入客户姓名: ");
    fgets(newCustomer.name, sizeof(newCustomer.name), stdin);
    newCustomer.name[strcspn(newCustomer.name, "\n")] = 0;
    if (newCustomer.name[0] == '\0') strcpy(newCustomer.name, " ");

    printf("输入客户所在区域: ");
    fgets(newCustomer.region, sizeof(newCustomer.region), stdin);
    newCustomer.region[strcspn(newCustomer.region, "\n")] = 0;
    if (newCustomer.region[0] == '\0') strcpy(newCustomer.region, " ");

    printf("输入客户地址: ");
    fgets(newCustomer.address, sizeof(newCustomer.address), stdin);
    newCustomer.address[strcspn(newCustomer.address, "\n")] = 0;
    if (newCustomer.address[0] == '\0') strcpy(newCustomer.address, " ");

    printf("输入客户公司法人: ");
    fgets(newCustomer.legalRepresentative, sizeof(newCustomer.legalRepresentative), stdin);
    newCustomer.legalRepresentative[strcspn(newCustomer.legalRepresentative, "\n")] = 0;
    if (newCustomer.legalRepresentative[0] == '\0') strcpy(newCustomer.legalRepresentative, " ");

    printf("输入客户规模（大、中、小）: ");
    fgets(newCustomer.scale, sizeof(newCustomer.scale), stdin);
    newCustomer.scale[strcspn(newCustomer.scale, "\n")] = 0;
    if (newCustomer.scale[0] == '\0') strcpy(newCustomer.scale, " ");

    printf("输入与本公司业务联系程度（高、中、低）: ");
    fgets(newCustomer.businessContactLevel, sizeof(newCustomer.businessContactLevel), stdin);
    newCustomer.businessContactLevel[strcspn(newCustomer.businessContactLevel, "\n")] = 0;
    if (newCustomer.businessContactLevel[0] == '\0') strcpy(newCustomer.businessContactLevel, " ");

    while (true) {
        printf("输入客户电子邮件: ");
        fgets(newCustomer.email, sizeof(newCustomer.email), stdin);
        newCustomer.email[strcspn(newCustomer.email, "\n")] = 0;
        if (newCustomer.email[0] == '\0') {
            strcpy(newCustomer.email, " ");
            break;
        } else if (matchMail(newCustomer.email)) {
            break;
        } else {
            printf("电子邮件格式不正确，请重新输入。\n");
        }
    }

    while (true) {
        printf("输入客户电话: ");
        fgets(newCustomer.phone, sizeof(newCustomer.phone), stdin);
        newCustomer.phone[strcspn(newCustomer.phone, "\n")] = 0;
        if (newCustomer.phone[0] == '\0') {
            strcpy(newCustomer.phone, " ");
            break;
        } else if (matchPhone(newCustomer.phone)) {
            break;
        } else {
            printf("电话号码格式不正确，请重新输入。\n");
        }
    }

    system(SYSTEM_CLEAR); // 清屏
    saveCustomerToFile(newCustomer);
    displayCustomer(newCustomer);
    printf("客户信息已添加.\n");
}

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
