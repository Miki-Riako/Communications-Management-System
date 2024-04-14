// addcommunicationrecord.c
#include "initialize.h"

// 函数声明
void manageCommunicationRecord();
void initializeCommunicationFile();
void addCommunicationRecord();
void viewCommunicationRecords();
bool matchDate(const char *date);
bool matchTime(const char *time);
bool matchDuration(const char *duration);
void saveCommunicationRecordToFile(CommunicationRecord record);

// 管理通信记录界面
void manageCommunicationRecord() {
    while (true) {
        int choice;
        printf("\n管理通信记录\n");
        printf("1. 添加通信记录\n");
        printf("2. 查看通信记录\n");
        printf("3. 返回\n");
        printf("请选择操作（1-3）：");
        scanf("%d", &choice);
        system(SYSTEM_CLEAR);

        switch (choice) {
            case 1:
                addCommunicationRecord();
                break;
            case 2:
                viewCommunicationRecords();
                break;
            case 3:
                return;  // 返回主菜单
            default:
                printf("无效的选项，请重新输入。\n");
        }
    }
}

void initializeCommunicationFile() {
    FILE *file = fopen("communication_records.csv", "r");
    if (!file) { 
        file = fopen("communication_records.csv", "w");
        if (!file) {
            perror("创建通信记录文件失败");
        } else {
            fprintf(file, "CompanyName|||ContactName|||Date|||Time|||Duration|||Content\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }
}

void addCommunicationRecord() {
    initializeCommunicationFile(); // 确保通信记录文件已初始化
    CommunicationRecord newRecord;

    while (getchar() != '\n');

    printf("输入公司名称: ");
    fgets(newRecord.companyName, sizeof(newRecord.companyName), stdin);
    newRecord.companyName[strcspn(newRecord.companyName, "\n")] = 0;
    if (newRecord.companyName[0] == '\0') strcpy(newRecord.companyName, " ");

    printf("输入联系人姓名: ");
    fgets(newRecord.contactName, sizeof(newRecord.contactName), stdin);
    newRecord.contactName[strcspn(newRecord.contactName, "\n")] = 0;
    if (newRecord.contactName[0] == '\0') strcpy(newRecord.contactName, " ");

    while (true) {
        printf("输入通信日期 (YYYY-MM-DD): ");
        fgets(newRecord.date, sizeof(newRecord.date), stdin);
        newRecord.date[strcspn(newRecord.date, "\n")] = 0; // 去除换行符
        if (newRecord.date[0] == '\0') {
            strcpy(newRecord.date, " ");
            break;
        } else if (matchDate(newRecord.date)) {
            break;
        } else {
            printf("日期格式不正确，请重新输入。\n");
        }
    }

    while (true) {
        printf("输入通信时间 (HH:MM:SS): ");
        fgets(newRecord.time, sizeof(newRecord.time), stdin);
        newRecord.time[strcspn(newRecord.time, "\n")] = 0;

        if (newRecord.time[0] == '\0') {
            strcpy(newRecord.time, " ");
            break;
        } else if (matchTime(newRecord.time)) {
            break;
        } else {
            printf("通信时间格式不正确，请重新输入。\n");
        }
    }

    while (true) {
        printf("输入通信持续时间 (分钟): ");
        fgets(newRecord.duration, sizeof(newRecord.duration), stdin);
        newRecord.duration[strcspn(newRecord.duration, "\n")] = 0; // 去除换行符

        if (newRecord.duration[0] == '\0') {
            strcpy(newRecord.duration, " ");
            break;
        } else if (matchDuration(newRecord.duration)) {
            break;
        } else {
            printf("通信持续时间格式不正确，请输入正整数或正小数。\n");
        }
    }

    printf("输入通信内容: ");
    fgets(newRecord.content, sizeof(newRecord.content), stdin);
    newRecord.content[strcspn(newRecord.content, "\n")] = 0;
    if (newRecord.content[0] == '\0') strcpy(newRecord.content, " ");

    saveCommunicationRecordToFile(newRecord);
    printf("通信记录已添加.\n");
}

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

bool matchDate(const char *date) {
    regex_t regex;
    int ret;
    char msgbuf[100];

    // YYYY-MM-DD format
    ret = regcomp(&regex, "^[0-9]{4}-[0-9]{2}-[0-9]{2}$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return false;
    }

    // Execute matching
    ret = regexec(&regex, date, 0, NULL, 0);
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

bool matchTime(const char *time) {
    regex_t regex;
    int ret;
    char msgbuf[100];

    // HH:MM:SS format
    ret = regcomp(&regex, "^[0-2][0-9]:[0-5][0-9]:[0-5][0-9]$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex for time\n");
        return false;
    }

    // Execute matching
    ret = regexec(&regex, time, 0, NULL, 0);
    regfree(&regex);  // 释放正则表达式
    if (!ret) {
        if (atoi(time) < 24) { // 验证小时部分是否小于24
            return true;
        }
        return false;
    } else if (ret == REG_NOMATCH) {
        return false;
    } else {
        regerror(ret, &regex, msgbuf, sizeof(msgbuf));
        fprintf(stderr, "Regex match failed: %s\n", msgbuf);
        return false;
    }
}


bool matchDuration(const char *duration) {
    regex_t regex;
    int ret;
    char msgbuf[100];

    // 编译正则表达式
    ret = regcomp(&regex, "^[0-9]+(\\.[0-9]+)?$", REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex for duration\n");
        return false;
    }

    // 执行匹配
    ret = regexec(&regex, duration, 0, NULL, 0);
    regfree(&regex);  // 释放正则表达式
    if (ret == 0) {
        return true; // 匹配成功
    } else {
        return false; // 匹配失败
    }
}

void saveCommunicationRecordToFile(CommunicationRecord record) {
    FILE *file = fopen("communication_records.csv", "a");
    if (!file) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s|||%s|||%s|||%s|||%s|||%s\n", 
        record.companyName, 
        record.contactName, 
        record.date, 
        record.time, 
        record.duration, 
        record.content
    );
    fclose(file);
}
