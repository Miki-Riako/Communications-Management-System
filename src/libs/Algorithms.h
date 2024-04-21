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
    switch (attrIndex) {
    case 0: attrA = a->record.user; attrB = b->record.user; break;
    case 1: attrA = a->record.companyName; attrB = b->record.companyName; break;
    case 2: attrA = a->record.contactName; attrB = b->record.contactName; break;
    case 3: attrA = a->record.date; attrB = b->record.date; break;
    case 4: attrA = a->record.time; attrB = b->record.time; break;
    case 5: attrA = a->record.duration; attrB = b->record.duration; break;
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