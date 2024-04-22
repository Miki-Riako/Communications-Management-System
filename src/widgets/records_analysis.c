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
    if (head == NULL || head->is_empty) {
        printf("没有可查询的数据。\n");
        return;
    }
    
    char queryValue[MAX_LENGTH];
    bool found = false;
    bool first = true;
    int attributeIndex = -1;
    head_node *headA;  // 分配内存
    head_node *headB;  // 分配内存

    while (true) {
        printf("\n信息查询\n");
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
            attributeIndex = selectSearchAttribute(3);
            if (attributeIndex == -1) {
                printf("无效的属性选择。\n");
                return;
            }
            infoInput(queryValue, sizeof(queryValue), "请输入搜索值：");
            printHeading(3);
            found = searchOnes(head, NULL, queryValue, attributeIndex, 3, 0);
            if (!found) {
                printf("没有找到匹配的信息。\n");
            }
            break;
        case '2':
            first = true;
            headA = (head_node *)malloc(sizeof(head_node));  // 分配内存
            headB = (head_node *)malloc(sizeof(head_node));  // 分配内存
            if (!headA || !headB) {
                fprintf(stderr, "内存分配失败！\n");
                return;
            }
            initializeHeadNode(headA);
            initializeHeadNode(headB);
            while (true) {
                if (!performQueryIteration(head, &headA, &headB, 3, &first)) break;
            }
            freeAll(headA);
            freeAll(headB);
            break;
        case '3':
            attributeIndex = selectSearchAttribute(3);
            if (attributeIndex == -1) {
                printf("无效的属性选择。\n");
                return;
            }
            infoInput(queryValue, sizeof(queryValue), "请输入搜索值：");
            printHeading(3);
            found = searchOnes(head, NULL, queryValue, attributeIndex, 3, 1);
            if (!found) {
                printf("没有找到匹配的信息。\n");
            }
            break;
        case '4':
            return;
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
    }
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
    if (head->is_empty) {
        printf("没有可统计的数据。\n");
        return;
    }
    int attrIndex = -1;
    int numAttrs = 0;
    int attrIndexes[32];
    char conditionValues[32][MAX_LENGTH]; // 存储每个属性的条件值
    int numConditions = 0; // 条件数量
    while (true) {
        printf("\n信息统计\n");
        printf("1. 简单统计\n");
        printf("2. 组合统计\n");
        printf("3. 预设统计\n");
        printf("4. 条件统计\n");
        printf("5. 返回\n");
        printf("请选择一个操作（1-5）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);
        char choice[MAX_LENGTH];
        bool print = false;

        switch (get[0]) {
        case '1':
            attrIndex = selectSearchAttribute(3);
            if (attrIndex == -1) {
                printf("无效的属性选择。\n");
                break;
            }
            countAttributes(head, attrIndex, 3);
            break;
        case '2':
            printf("请输入属性索引，输入-1结束：\n");
            print = false;
            while (true) {
                attrIndex = selectSearchAttribute(3);
                attrIndexes[numAttrs++] = attrIndex;
                if (attrIndex == -1) break;
                else if (numAttrs >= 32) {
                    printf("属性索引数量超过限制。\n");
                    break;
                }
                print = true;
            }
            countCombinedAttributes(head, attrIndexes, numAttrs, 3);
            break;
        case '3':
            printf("预设统计选项：\n");
            printf("1. 按客户公司统计\n");
            printf("2. 按通信内容统计\n");
            printf("请选择一个操作（1-2）：");

            getInput(choice, sizeof(choice));

            if (!isOneChar(choice)) {
                printf("无效的选择。\n");
                break;
            }
            switch (choice[0]) {
            case '1':
                countAttributes(head, 1, 3); // 1 是索引，3 是类型
                break;
            case '2':
                countAttributes(head, 6, 3); // 6 是索引，3 是类型
                break;
            default:
                printf("无效的选择。\n");
                break;
            }
            break;
        case '4':
            printf("请输入属性索引和条件值，输入-1结束索引输入：\n");
            print = false;
            while (true) {
                printf("属性索引：\n");
                int attrIndex = selectSearchAttribute(3);
                if (attrIndex == -1) break;
                attrIndexes[numConditions] = attrIndex;
                print = true;

                printf("条件值：");
                getInput(conditionValues[numConditions], sizeof(conditionValues[numConditions]));
                ++numConditions;

                if (numConditions >= 32) {
                    printf("条件数量超过限制。\n");
                    break;
                }
            }
            if (print) countAttributesByConditions(head, attrIndexes, conditionValues, numConditions, 3);
            break;
        case '5':
            return;
        default:
            printf("无效的选择，请重新输入。\n");
        }
    }
}

// end widgets/records_analysis.c
