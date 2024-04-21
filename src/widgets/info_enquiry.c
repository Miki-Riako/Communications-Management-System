// widgets/info_enquiry.c
#include "../header.h"

void infoEnquiryWidget();
int selectSearchAttribute(int which);
bool searchOnes(head_node *head, head_node *copyList, char *query, int attrIndex, int which, int how);
bool howToSearch(const char *toCompare, const char *query, int how);
void simpleQuery(head_node *head);
// bool matchNode(void *node, int query, int attrIndex, int which, int method);
void combinedQuery(head_node *head);
// void updateTempList(head_node *currentHead, head_node *tempHead, char *query, int attrIndex, int method, int which);
void fuzzyQuery(head_node *head);

void infoEnquiryWidget() {
    initializeAll();
    printf("正在加载中，请您耐心等待。\n");
    head_node *head = (head_node *)malloc(sizeof(head_node));  // 分配内存
    if (!head) {
        fprintf(stderr, "内存分配失败！\n");
        return;
    }
    loadFile(head);  // 加载数据
    if (head->is_empty) printf("没有加载到任何数据。\n");
    else printf("数据加载成功！\n");

    while (true) {
        printf("\n信息查询系统\n");
        printf("1. 简单查询\n");
        printf("2. 组合查询\n");
        printf("3. 模糊查询\n");
        printf("4. 返回\n");
        printf("请选择一个操作：（1-4）");
        
        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);
        
        if (!isOneChar(get)) {
            printf("无效的选择，请重新输入。\n");
            continue;
        }
        switch (get[0]) {
        case '1':
            simpleQuery(head);
            break;
        case '2':
            combinedQuery(head);
            break;
        case '3':
            fuzzyQuery(head);
            break;
        case '4':
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

int selectSearchAttribute(int which) {
    char index = '6';
    switch (which) {
    case 0: // 客户
        printf("1. 名称\n2. 地区\n3. 地址\n4. 法人\n5. 规模\n6. 联系等级\n7. 邮箱\n8. 电话\n");
        index = '8';
        break;
    case 1: // 联络人
    case 2: // 业务员
        printf("1. 名称\n2. 性别\n3. 生日\n4. 邮箱\n5. 电话\n6. 代表公司\n");
        break;
    }
    char get[MAX_LENGTH];
    infoInput(get, sizeof(get), "请选择属性以进行搜索：\n");
    if (!isOneChar(get) || get[0] < '1' || get[0] > index) {
        printf("无效的选择\n");
        return -1;
    } else {
        return charToInt(get[0]) - 1;
    }
}

bool searchOnes(head_node *head, head_node *copyList, char *query, int attrIndex, int which, int how) {
    // 如果copyList是NULL，就不会执行复制结点到另一个链表的操作
    bool found = false;
    switch (which) {
    case 0: // 客户
        node_cus *cusNode = head->next_cus;
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
        node_ctp *ctpNode = head->next_ctp;
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
        node_emp *empNode = head->next_emp;
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
    }
}

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

void simpleQuery(head_node *head) {
    int which = beforeInfo(head, "查询");
    if (which == -1) return;  // 无效的查询类型或无数据类型被选中

    char queryValue[MAX_LENGTH];
    bool found = false;
    int attributeIndex = selectSearchAttribute(which);

    if (attributeIndex == -1) {
        printf("无效的属性选择。\n");
        return;
    }

    // 获取用户想要搜索的值
    infoInput(queryValue, sizeof(queryValue), "请输入搜索值：");

    // 根据用户选择决定查询内容和显示格式
    printHeading(which);
    found = searchOnes(head, NULL, queryValue, attributeIndex, which, 0);
    if (!found) {
        printf("没有找到匹配的信息。\n");
    }
}

void combinedQuery(head_node *head) {
    // 多一个链表，A链表符合条件的放到B链表，还搜的话就B链表变A链表，继续以此类推
    int which = beforeInfo(head, "查询");
    if (which == -1) return;  // 无效的查询类型或无数据类型被选中
    
    bool first = true;
    head_node *headA = (head_node *)malloc(sizeof(head_node));  // 分配内存
    head_node *headB = (head_node *)malloc(sizeof(head_node));  // 分配内存
    if (!headA || !headB) {
        fprintf(stderr, "内存分配失败！\n");
        return;
    }
    initializeHeadNode(headA);
    initializeHeadNode(headB);

    while (true) {
        char queryValue[MAX_LENGTH];
        char searchType[MAX_LENGTH];
        bool found = false;
        int attributeIndex = selectSearchAttribute(which);

        if (attributeIndex == -1) {
            printf("无效的属性选择。\n");
            return;
        }

        // 获取用户想要搜索的值
        infoInput(queryValue, sizeof(queryValue), "请输入搜索值：");
        infoInput(searchType, sizeof(searchType), "请输入搜索方式 (0: 精确查询, 1: 模糊查询):\n");
        if (!isOneChar(searchType) || (charToInt(searchType[0]) < 0 || charToInt(searchType[0]) > 1)) {
            printf("错误的搜索方式！\n");
            continue;
        }
        // 根据用户选择决定查询内容和显示格
        printHeading(which);
        if (first) {
            found = searchOnes(head, headB, queryValue, attributeIndex, which, charToInt(searchType[0]));
        } else {
            found = searchOnes(headA, headB, queryValue, attributeIndex, which, charToInt(searchType[0]));
        }
        if (!found) {
            printf("没有找到匹配的信息。\n");
        }

        printf("是否继续查询？(y):\n");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);
        
        if (!isOneChar(get)) {
            break;
        } else if (get[0] != 'y'&& get[0] != 'Y') {
            break;
        } else {
            swapLists(&headA, &headB);
            if (!first) {
                clearList(headB);
            }
        }
        first = false;
    }

    freeAll(headA);
    freeAll(headB);
}

void fuzzyQuery(head_node *head) {
    int which = beforeInfo(head, "查询");
    if (which == -1) return;

    char queryValue[MAX_LENGTH];
    bool found = false;
    int attributeIndex = selectSearchAttribute(which);

    if (attributeIndex == -1) {
        printf("无效的属性选择。\n");
        return;
    }

    // 获取用户想要搜索的值
    infoInput(queryValue, sizeof(queryValue), "请输入搜索值：");

    // 根据用户选择决定查询内容和显示格式
    printHeading(which);
    found = searchOnes(head, NULL, queryValue, attributeIndex, which, 1);
    if (!found) {
        printf("没有找到匹配的信息。\n");
    }
}

// end widgets/info_enquiry.c