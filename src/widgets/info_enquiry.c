// widgets/info_enquiry.c
#include "../header.h"

void infoEnquiryWidget();
void simpleQuery(head_node *head);
void combinedQuery(head_node *head);
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

void simpleQuery(head_node *head) {
    if (head == NULL || head->is_empty) {
        printf("没有可查询的数据。\n");
        return;
    }
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
    if (head == NULL || head->is_empty) {
        printf("没有可查询的数据。\n");
        return;
    }
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
        if (!performQueryIteration(head, &headA, &headB, which, &first)) break;
    }

    freeAll(headA);
    freeAll(headB);
}

void fuzzyQuery(head_node *head) {
    if (head == NULL || head->is_empty) {
        printf("没有可查询的数据。\n");
        return;
    }
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