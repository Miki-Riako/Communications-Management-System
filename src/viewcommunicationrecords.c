// viewcommunicationrecords.c
#include "header.h"

// 函数声明
void viewCommunicationRecords();

void viewCommunicationRecords() {
    FILE *file = fopen("communication_records.csv", "r");
    if (!file) {
        perror("无法打开文件");
        return;
    }

    char line[1024];  // 考虑到一行数据的最大长度
    printf("\n通信记录列表:\n");
    printf("\t%-20s %-20s %-15s %-20s %-40s\n", "公司名称", "联系人姓名", "日期", "持续时间", "内容");

    // 跳过标题行
    fgets(line, sizeof(line), file);

    // 读取并显示每一行通信记录
    while (fgets(line, sizeof(line), file)) {
        char *companyName = strtok(line, "|||");
        char *contactName = strtok(NULL, "|||");
        char *date = strtok(NULL, "|||");
        char *duration = strtok(NULL, "|||");
        char *content = strtok(NULL, "|||");

        if (content) {
            content[strcspn(content, "\n")] = 0;  // 移除可能的换行符
        }

        printf("%-20s %-20s %-15s %-10s %-50s\n", 
            companyName ? companyName : "", 
            contactName ? contactName : "", 
            date ? date : "", 
            duration ? duration : "", 
            content ? content : "");
    }

    fclose(file);
}
