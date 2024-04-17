// widgets/record_manage.c
#include "../header.h"

void recordsManageWidget();
void addRecord();
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
            // changeRecord();
            break;
        case '3':
            // showRecord();
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