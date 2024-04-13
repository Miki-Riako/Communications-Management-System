// addcustomer.c
#include "header.h"

// 函数声明
void addCustomer();
bool matchMail(const char *email);
bool matchPhone(const char *phone);
void saveCustomerToFile(Customer customer);
void displayCustomer(Customer customer);

void initializeCustomerFile() {
    FILE *file = fopen("customers.csv", "r");
    if (!file) { // 文件不存在，创建新文件
        file = fopen("customers.csv", "w");
        if (!file) {
            perror("创建客户文件失败");
        } else {
            fprintf(file, "Name|||Address|||Email|||Phone\n"); // 写入列标题
            fclose(file);
        }
    } else {
        fclose(file); // 文件已存在，关闭文件
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
        if (!isdigit((unsigned char)*phone) && *phone != '-' && *phone != '+') {
            return false;  // 如果字符不是数字也不是连字符，则返回false
        }
        phone++;
    }
    return true;  // 所有字符都是数字或连字符
}

// 主函数，用于添加客户
void addCustomer() {
    initializeCustomerFile(); // 确保客户文件已初始化
    Customer newCustomer;

    while (getchar() != '\n');

    printf("输入客户姓名: ");
    fgets(newCustomer.name, sizeof(newCustomer.name), stdin);
    newCustomer.name[strcspn(newCustomer.name, "\n")] = 0; // 去除换行符
    if (newCustomer.name[0] == '\0') strcpy(newCustomer.name, " ");

    printf("输入客户地址: ");
    fgets(newCustomer.address, sizeof(newCustomer.address), stdin);
    newCustomer.address[strcspn(newCustomer.address, "\n")] = 0; // 去除换行符
    if (newCustomer.address[0] == '\0') strcpy(newCustomer.address, " ");

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
        newCustomer.phone[strcspn(newCustomer.phone, "\n")] = 0; // 去除换行符
        if (newCustomer.phone[0] == '\0') {
            strcpy(newCustomer.phone, " ");
            break;
        } else if (matchPhone(newCustomer.phone)) {
            break;
        } else {
            printf("电话号码格式不正确，请重新输入。\n");
        }
    }

    system(SYSTEM_CLEAR); // 保存客户信息到文件
    saveCustomerToFile(newCustomer); // 显示客户信息
    displayCustomer(newCustomer);

    printf("客户信息已添加.\n");
}

// 将客户信息保存到文件
void saveCustomerToFile(Customer customer) {
    FILE *file = fopen("customers.csv", "a"); // 以追加模式打开文件
    if (file == NULL) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s|||%s|||%s|||%s\n", customer.name, customer.address, customer.email, customer.phone);
    fclose(file);
}

// 显示客户信息
void displayCustomer(Customer customer) {
    printf("\n显示客户信息:\n");
    printf("姓名: %s\n", customer.name);
    printf("地址: %s\n", customer.address);
    printf("电子邮件: %s\n", customer.email);
    printf("电话: %s\n", customer.phone);
}

