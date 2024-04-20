// widgets/info_enquiry.c
#include "../header.h"

void infoEnquiryWidget();
void simpleQuery();
void combinedQuery();
void fuzzyQuery();

void infoEnquiryWidget() {
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
            simpleQuery();
            break;
        case '2':
            combinedQuery();
            break;
        case '3':
            fuzzyQuery();
            break;
        case '4':
            freeAll(head);
            return;
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
    }
}

void simpleQuery() {
    printf("执行简单查询...\n");
    // 实现具体的查询逻辑
}

void combinedQuery() {
    printf("执行组合查询...\n");
    // 实现具体的查询逻辑
}

void fuzzyQuery() {
    printf("执行模糊查询...\n");
    // 实现具体的查询逻辑
}


// end widgets/info_enquiry.c