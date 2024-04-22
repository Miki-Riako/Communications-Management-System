// widgets/info_statistics.c
#include "../header.h"

void infoStatisticsWidget();
void simpleStatistics(head_node *head);
void combinedStatistics(head_node *head);
void presetStatistics(head_node *head);
void conditionalStatistics(head_node *head);

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
    bool print = false;

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
        print = true;
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
        if (IsManager) {
            countAttributes(head, 1, 1); // 1 是性别属性索引，1 是联络人类型
        } else {
            printf("您不是经理，没有权限执行此操作。\n");
        }
        break;
    case '5':
        // 按性别统计业务员
        if (IsManager) {
            countAttributes(head, 1, 2); // 1 是性别属性索引，2 是业务员类型
        } else {
            printf("您不是经理，没有权限执行此操作。\n");
        }
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
    bool print = false;

    printf("请输入属性索引和条件值，输入-1结束索引输入：\n");
    while (true) {
        printf("属性索引：\n");
        int attrIndex = selectSearchAttribute(which);
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

    if (print) countAttributesByConditions(head, attrIndexes, conditionValues, numConditions, which);
}

// end widgets/info_statistics.c
