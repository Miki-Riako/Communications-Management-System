// widgets/info_statistics.c
#include "../header.h"

void infoStatisticsWidget();
void simpleStatistics(head_node *head);
void combinedStatistics(head_node *head);
void presetStatistics(head_node *head);
void conditionalStatistics(head_node *head);
void countAttributesByConditions(head_node *head, int *attrIndexes, char conditionValues[][MAX_LENGTH], int numConditions, int which);
void countCombinedAttributes(head_node *head, int *attrIndexes, int numAttrs, int which);
void countAttributes(head_node *head, int attrIndex, int which);
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
        printf("4. 条件统计\n");
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
            presetStatistics(head);
            break;
        case '4':
            conditionalStatistics(head);
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
    if (head->is_empty) {
        printf("没有可统计的数据。\n");
        return;
    }

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
    if (head->is_empty) {
        printf("没有可统计的数据。\n");
        return;
    }

    int which = beforeInfo(head, "统计");
    if (which == -1) return;

    int attrIndexes[32];
    int numAttrs = 0;
    printf("请输入属性索引，输入-1结束：\n");

    while (true) {
        int attrIndex = selectSearchAttribute(which);
        attrIndexes[numAttrs++] = attrIndex;
        if (attrIndex == -1) break;
        else if (numAttrs >= 32) {
            printf("属性索引数量超过限制。\n");
            break;
        }
    }

    countCombinedAttributes(head, attrIndexes, numAttrs, which);
}

void presetStatistics(head_node *head) {
    if (head->is_empty) {
        printf("没有可统计的数据。\n");
        return;
    }

    printf("预设统计选项：\n");
    printf("1. 按区域统计客户\n");
    printf("2. 按区域和地址统计客户\n");
    printf("3. 按规模与联系程度统计客户\n");
    printf("4. 按性别统计联络员\n");
    printf("5. 按性别统计业务员\n");
    printf("请选择一个操作（1-5）：");

    char choice[MAX_LENGTH];
    getInput(choice, sizeof(choice));

    int attrIndexes[3];  // 最多两个属性

    if (!isOneChar(choice)) {
        printf("无效的选择。\n");
        return;
    }
    switch (choice[0]) {
    case '1':
        // 按区域统计客户
        countAttributes(head, 1, 0); // 1 是区域属性索引，0 是客户类型
        break;
    case '2':
        // 按区域和地址统计客户
        attrIndexes[0] = 1;
        attrIndexes[1] = 2;
        attrIndexes[2] = -1;
        countCombinedAttributes(head, attrIndexes, 3, 0); // 0 是客户类型
        break;
    case '3':
        // 按规模与联系程度统计客户
        attrIndexes[0] = 4; // 规模
        attrIndexes[1] = 5; // 联系程度
        attrIndexes[2] = -1;
        countCombinedAttributes(head, attrIndexes, 3, 0); // 0 是客户类型
        break;
    case '4':
        // 按性别统计联络员
        countAttributes(head, 1, 1); // 1 是性别属性索引，1 是联络人类型
        break;
    case '5':
        // 按性别统计业务员
        countAttributes(head, 1, 2); // 1 是性别属性索引，2 是业务员类型
        break;
    default:
        printf("无效的选择。\n");
        break;
    }
}

void conditionalStatistics(head_node *head) {
    if (head->is_empty) {
        printf("没有可统计的数据。\n");
        return;
    }

    int which = beforeInfo(head, "统计");
    if (which == -1) return;  // 无效的选择

    int attrIndexes[32]; // 存储属性索引
    char conditionValues[32][MAX_LENGTH]; // 存储每个属性的条件值
    int numConditions = 0; // 条件数量

    printf("请输入属性索引和条件值，输入-1结束索引输入：\n");
    while (true) {
        printf("属性索引：\n");
        int attrIndex = selectSearchAttribute(which);
        if (attrIndex == -1) break;
        attrIndexes[numConditions] = attrIndex;

        printf("条件值：");
        getInput(conditionValues[numConditions], sizeof(conditionValues[numConditions]));
        numConditions++;

        if (numConditions >= 32) {
            printf("条件数量超过限制。\n");
            break;
        }
    }

    countAttributesByConditions(head, attrIndexes, conditionValues, numConditions, which);
}

void countAttributesByConditions(head_node *head, int *attrIndexes, char conditionValues[][MAX_LENGTH], int numConditions, int which) {
    AttributeCount counts[MAX_LENGTH];
    int uniqueCount = 0;
    bool found;
    bool match;

    switch (which) {
    case 0: // 客户
        for (node_cus *node = head->next_cus; node != NULL; node = node->next) {
            match = true;
            char combinedAttributes[MAX_LENGTH * 10] = "";
            for (int i = 0; i < numConditions; ++i) {
                char *attr = getCustomerAttribute(&node->customer, attrIndexes[i]);
                if (strcmp(attr, conditionValues[i]) != 0) {
                    match = false;
                    break;
                }
                strcat(combinedAttributes, attr);
                if (i < numConditions - 1) {
                    strcat(combinedAttributes, " | ");
                }
            }

            if (match) {
                found = false;
                for (int i = 0; i < uniqueCount; ++i) {
                    if (strcmp(counts[i].value, combinedAttributes) == 0) {
                        ++counts[i].count;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    strcpy(counts[uniqueCount].value, combinedAttributes);
                    counts[uniqueCount].count = 1;
                    ++uniqueCount;
                }
            }
        }
        break;
    case 1: // 联络人
        for (node_ctp *node = head->next_ctp; node != NULL; node = node->next) {
            match = true;
            char combinedAttributes[MAX_LENGTH * 10] = "";
            for (int i = 0; i < numConditions; ++i) {
                char *attr = getContactPersonAttribute(&node->contactPerson, attrIndexes[i]);
                if (strcmp(attr, conditionValues[i]) != 0) {
                    match = false;
                    break;
                }
                strcat(combinedAttributes, attr);
                if (i < numConditions - 1) {
                    strcat(combinedAttributes, " | ");
                }
            }

            if (match) {
                found = false;
                for (int i = 0; i < uniqueCount; ++i) {
                    if (strcmp(counts[i].value, combinedAttributes) == 0) {
                        ++counts[i].count;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    strcpy(counts[uniqueCount].value, combinedAttributes);
                    counts[uniqueCount].count = 1;
                    ++uniqueCount;
                }
            }
        }
        break;
    case 2: // 业务员
        for (node_emp *node = head->next_emp; node != NULL; node = node->next) {
            match = true;
            char combinedAttributes[MAX_LENGTH * 10] = "";
            for (int i = 0; i < numConditions; ++i) {
                char *attr = getEmployeeAttribute(&node->employee, attrIndexes[i]);
                if (strcmp(attr, conditionValues[i]) != 0) {
                    match = false;
                    break;
                }
                strcat(combinedAttributes, attr);
                if (i < numConditions - 1) {
                    strcat(combinedAttributes, " | ");
                }
            }

            if (match) {
                found = false;
                for (int i = 0; i < uniqueCount; ++i) {
                    if (strcmp(counts[i].value, combinedAttributes) == 0) {
                        ++counts[i].count;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    strcpy(counts[uniqueCount].value, combinedAttributes);
                    counts[uniqueCount].count = 1;
                    ++uniqueCount;
                }
            }
        }
        break;
    }

    printf("条件统计结果：\n");
    for (int i = 0; i < uniqueCount; i++) {
        printf("%s: %d\n", counts[i].value, counts[i].count);
    }
    if (uniqueCount == 0) printf("无符合条件的结果！\n");
    printf("统计完毕！\n");
}

void countCombinedAttributes(head_node *head, int *attrIndexes, int numAttrs, int which) {
    AttributeCount counts[MAX_LENGTH];
    int uniqueCount = 0;
    bool found;

    switch (which) {
    case 0: // 客户
        for (node_cus *node = head->next_cus; node != NULL; node = node->next) {
            char combinedAttributes[MAX_LENGTH * 10] = "";
            for (int i = 0; i < numAttrs - 1; ++i) {
                char *attr = getCustomerAttribute(&node->customer, attrIndexes[i]);
                strcat(combinedAttributes, attr);
                if (i < numAttrs - 1) {
                    strcat(combinedAttributes, " | ");
                }
            }

            found = false;
            for (int i = 0; i < uniqueCount; ++i) {
                if (strcmp(counts[i].value, combinedAttributes) == 0) {
                    ++counts[i].count;
                    found = true;
                    break;
                }
            }
            if (!found) {
                strcpy(counts[uniqueCount].value, combinedAttributes);
                counts[uniqueCount].count = 1;
                ++uniqueCount;
            }
        }
        break;
    case 1: // 联络人
        for (node_ctp *node = head->next_ctp; node != NULL; node = node->next) {
            char combinedAttributes[MAX_LENGTH * 10] = "";
            for (int i = 0; i < numAttrs - 1; ++i) {
                char *attr = getContactPersonAttribute(&node->contactPerson, attrIndexes[i]);
                strcat(combinedAttributes, attr);
                if (i < numAttrs - 1) {
                    strcat(combinedAttributes, " | ");
                }
            }

            found = false;
            for (int i = 0; i < uniqueCount; ++i) {
                if (strcmp(counts[i].value, combinedAttributes) == 0) {
                    ++counts[i].count;
                    found = true;
                    break;
                }
            }
            if (!found) {
                strcpy(counts[uniqueCount].value, combinedAttributes);
                counts[uniqueCount].count = 1;
                ++uniqueCount;
            }
        }
    case 2: // 业务员
        for (node_emp *node = head->next_emp; node != NULL; node = node->next) {
            char combinedAttributes[MAX_LENGTH * 10] = "";
            for (int i = 0; i < numAttrs - 1; ++i) {
                char *attr = getEmployeeAttribute(&node->employee, attrIndexes[i]);
                strcat(combinedAttributes, attr);
                if (i < numAttrs - 1) {
                    strcat(combinedAttributes, " | ");
                }
            }

            found = false;
            for (int i = 0; i < uniqueCount; ++i) {
                if (strcmp(counts[i].value, combinedAttributes) == 0) {
                    ++counts[i].count;
                    found = true;
                    break;
                }
            }
            if (!found) {
                strcpy(counts[uniqueCount].value, combinedAttributes);
                counts[uniqueCount].count = 1;
                ++uniqueCount;
            }
        }
        break;
    }

    printf("组合统计结果：\n");
    for (int i = 0; i < uniqueCount; i++) {
        printf("%s: %d\n", counts[i].value, counts[i].count);
    }
    if (uniqueCount == 0) printf("无符合条件的结果！\n");
    printf("统计完毕！\n");
}

void countAttributes(head_node *head, int attrIndex, int which) {
    // 用于存储每个唯一值及其出现次数的结构

    AttributeCount counts[MAX_LENGTH];
    int uniqueCount = 0;
    bool found;
    char *attributeValue;

    switch (which) {
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
        printf("%s: %d\n", counts[i].value, counts[i].count);
    }
    if (uniqueCount == 0) printf("无符合条件的结果！\n");
    printf("统计完毕！\n");
}

char* getCustomerAttribute(Customer *customer, int attrIndex) {
    switch (attrIndex) {
    case 0: return isSameString(customer->name, " ") ? "空值" : customer->name;
    case 1: return isSameString(customer->region, " ") ? "空值" : customer->region;
    case 2: return isSameString(customer->address, " ") ? "空值" : customer->address;
    case 3: return isSameString(customer->legalRepresentative, " ") ? "空值" : customer->legalRepresentative;
    case 4: return isSameString(customer->scale, " ") ? "空值" : customer->scale;
    case 5: return isSameString(customer->businessContactLevel, " ") ? "空值" : customer->businessContactLevel;
    case 6: return isSameString(customer->email, " ") ? "空值" : customer->email;
    case 7: return isSameString(customer->phone, " ") ? "空值" : customer->phone;
    default: return "空值";
    }
}

char* getContactPersonAttribute(ContactPerson *contact, int attrIndex) {
    switch (attrIndex) {
    case 0: return isSameString(contact->name, " ") ? "空值" : contact->name;
    case 1: return isSameString(contact->gender, " ") ? "空值" : contact->gender;
    case 2: return isSameString(contact->birthday, " ") ? "空值" : contact->birthday;
    case 3: return isSameString(contact->email, " ") ? "空值" : contact->email;
    case 4: return isSameString(contact->phone, " ") ? "空值" : contact->phone;
    case 5: return isSameString(contact->representative, " ") ? "空值" : contact->representative;
    default: return "空值";
    }
}

char* getEmployeeAttribute(Employee *employee, int attrIndex) {
    switch (attrIndex) {
    case 0: return isSameString(employee->name, " ") ? "空值" : employee->name;
    case 1: return isSameString(employee->gender, " ") ? "空值" : employee->gender;
    case 2: return isSameString(employee->birthday, " ") ? "空值" : employee->birthday;
    case 3: return isSameString(employee->email, " ") ? "空值" : employee->email;
    case 4: return isSameString(employee->phone, " ") ? "空值" : employee->phone;
    case 5: return isSameString(employee->representative, " ") ? "空值" : employee->representative;
    default: return "空值";
    }
}

// end widgets/info_statistics.c
