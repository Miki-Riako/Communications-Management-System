// widgets/group_manage.c
#include "../header.h"

void createDirectory(const char *path);
void createGroup(const char *groupName);
void regionGroup(const char *groupName);
void scaleGroup(const char *groupName);
void contactGroup(const char *groupName);
void addGroup();
void changeGroup();
void removeGroup();
void showGroups();

void groupManageWidget() {
    createDirectory("groups");
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

void createDirectory(const char *path) {
    CREATE_DIRECTORY(path);
}

void createGroup(const char *groupName) {
    char filename[MAX_LENGTH + 12];
    snprintf(filename, sizeof(filename), "groups/%s.csv", groupName);
    initializeInfoFile(filename, "Name|||Region|||Address|||LegalRepresentative|||Scale|||BusinessContactLevel|||Email|||Phone");
    printf("自定义分组 '%s' 已创建。\n", groupName);
}

void addGroup() {
    char groupName[MAX_LENGTH];

    printf("请输入新分组的名称：");
    getInput(groupName, sizeof(groupName));

    printf("选择分组类型：\n");
    printf("1. 按区域分组\n");
    printf("2. 按规模分组\n");
    printf("3. 按联系程度分组\n");
    printf("4. 自定义分组\n");
    printf("其他键退出");
    printf("请输入选择（1-4）：");

    char get[MAX_LENGTH];
    getInput(get, sizeof(get));
    system(SYSTEM_CLEAR);

    if (!isOneChar(get)) {
        return;
    }
    switch (get[0]) {
    case '1':
        regionGroup(groupName);
        break;
    case '2':
        scaleGroup(groupName);
        break;
    case '3':
        contactGroup(groupName);
        break;
    case '4':
        createGroup(groupName);
        break;
    default:
        return;
    }
}

void regionGroup(const char *groupName) {
    char inputRegion[MAX_LENGTH];
    printf("请输入区域名：");
    getInput(inputRegion, sizeof(inputRegion));

    char filename[MAX_LENGTH];
    snprintf(filename, sizeof(filename), "groups/%s.csv", groupName);
    createGroup(groupName);  // 创建空分组文件并初始化

    copyLine("customers.csv", filename, "Region", inputRegion);  // 复制符合条件的行
}

void scaleGroup(const char *groupName) {
    char filename[MAX_LENGTH];
    snprintf(filename, sizeof(filename), "groups/%s.csv", groupName);
    createGroup(groupName);
    const char *scaleValue;

    printf("请选择客户的规模：\n");
    printf("1. 大\n");
    printf("2. 中\n");
    printf("3. 小\n");
    printf("请输入选择（1-3）：");

    char get[MAX_LENGTH];
    getInput(get, sizeof(get));
    system(SYSTEM_CLEAR);

    switch (get[0]) {
    case '1':
        scaleValue = "大";
        break;
    case '2':
        scaleValue = "中";
        break;
    case '3':
        scaleValue = "小";
        break;
    default:
        printf("无效的选择\n");
        return;
    }

    copyLine("customers.csv", filename, "Scale", scaleValue);
    printf("已将规模为 '%s' 的客户添加到分组 '%s'.\n", scaleValue, groupName);
}

void contactGroup(const char *groupName) {
    char filename[MAX_LENGTH];
    snprintf(filename, sizeof(filename), "groups/%s.csv", groupName);
    createGroup(groupName);  // 创建空分组文件并初始化

    printf("请选择客户的业务联系程度：\n");
    printf("1. 高\n");
    printf("2. 中\n");
    printf("3. 低\n");
    printf("请输入选择（1-3）：");

    char get[MAX_LENGTH];
    getInput(get, sizeof(get));
    system(SYSTEM_CLEAR);

    const char *contactLevel;
    switch (get[0]) {
    case '1':
        contactLevel = "高";
        break;
    case '2':
        contactLevel = "中";
        break;
    case '3':
        contactLevel = "低";
        break;
    default:
        printf("无效的选择，请重新输入。\n");
        return;
    }

    copyLine("customers.csv", filename, "BusinessContactLevel", contactLevel);
    printf("已将联系程度为 '%s' 的客户添加到分组 '%s'.\n", contactLevel, groupName);
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