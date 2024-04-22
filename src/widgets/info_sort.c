// widgets/info_sort.c
#include "../header.h"

void infoSortWidget();
void defaultSort(head_node *head);
void simpleSort(head_node *head);
void combinedSort(head_node *head);
void combinedSortHelper(head_node *head, int which);

void infoSortWidget() {
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
        printf("信息排序显示系统\n");
        printf("\n请选择数据的排序类型：\n");
        printf("1. 显示当前排序\n");
        printf("2. 单一属性排序\n");
        printf("3. 多属性排序\n");
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
            defaultSort(head);
            break;
        case '2':
            simpleSort(head);
            break;
        case '3':
            combinedSort(head);
            break;
        case '4':
            printf("正在返回，请稍等。\n");
            freeAll(head);
            printf("返回成功。\n");
            return;
        default:
            printf("无效的选择，请重新输入。\n");
        }
    }
}

void defaultSort(head_node *head) {
    int which = beforeInfo(head, "排序");
    if (which == -1) return;  // 选择无效

    switch (which) {
    case 0:
        printf("客户信息列表：\n");
        break;
    case 1:
        printf("联络人信息列表：\n");
        break;
    case 2:
        printf("业务员信息列表：\n");
        break;
    }
    printNodeList(head, which);
}

void simpleSort(head_node *head) {
    int which = beforeInfo(head, "排序");
    if (which == -1) return;  // 如果选择无效或不允许展示，则返回

    switch (which) {
    case 0:
        printf("客户信息列表：\n");
        break;
    case 1:
        printf("联络人信息列表：\n");
        break;
    case 2:
        printf("业务员信息列表：\n");
        break;
    }
    int attributeIndex = selectSearchAttribute(which);
    if (attributeIndex == -1) {
        printf("无效的属性选择。\n");
        return;
    }

    char ascending[MAX_LENGTH];
    printf("请输入排序方式（1升序/0降序）：");
    getInput(ascending, sizeof(ascending));
    if (!isOneChar(ascending)) {
        printf("无效的排序方式，请重新输入。\n");
        return;
    }
    
    sort(which, head, attributeIndex, charToInt(ascending[0]));
    printNodeList(head, which);
}

void combinedSort(head_node *head) {
    if (head == NULL || head->is_empty) {
        printf("没有可排序的数据。\n");
        return;
    }
    printf("开始进行组合排序。\n");
    int which = beforeInfo(head, "排序");
    if (which == -1) return;  // 如果选择无效或不允许展示，则返回

    switch (which) {
    case 0:
        printf("客户信息列表：\n");
        break;
    case 1:
        printf("联络人信息列表：\n");
        break;
    case 2:
        printf("业务员信息列表：\n");
        break;
    }
    combinedSortHelper(head, which);
    system(SYSTEM_CLEAR);
    printNodeList(head, which);
}

void combinedSortHelper(head_node *head, int which) {
    int attributeIndex = 0;
    while (true) {
        attributeIndex = selectSearchAttribute(which);
        if (attributeIndex == -1) {
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

    char get[MAX_LENGTH];
    printf("是否继续添加排序条件？(y): ");
    getInput(get, sizeof(get));
    if (isOneChar(get) && (get[0] == 'y' || get[0] == 'Y')) {
        system(SYSTEM_CLEAR);
        combinedSortHelper(head, which);  // 递归调用以继续排序
    }

    // 先进后排序
    sort(which, head, attributeIndex, charToInt(ascending[0]));
}








// end widgets/info_sort.c
