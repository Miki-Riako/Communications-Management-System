// managecustomer.c
#include "initialize.h"

void manageCustomer();
void initializeCustomerFile();
void addCustomer();
void viewCustomers();
bool matchMail(const char *email);
bool matchPhone(const char *phone);
void saveCustomerToFile(Customer customer);
void displayCustomer(Customer customer);

// 管理客户信息界面
void manageCustomer() {
    while (true) {
        int choice;
        printf("\n管理客户信息\n");
        printf("1. 添加客户信息\n");
        printf("2. 查看客户信息\n");
        printf("3. 返回\n");
        printf("请选择操作（1-3）：");
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
                return;  // 返回主菜单
            default:
                printf("无效的选项，请重新输入。\n");
        }
    }
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

void addCustomer() {
    initializeCustomerFile(); // 确保客户文件已初始化
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

void viewCustomers() {
    initializeCustomerFile(); // 确保客户文件已初始化

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


// 将客户信息保存到文件
void saveCustomerToFile(Customer customer) {
    FILE *file = fopen("customers.csv", "a");
    if (!file) {
        perror("打开文件失败");
        return;
    }
    fprintf(file,
        "%s|||%s|||%s|||%s|||%s|||%s|||%s|||%s\n",
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