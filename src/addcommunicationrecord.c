// addcommunicationrecord.c
#include "initialize.h"

// 函数声明
void addCommunicationRecord();
void saveCommunicationRecordToFile(CommunicationRecord record);
bool matchDate(const char *date);
bool matchTime(const char *time);
bool matchDuration(const char *duration);

void addCommunicationRecord() {
    initializeCommunicationFile(); // 确保通信记录文件已初始化

    while (getchar() != '\n');

    CommunicationRecord newRecord;
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