// viewcustomers.c
#include "header.h"

// 函数声明
void viewCustomers();

void viewCustomers() {
    FILE *file = fopen("customers.csv", "r");
    if (!file) {
        perror("无法打开文件");
        return;
    }

    char line[MAX_LENGTH * 4];  // 考虑到一行数据的最大长度
    printf("客户列表:\n");
    printf("\t%-20s %-30s %-25s %-15s\n", "姓名", "地址", "电子邮件", "电话");

    // 跳过标题行
    fgets(line, sizeof(line), file);

    // 读取并显示每一行客户信息
    while (fgets(line, sizeof(line), file)) {
        char *name = strtok(line, "|||");
        char *address = strtok(NULL, "|||");
        char *email = strtok(NULL, "|||");
        char *phone = strtok(NULL, "|||");

        if (phone) {
            phone[strcspn(phone, "\n")] = 0;  // 移除可能的换行符
        }

        printf(
            "%-20s %-30s %-25s %-15s\n", 
            name ? name : "", 
            address ? address : "", 
            email ? email : "", 
            phone ? phone : ""
        );
    }

    fclose(file);
}

