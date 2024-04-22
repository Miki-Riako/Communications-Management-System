// 选择搜索逻辑
bool howToSearch(const char *toCompare, const char *query, int how) {
    switch (how) {
    case 0:  // 完全匹配
        return isSameString(toCompare, query);
    case 1:
        return strstr(toCompare, query) != NULL;
    default:
        printf("无效的属性选择。\n");
        return false;
    }
}

// 搜索实现
bool searchOnes(head_node *head, head_node *copyList, char *query, int attrIndex, int which, int how) {
    // 如果copyList是NULL，就不会执行复制结点到另一个链表的操作
    bool found = false;
    node_cus *cusNode = NULL;
    node_ctp *ctpNode = NULL;
    node_emp *empNode = NULL;
    node_rec *recNode = NULL;

    switch (which) {
    case 0: // 客户
        cusNode = head->next_cus;
        while (cusNode) {
            char *toCompare = NULL;
            switch (attrIndex) {
            case 0:
                toCompare = cusNode->customer.name;
                break;
            case 1:
                toCompare = cusNode->customer.region;
                break;
            case 2:
                toCompare = cusNode->customer.address;
                break;
            case 3:
                toCompare = cusNode->customer.legalRepresentative;
                break;
            case 4:
                toCompare = cusNode->customer.scale;
                break;
            case 5:
                toCompare = cusNode->customer.businessContactLevel;
                break;
            case 6:
                toCompare = cusNode->customer.email;
                break;
            case 7:
                toCompare = cusNode->customer.phone;
                break;
            default:
                printf("无效的属性选择。\n");
                return false;
            }
            if (toCompare && howToSearch(toCompare, query, how)) {
                printNode_cus(cusNode);
                found = true;
                if (copyList) {
                    node_cus *newNode = copyNode_cus(cusNode);
                    linkNode_cus(copyList, newNode);
                }
            }
            cusNode = cusNode->next;
        }
        return found;
    case 1: // 联络人
        ctpNode = head->next_ctp;
        while (ctpNode) {
            char *toCompare = NULL;
            switch (attrIndex) {
            case 0:
                toCompare = ctpNode->contactPerson.name;
                break;
            case 1:
                toCompare = ctpNode->contactPerson.gender;
                break;
            case 2:
                toCompare = ctpNode->contactPerson.birthday;
                break;
            case 3:
                toCompare = ctpNode->contactPerson.email;
                break;
            case 4:
                toCompare = ctpNode->contactPerson.phone;
                break;
            case 5:
                toCompare = ctpNode->contactPerson.representative;
                break;
            default:
                printf("无效的属性选择。\n");
                return false;
            }
            if (toCompare && howToSearch(toCompare, query, how)) {
                printNode_ctp(ctpNode);
                found = true;
                if (copyList) {
                    node_ctp *newNode = copyNode_ctp(ctpNode);
                    linkNode_ctp(copyList, newNode);
                }
            }
            ctpNode = ctpNode->next;
        }
        return found;
    case 2: // 业务员
        empNode = head->next_emp;
        while (empNode) {
            char *toCompare = NULL;
            switch (attrIndex) {
            case 0:
                toCompare = empNode->employee.name;
                break;
            case 1:
                toCompare = empNode->employee.gender;
                break;
            case 2:
                toCompare = empNode->employee.birthday;
                break;
            case 3:
                toCompare = empNode->employee.email;
                break;
            case 4:
                toCompare = empNode->employee.phone;
                break;
            case 5:
                toCompare = empNode->employee.representative;
                break;
            default:
                printf("无效的属性选择。\n");
                return false;
            }
            if (toCompare && howToSearch(toCompare, query, how)) {
                printNode_emp(empNode);
                found = true;
                if (copyList) {
                    node_emp *newNode = copyNode_emp(empNode);
                    linkNode_emp(copyList, newNode);
                }
            }
            empNode = empNode->next;
        }
        return found;
    case 3: // 通信记录
        recNode = head->next_rec;
        while (recNode) {
            char *toCompare = NULL;
            switch (attrIndex) {
            case 0:
                toCompare = recNode->record.user;
                break;
            case 1:
                toCompare = recNode->record.companyName;
                break;
            case 2:
                toCompare = recNode->record.contactName;
                break;
            case 3:
                toCompare = recNode->record.date;
                break;
            case 4:
                toCompare = recNode->record.time;
                break;
            case 5:
                toCompare = recNode->record.duration;
                break;
            case 6:
                toCompare = recNode->record.content;
                break;
            default:
                printf("无效的属性选择。\n");
                return false;
            }
            if (toCompare && howToSearch(toCompare, query, how)) {
                printNode_rec(recNode);
                found = true;
                if (copyList) {
                    node_rec *newNode = copyNode_rec(recNode);
                    linkNode_rec(copyList, newNode);
                }
            }
            recNode = recNode->next;
        }
        return found;
    }
}

// 帮助搜索的链表AB来回倒的函数
bool performQueryIteration(head_node *head, head_node **headA, head_node **headB, int which, bool *first) {
    char queryValue[MAX_LENGTH];
    char searchType[MAX_LENGTH];
    bool found = false;
    int attributeIndex = selectSearchAttribute(which);
    if (attributeIndex == -1) {
        printf("无效的属性选择。\n");
        return false;
    }

    // 获取用户想要搜索的值
    infoInput(queryValue, sizeof(queryValue), "请输入搜索值：");
    infoInput(searchType, sizeof(searchType), "请输入搜索方式 (0: 精确查询, 1: 模糊查询):\n");
    if (!isOneChar(searchType) || (charToInt(searchType[0]) < 0 || charToInt(searchType[0]) > 1)) {
        printf("错误的搜索方式！\n");
        return false;
    }

    // 根据用户选择决定查询内容和显示格
    printHeading(which);
    if (*first) {
        found = searchOnes(head, *headB, queryValue, attributeIndex, which, charToInt(searchType[0]));
    } else {
        found = searchOnes(*headA, *headB, queryValue, attributeIndex, which, charToInt(searchType[0]));
    }
    if (!found) {
        printf("没有找到匹配的信息。\n");
    }

    printf("是否继续查询？(y):\n");
    char get[MAX_LENGTH];
    getInput(get, sizeof(get));
    system(SYSTEM_CLEAR);

    if (!isOneChar(get) || (get[0] != 'y' && get[0] != 'Y')) {
        return false;
    }

    swapLists(headA, headB);
    if (!*first) {
        clearList(*headB);
    }
    *first = false;
    return true;
}

// 特殊比较
int mapScaleToPriority(const char *scale) {
    if (strcmp(scale, "大") == 0) return 3;
    if (strcmp(scale, "中") == 0) return 2;
    if (strcmp(scale, "小") == 0) return 1;
    return 0; // 默认对于空字符串或无效输入
}
int mapContactLevelToPriority(const char *level) {
    if (strcmp(level, "高") == 0) return 3;
    if (strcmp(level, "中") == 0) return 2;
    if (strcmp(level, "低") == 0) return 1;
    return 0; // 默认对于空字符串或无效输入
}
// 根据客户名称字典序进行比较（1，升序；0，降序）
bool compareNodeCus(node_cus *a, node_cus *b, int attrIndex, bool ascending) {
    char *attrA, *attrB;
    int compareResult = 0;
    switch (attrIndex) {
    case 0: attrA = a->customer.name; attrB = b->customer.name; break;
    case 1: attrA = a->customer.region; attrB = b->customer.region; break;
    case 2: attrA = a->customer.address; attrB = b->customer.address; break;
    case 3: attrA = a->customer.legalRepresentative; attrB = b->customer.legalRepresentative; break;
    case 4:  // 特殊比较：规模
        compareResult = mapScaleToPriority(a->customer.scale) - mapScaleToPriority(b->customer.scale);
        break;
    case 5: // 特殊比较：联系程度
        compareResult = mapContactLevelToPriority(a->customer.businessContactLevel) - mapContactLevelToPriority(b->customer.businessContactLevel);
        break;
    case 6: attrA = a->customer.email; attrB = b->customer.email; break;
    case 7: attrA = a->customer.phone; attrB = b->customer.phone; break;
    default: return false;
    }
    if (attrIndex == 4 || attrIndex == 5) {
        return ascending ? (compareResult > 0) : (compareResult < 0);
    } else {
        return ascending ? (strcmp(attrA, attrB) > 0) : (strcmp(attrA, attrB) < 0);
    }
}
bool compareNodeCtp(node_ctp *a, node_ctp *b, int attrIndex, bool ascending) {
    char *attrA, *attrB;
    switch (attrIndex) {
    case 0: attrA = a->contactPerson.name; attrB = b->contactPerson.name; break;
    case 1: attrA = a->contactPerson.gender; attrB = b->contactPerson.gender; break;
    case 2: attrA = a->contactPerson.birthday; attrB = b->contactPerson.birthday; break;
    case 3: attrA = a->contactPerson.email; attrB = b->contactPerson.email; break;
    case 4: attrA = a->contactPerson.phone; attrB = b->contactPerson.phone; break;
    case 5: attrA = a->contactPerson.representative; attrB = b->contactPerson.representative; break;
    default: return false;
    }
    return ascending ? (strcmp(attrA, attrB) > 0) : (strcmp(attrA, attrB) < 0);
}
bool compareNodeEmp(node_emp *a, node_emp *b, int attrIndex, bool ascending) {
    char *attrA, *attrB;
    switch (attrIndex) {
    case 0: attrA = a->employee.name; attrB = b->employee.name; break;
    case 1: attrA = a->employee.gender; attrB = b->employee.gender; break;
    case 2: attrA = a->employee.birthday; attrB = b->employee.birthday; break;
    case 3: attrA = a->employee.email; attrB = b->employee.email; break;
    case 4: attrA = a->employee.phone; attrB = b->employee.phone; break;
    case 5: attrA = a->employee.representative; attrB = b->employee.representative; break;
    default: return false;
    }
    return ascending ? (strcmp(attrA, attrB) > 0) : (strcmp(attrA, attrB) < 0);
}
bool compareNodeRec(node_rec *a, node_rec *b, int attrIndex, bool ascending) {
    char *attrA, *attrB;
    int intA, intB;
    switch (attrIndex) {
    case 0: attrA = a->record.user; attrB = b->record.user; break;
    case 1: attrA = a->record.companyName; attrB = b->record.companyName; break;
    case 2: attrA = a->record.contactName; attrB = b->record.contactName; break;
    case 3: attrA = a->record.date; attrB = b->record.date; break;
    case 4: attrA = a->record.time; attrB = b->record.time; break;
    case 5:
        // 处理duration作为整数比较
        intA = atoi(a->record.duration); // 将duration字符串转换为整数
        intB = atoi(b->record.duration);
        if (ascending) {
            return intA > intB;
        } else {
            return intA < intB;
        }
    case 6: attrA = a->record.content; attrB = b->record.content; break;
    default: return false;
    }
    return ascending ? (strcmp(attrA, attrB) > 0) : (strcmp(attrA, attrB) < 0);
}
// 冒泡排序函数
void sort(int which, head_node *head, int attrIndex, bool ascending) {
    if (head == NULL) {
        return; // 链表为空
    }
    bool swapped;
    switch (which) {
    case 0: // 客户
        if (head->next_cus == NULL) {
            return;
        }
        node_cus **current;
        do {
            swapped = false;
            current = &head->next_cus; // 从头节点的next开始

            while ((*current) != NULL && (*current)->next != NULL) {
                if (compareNodeCus(*current, (*current)->next, attrIndex, ascending)) {
                    // 交换节点
                    node_cus *tmp = (*current)->next;
                    (*current)->next = tmp->next;
                    tmp->next = *current;
                    *current = tmp;

                    swapped = true;
                }
                current = &((*current)->next);
            }
        } while (swapped);
        break;
    case 1: // 联络人
        if (head->next_ctp == NULL) {
            return;
        }
        node_ctp **ctpCurrent;
        do {
            swapped = false;
            ctpCurrent = &head->next_ctp; // 从头节点的next开始

            while ((*ctpCurrent) != NULL && (*ctpCurrent)->next != NULL) {
                if (compareNodeCtp(*ctpCurrent, (*ctpCurrent)->next, attrIndex, ascending)) {
                    // 交换节点
                    node_ctp *tmp = (*ctpCurrent)->next;
                    (*ctpCurrent)->next = tmp->next;
                    tmp->next = *ctpCurrent;
                    *ctpCurrent = tmp;

                    swapped = true;
                }
                ctpCurrent = &((*ctpCurrent)->next);
            }
        } while (swapped);
        break;
    case 2: // 业务员
        if (head->next_emp == NULL) {
            return;
        }
        node_emp **empCurrent;
        do {
            swapped = false;
            empCurrent = &head->next_emp; // 从头节点的next开始

            while ((*empCurrent) != NULL && (*empCurrent)->next != NULL) {
                if (compareNodeEmp(*empCurrent, (*empCurrent)->next, attrIndex, ascending)) {
                    // 交换节点
                    node_emp *tmp = (*empCurrent)->next;
                    (*empCurrent)->next = tmp->next;
                    tmp->next = *empCurrent;
                    *empCurrent = tmp;

                    swapped = true;
                }
                empCurrent = &((*empCurrent)->next);
            }
        } while (swapped);
        break;
    case 3: // 通信记录
        if (head->next_rec == NULL) {
            return;
        }
        node_rec **recCurrent;
        do {
            swapped = false;
            recCurrent = &head->next_rec; // 从头节点的next开始

            while ((*recCurrent) != NULL && (*recCurrent)->next != NULL) {
                if (compareNodeRec(*recCurrent, (*recCurrent)->next, attrIndex, ascending)) {
                    // 交换节点
                    node_rec *tmp = (*recCurrent)->next;
                    (*recCurrent)->next = tmp->next;
                    tmp->next = *recCurrent;
                    *recCurrent = tmp;

                    swapped = true;
                }
                recCurrent = &((*recCurrent)->next);
            }
        } while (swapped);
        break;
    default:
        break;
    }
}

// 排序前向用户确认信息的函数
void beforeSort(head_node *head, int which, int *attributeIndex, bool *isAscending) {
    while (true) {
        *attributeIndex = selectSearchAttribute(which);
        if (*attributeIndex == -1) {
            printf("无效的属性选择，请重新输入。\n");
        } else {
            break;
        }
    }

    char ascending[MAX_LENGTH];
    while (true) {
        printf("请输入排序方式（1升序/0降序）：");
        getInput(ascending, sizeof(ascending));
        if (!isOneChar(ascending)) {
            printf("无效的排序方式，请重新输入。\n");
        } else {
            break;
        }
    }
    *isAscending = charToInt(ascending[0]) == 0 ? false : true;
}

// 帮助组合排序的递归函数
void combinedSortHelper(head_node *head, int which) {
    int attributeIndex = 0;
    bool isAscending = false;

    beforeSort(head, which, &attributeIndex, &isAscending);

    char get[MAX_LENGTH];
    printf("是否继续添加排序条件？(y): ");
    getInput(get, sizeof(get));
    if (isOneChar(get) && (get[0] == 'y' || get[0] == 'Y')) {
        system(SYSTEM_CLEAR);
        combinedSortHelper(head, which);  // 递归调用以继续排序
    }

    // 先进后排序
    sort(which, head, attributeIndex, isAscending);
}

// 好用函数
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
    case 3: //通信记录
        for (node_rec *node = head->next_rec; node != NULL; node = node->next) {
            attributeValue = getRecordAttribute(&node->record, attrIndex);
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

// 组合统计函数
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
    case 3: // 通信记录
        for (node_rec *node = head->next_rec; node != NULL; node = node->next) {
            char combinedAttributes[MAX_LENGTH * 10] = "";
            for (int i = 0; i < numAttrs - 1; ++i) {
                char *attr = getRecordAttribute(&node->record, attrIndexes[i]);
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
    for (int i = 0; i < uniqueCount; ++i) {
        printf("%s: %d\n", counts[i].value, counts[i].count);
    }
    if (uniqueCount == 0) printf("无符合条件的结果！\n");
    printf("统计完毕！\n");
}

// 有条件搜索的逻辑
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
    case 3: // 通信记录
        for (node_rec *node = head->next_rec; node != NULL; node = node->next) {
            match = true;
            char combinedAttributes[MAX_LENGTH * 10] = "";
            for (int i = 0; i < numConditions; ++i) {
                char *attr = getRecordAttribute(&node->record, attrIndexes[i]);
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

// 好用函数
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
char* getRecordAttribute(Record *record, int attrIndex) {
    switch (attrIndex) {
    case 0: return isSameString(record->user, " ") ? "空值" : record->user;
    case 1: return isSameString(record->companyName, " ") ? "空值" : record->companyName;
    case 2: return isSameString(record->contactName, " ") ? "空值" : record->contactName;
    case 3: return isSameString(record->date, " ") ? "空值" : record->date;
    case 4: return isSameString(record->time, " ") ? "空值" : record->time;
    case 5: return isSameString(record->duration, " ") ? "空值" : record->duration;
    case 6: return isSameString(record->content, " ") ? "空值" : record->content;
    default: return "空值";
    }
}
