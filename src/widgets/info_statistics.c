// widgets/info_statistics.c
#include "../header.h"

void infoStatisticsWidget();
void simpleStatistics(head_node *head);
void combinedStatistics(head_node *head);
void countAttributes(head_node *head, int attrIndex, int dataType);
char* getCustomerAttribute(Customer *customer, int attrIndex);
char* getContactPersonAttribute(ContactPerson *contact, int attrIndex);
char* getEmployeeAttribute(Employee *employee, int attrIndex);

void infoStatisticsWidget() {
    initializeAll();
    printf("正在加载中，请您耐心等待。\n");
    head_node *head = (head_node *)malloc(sizeof(head_node));  // 分配内存
    if (!head) {
        fprintf(stderr, "内存分配失败！\n");
        return;
    }
    loadFile(head);  // 加载数据
    if (head->is_empty)  printf("没有加载到任何数据。\n");
    else printf("数据加载成功！\n");

    while (true) {
        printf("\n信息统计系统\n");
        printf("1. 简单统计\n");
        printf("2. 组合统计\n");
        printf("3. 预设统计\n");
        printf("4. 按条件统计\n");
        printf("5. 返回\n");
        printf("请选择一个操作（1-5）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);

        switch (get[0]) {
        case '1':
            simpleStatistics(head);
            break;
        case '2':
            combinedStatistics(head);
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            printf("正在返回，请稍等。\n");
            freeAll(head);
            printf("返回成功。\n");
            return;
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
    }
}

void simpleStatistics(head_node *head) {
    int which = beforeInfo(head, "统计");
    if (which == -1) return;  // 无效的选择

    int attrIndex = selectSearchAttribute(which);
    if (attrIndex == -1) {
        printf("无效的属性选择。\n");
        return;
    }

    countAttributes(head, attrIndex, which);
}

void combinedStatistics(head_node *head) {

}

void countAttributes(head_node *head, int attrIndex, int dataType) {
    // 用于存储每个唯一值及其出现次数的结构

    AttributeCount counts[MAX_LENGTH];
    int uniqueCount = 0;
    bool found;
    char *attributeValue;

    switch (dataType) {
    case 0: // 客户
        for (node_cus *node = head->next_cus; node != NULL; node = node->next) {
            attributeValue = getCustomerAttribute(&node->customer, attrIndex);
            found = false;
            for (int i = 0; i < uniqueCount; i++) {
                if (strcmp(counts[i].value, attributeValue) == 0) {
                    counts[i].count++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                strcpy(counts[uniqueCount].value, attributeValue);
                counts[uniqueCount].count = 1;
                ++uniqueCount;
            }
        }
        break;
    case 1: // 联络人
        for (node_ctp *node = head->next_ctp; node != NULL; node = node->next) {
            attributeValue = getContactPersonAttribute(&node->contactPerson, attrIndex);
            found = false;
            for (int i = 0; i < uniqueCount; i++) {
                if (strcmp(counts[i].value, attributeValue) == 0) {
                    counts[i].count++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                strcpy(counts[uniqueCount].value, attributeValue);
                counts[uniqueCount].count = 1;
                ++uniqueCount;
            }
        }
        break;
    case 2: // 业务员
        for (node_emp *node = head->next_emp; node != NULL; node = node->next) {
            attributeValue = getEmployeeAttribute(&node->employee, attrIndex);
            found = false;
            for (int i = 0; i < uniqueCount; i++) {
                if (strcmp(counts[i].value, attributeValue) == 0) {
                    counts[i].count++;
                    found = true;
                    break;
                }
            }
            if (!found) {
                strcpy(counts[uniqueCount].value, attributeValue);
                counts[uniqueCount].count = 1;
                ++uniqueCount;
            }
        }
        break;
    }

    // 打印统计结果
    printf("统计结果：\n");
    for (int i = 0; i < uniqueCount; ++i) {
        if (isSameString(counts[i].value, " ")) {
            printf("未输入的空值: %d\n", counts[i].count);
        } else {
            printf("%s: %d\n", counts[i].value, counts[i].count);
        }
    }
    printf("统计完毕！\n");
}

char* getCustomerAttribute(Customer *customer, int attrIndex) {
    switch (attrIndex) {
    case 0: return customer->name;
    case 1: return customer->region;
    case 2: return customer->address;
    case 3: return customer->legalRepresentative;
    case 4: return customer->scale;
    case 5: return customer->businessContactLevel;
    case 6: return customer->email;
    case 7: return customer->phone;
    default: return " ";
    }
}

char* getContactPersonAttribute(ContactPerson *contact, int attrIndex) {
    switch (attrIndex) {
    case 0: return contact->name;
    case 1: return contact->gender;
    case 2: return contact->birthday;
    case 3: return contact->email;
    case 4: return contact->phone;
    case 5: return contact->representative;
    default: return " ";
    }
}

char* getEmployeeAttribute(Employee *employee, int attrIndex) {
    switch (attrIndex) {
    case 0: return employee->name;
    case 1: return employee->gender;
    case 2: return employee->birthday;
    case 3: return employee->email;
    case 4: return employee->phone;
    case 5: return employee->representative;
    default: return " ";
    }
}

// end widgets/info_statistics.c
