// viewcustomers.c
#include "initialize.h"

// 函数声明
void viewCustomers();

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

        printf("%-20s %-20s %-30s %-20s %-10s %-20s %-25s %-15s\n",
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

