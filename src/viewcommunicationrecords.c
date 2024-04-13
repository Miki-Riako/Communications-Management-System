// viewcommunicationrecords.c
#include "initialize.h"

// 函数声明
void viewCommunicationRecords();

void viewCommunicationRecords() {
    initializeCommunicationFile(); // 确保通信记录文件已初始化

    FILE *file = fopen("communication_records.csv", "r");
    if (!file) {
        perror("无法打开文件");
        return;
    }

    char line[1024];
    printf("\n通信记录列表:\n");
    printf("\t%-20s %-20s %-20s %-20s %-20s %-20s\n", "公司名称", "联系人姓名", "日期", "时间", "持续时间", "内容");

    fgets(line, sizeof(line), file);  // 跳过标题行
    while (fgets(line, sizeof(line), file)) {
        char *companyName = strtok(line, "|||");
        char *contactName = strtok(NULL, "|||");
        char *date = strtok(NULL, "|||");
        char *time = strtok(NULL, "|||");
        char *duration = strtok(NULL, "|||");
        char *content = strtok(NULL, "|||");

        if (content) content[strcspn(content, "\n")] = 0;

        printf("%-20s %-20s %-20s %-20s %-20s %-20s\n", 
            companyName,
            contactName,
            date,
            time,
            duration,
            content
        );
    }

    fclose(file);
}
