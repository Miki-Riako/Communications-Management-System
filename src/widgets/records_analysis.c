// widgets/records_analysis.c
#include "../header.h"

void recordsAnalysisWidget(void);
void enquiryRecords(head_node *head);
void sortRecords(head_node *head);
void statisticsRecords(head_node *head);

void recordsAnalysisWidget(void) {
    initializeAll();
    printf("正在加载中，请您耐心等待。\n");
    head_node *head = (head_node *)malloc(sizeof(head_node));  // 分配内存
    if (!head) {
        fprintf(stderr, "内存分配失败！\n");
        return;
    }
    loadFile_record(head);  // 加载数据
    if (head->is_empty)  printf("没有加载到任何数据。\n");
    else printf("数据加载成功！\n");

    while (true) {
        printf("通信记录分析系统\n");
        printf("1. 查询通信记录\n");
        printf("2. 排序通信记录\n");
        printf("3. 统计通信情况\n");
        printf("4. 返回\n");
        printf("请选择一个操作（1-4）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);

        switch(get[0]) {
        case '1':
            enquiryRecords(head);
            break;
        case '2':
            sortRecords(head);
            break;
        case '3':
            statisticsRecords(head);
            break;
        case '4':
            printf("正在返回，请稍等。\n");
            free(head);
            printf("返回成功。\n");
            return;
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
    }
}

void enquiryRecords(head_node *head) {
    // 此处实现查询逻辑
    printf("查询通信记录的功能尚未实现。\n");
}

void sortRecords(head_node *head) {
    if (head == NULL || head->is_empty) {
        printf("没有可排序的数据。\n");
        return;
    }
    while (true) {
        printf("排序显示\n");
        printf("\n请选择排序类型：\n");
        printf("1. 显示当前排序\n");
        printf("2. 单一属性排序\n");
        printf("3. 多属性排序\n");
        printf("4. 返回\n");
        printf("请选择一个操作（1-4）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);

        int attributeIndex = 0;
        bool isAscending = false;

        if (!isOneChar(get)) {
            printf("无效的选择，请重新输入。\n");
            continue;
        }
        switch (get[0]) {
        case '1':
            printf("通信记录的信息列表：\n");
            printNodeList(head, 3);
            break;
        case '2':
            printf("通信记录的信息列表：\n");
            beforeSort(head, 3, &attributeIndex, &isAscending);
            sort(3, head, attributeIndex, isAscending);
            printNodeList(head, 3);
            break;
        case '3':
            combinedSortHelper(head, 3);
            system(SYSTEM_CLEAR);
            printNodeList(head, 3);
            break;
        case '4':
            return;
        default:
            printf("无效的选择，请重新输入。\n");
        }
    }
}

void statisticsRecords(head_node *head) {
    // 此处实现统计逻辑
    printf("统计通信情况的功能尚未实现。\n");
}








// end widgets/records_analysis.c
