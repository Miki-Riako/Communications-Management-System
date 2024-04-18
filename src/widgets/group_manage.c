// widgets/group_manage.c
#include "../header.h"

void addGroup();
void changeGroup();
void removeGroup();
void showGroups();

void groupManageWidget() {
    while (true) {
        printf("\n分组管理\n");
        printf("1. 创建分组\n");
        printf("2. 修改分组\n");
        printf("3. 删除分组\n");
        printf("4. 查看所有分组\n");
        printf("5. 返回\n");
        printf("请选择一个操作（1-5）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);

        if (!isOneChar(get)) {
            printf("无效的选择，请重新输入。\n");
            continue;
        }
        switch (get[0]) {
        case '1':
            addGroup();
            break;
        case '2':
            changeGroup();
            break;
        case '3':
            removeGroup();
            break;
        case '4':
            showGroups();
            break;
        case '5':
            return;
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
    }
}

void addGroup() {
    printf("创建新的分组...\n");
    // 实现创建分组的逻辑
}

void changeGroup() {
    printf("修改现有分组...\n");
    // 实现修改分组的逻辑
}

void removeGroup() {
    printf("删除分组...\n");
    // 实现删除分组的逻辑
}

void showGroups() {
    printf("查看所有分组...\n");
    // 实现查看所有分组的逻辑
}

// end widgets/group_manage.c