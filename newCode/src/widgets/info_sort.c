// widgets/info_sort.c
#include "../header.h"

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
        printf("1. 默认排序\n");
        printf("2. 单一属性排序\n");
        printf("3. 多属性排序\n");
        printf("4. 通信记录排序\n");
        printf("5. 返回\n");
        printf("请输入您的选择（1-5）：");

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
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
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
    int which = beforeInfo(head, "展示");
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
    printNodeList(head, which);
}
    // case 3:
    //     printf("通信记录列表：\n");
    //     printf("管理用户 - 公司名称 - 联络人 - 日期 - 时间 - 时长 - 通信内容\n");
    //     break;

// end widgets/info_sort.c