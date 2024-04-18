// widgets/record_manage.c
#include "../header.h"

void recordsManageWidget();
void addRecord();
void changeRecord();
void showRecord();
void displayRecord(Record record);

void recordsManageWidget() {
    initializeInfoFile("records.csv", "User|||CompanyName|||ContactName|||Date|||Time|||Duration|||Content");
    while (true) {
        printf("\n通信记录管理系统\n");
        printf("1. 增加通信记录\n");
        printf("2. 修改通信记录\n");
        printf("3. 显示通信记录\n");
        printf("4. 返回\n");
        printf("请选择一个操作（1-4）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);

        if (!isOneChar(get)) {
            printf("无效的选择，请重新输入。\n");
            continue;
        }
        switch (get[0]) {
        case '1':
            addRecord();
            break;
        case '2':
            changeRecord();
            break;
        case '3':
            showRecord();
            break;
        case '4':
            return;
        default:
            printf("无效的选项，请重新输入。\n");
            break;
        }
    }
}

void addRecord() {
    Record record;

    printf("添加新的通信记录。\n");
    
    inputTheName(record.companyName, sizeof(record.companyName), "请输入客户公司名称：");
    inputTheName(record.contactName, sizeof(record.contactName), "请输入客户联络员名称：");

    while (true) {
        infoInput(record.date, sizeof(record.date), "请输入日期 (YYYY-MM-DD)：");
        if (isSameString(record.date, " ") || matchDate(record.date)) {
            break;
        } else {
            printf("无效的日期格式，请重新输入。\n");
        }
    }
    while (true) {
        infoInput(record.time, sizeof(record.time), "请输入时间 (HH:MM:SS)：");
        if (isSameString(record.time, " ") || matchTime(record.time)) {
            break;
        } else {
            printf("无效的时间格式，请重新输入。\n");
        }
    }
    while (true) {
        infoInput(record.duration, sizeof(record.duration), "请输入通信时长（分钟）：");
        if (isSameString(record.duration, " ") || matchDuration(record.duration)) {
            break;
        } else {
            printf("无效的通信时长，请重新输入。\n");
        }
    }
    infoInput(record.content, sizeof(record.content), "请输入通信内容：");

    // 构建完整的记录字符串
    char fullLine[MAX_LENGTH * 7 + 18];
    strcpy(fullLine, User);
    addColumn(fullLine, record.companyName);
    addColumn(fullLine, record.contactName);
    addColumn(fullLine, record.date);
    addColumn(fullLine, record.time);
    addColumn(fullLine, record.duration);
    addColumn(fullLine, record.content);

    // 写入文件
    writeLineToFile("records.csv", fullLine);
    system(SYSTEM_CLEAR);
    displayRecord(record);
    printf("通信记录已成功添加。\n");
}

void changeRecord() {
    char companyName[MAX_LENGTH], contactName[MAX_LENGTH];
    char newCompanyName[MAX_LENGTH], newContactName[MAX_LENGTH], newDate[MAX_LENGTH], newTime[MAX_LENGTH], newDuration[MAX_LENGTH], newContent[MAX_LENGTH];
    char line[MAX_LENGTH * 8];
    char originalLine[MAX_LENGTH * 8]; // 保存原始行
    bool found = false;

    inputTheName(companyName, sizeof(companyName), "请输入要修改的客户公司名称：");
    inputTheName(contactName, sizeof(contactName), "请输入要修改的客户联络员名称：");

    FILE *file = fopen("records.csv", "r");
    FILE *tempFile = fopen("records_backup.csv", "w");
    if (!file || !tempFile) {
        perror("文件打开失败");
        return;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        strcpy(originalLine, line); // 保存原始行
        char *fields[7], *token;
        int i = 0;
        token = strtok(line, "|||");
        while (token != NULL && i < 7) {
            fields[i++] = token;
            token = strtok(NULL, "|||");
        }
        if (i == 7 && strcmp(fields[0], User) == 0 && strcmp(fields[1], companyName) == 0 && strcmp(fields[2], contactName) == 0) {
            found = true;
            printf("找到记录，输入新的值:\n");
            inputTheName(newCompanyName, sizeof(newCompanyName), "请输入新的客户公司名称：");
            inputTheName(newContactName, sizeof(newContactName), "请输入新的客户联络员名称：");
            while (true) {
                infoInput(newDate, sizeof(newDate), "请输入新的日期 (YYYY-MM-DD)：");
                if (isSameString(newDate, " ") || matchDate(newDate)) {
                    break;
                } else {
                    printf("无效的日期格式，请重新输入。\n");
                }
            }
            while (true) {
                infoInput(newTime, sizeof(newTime), "请输入新的时间 (HH:MM:SS)：");
                if (isSameString(newTime, " ") || matchTime(newTime)) {
                    break;
                } else {
                    printf("无效的时间格式，请重新输入。\n");
                }
            }
            while (true) {
                infoInput(newDuration, sizeof(newDuration), "请输入新的通信时长（分钟）：");
                if (isSameString(newDuration, " ") || matchDuration(newDuration)) {
                    break;
                } else {
                    printf("无效的通信时长，请重新输入。\n");
                }
            }
            snprintf(originalLine, sizeof(originalLine), "%s|||%s|||%s|||%s|||%s|||%s|||%s\n", User, newCompanyName, newContactName, newDate, newTime, newDuration, newContent);
        }
        fputs(originalLine, tempFile); // 总是写回临时文件
    }
    fclose(file);
    fclose(tempFile);

    // 替换原文件
    remove("records.csv");
    rename("records_backup.csv", "records.csv");

    if (!found) {
        printf("没有找到相应的记录。\n");
    } else {
        printf("记录已成功更新。\n");
    }
}

void showRecord() {
    FILE *file = fopen("records.csv", "r");
    if (!file) {
        perror("无法打开记录文件");
        return;
    }
    char line[MAX_LENGTH];
    printf("当前用户 %s 的通信记录如下：\n", User);
    
    printf("公司客户名 - 联络员 - 日期 - 时间 - 时长 - 内容\n");
    while (fgets(line, sizeof(line), file)) {
        char *currentUser = strtok(line, "|||");
        if (currentUser != NULL && strcmp(currentUser, User) == 0) {  // 确保当前行属于当前用户
            char *companyName = strtok(NULL, "|||");
            char *contactName = strtok(NULL, "|||");
            char *date = strtok(NULL, "|||");
            char *time = strtok(NULL, "|||");
            char *duration = strtok(NULL, "|||");
            char *content = strtok(NULL, "|||");
            printf("%s - %s - %s - %s - %s - %s", companyName, contactName, date, time, duration, content);
        }
    }
    fclose(file);
}

void displayRecord(Record record) {
    printf("\n显示通信记录信息:\n");
    printf("客户公司名称: %s\n", record.companyName);
    printf("联络员名称: %s\n", record.contactName);
    printf("日期: %s\n", record.date);
    printf("时间: %s\n", record.time);
    printf("通信时长: %s\n", record.duration);
    printf("通信内容: %s\n", record.content);
}


// end widgets/record_manage.c