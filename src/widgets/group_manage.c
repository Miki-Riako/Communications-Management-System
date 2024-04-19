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
void divideCustomer();
void adjustCustomer();

void groupManageWidget() {
    createDirectory("groups");
    while (true) {
        printf("\n分组管理\n");
        printf("1. 创建分组\n");
        printf("2. 修改分组\n");
        printf("3. 删除分组\n");
        printf("4. 查看所有分组\n");
        printf("5. 客户划分\n");
        printf("6. 客户调整\n");
        printf("7. 返回\n");
        printf("请选择一个操作（1-7）：");

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
            divideCustomer();
            break;
        case '6':
            adjustCustomer();
            break;
        case '7':
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
    char oldGroupName[MAX_LENGTH];
    char newGroupName[MAX_LENGTH];
    char oldFilename[MAX_LENGTH + 12];
    char newFilename[MAX_LENGTH + 12];

    printf("请输入要修改的分组名称：");
    getInput(oldGroupName, sizeof(oldGroupName));
    snprintf(oldFilename, sizeof(oldFilename), "groups/%s.csv", oldGroupName); // 构建原始文件名

    // 检查原始文件是否存在
    if (ACCESS(oldFilename, F_OK) != -1) {
        printf("请输入新的分组名称：");
        getInput(newGroupName, sizeof(newGroupName));
        snprintf(newFilename, sizeof(newFilename), "groups/%s.csv", newGroupName); // 构建新文件名

        // 重命名文件
        if (rename(oldFilename, newFilename) == 0) {
            printf("分组 '%s' 已成功重命名为 '%s'.\n", oldGroupName, newGroupName);
        } else {
            perror("重命名文件失败"); // 处理错误
        }
    } else {
        printf("分组 '%s' 不存在。\n", oldGroupName);  // 原始文件不存在
    }
}

void removeGroup() {
    char groupName[MAX_LENGTH];
    char filename[MAX_LENGTH + 12];

    printf("请输入要删除的分组名称：");
    getInput(groupName, sizeof(groupName));
    snprintf(filename, sizeof(filename), "groups/%s.csv", groupName); // 构建完整的文件路径

    // 检查文件是否存在
    if (ACCESS(filename, F_OK) != -1) {
        // 文件存在，尝试删除
        if (remove(filename) == 0) {
            printf("分组 '%s' 已成功删除。\n", groupName);
        } else {
            perror("删除文件失败");  // 删除失败，打印错误信息
        }
    } else {
        printf("分组 '%s' 不存在。\n", groupName);  // 文件不存在
    }
}

void showGroups() {
    printf("查看所有分组...\n");
    // 实现查看所有分组的逻辑
}

void divideCustomer() {
    char customerName[MAX_LENGTH];
    char groupName[MAX_LENGTH];
    char groupFilename[MAX_LENGTH + 12];

    infoInput(customerName, sizeof(customerName), "请输入客户名以进行分组：");
    infoInput(groupName, sizeof(groupName), "请输入目标分组名称：");
    snprintf(groupFilename, sizeof(groupFilename), "groups/%s.csv", groupName);

    if (ACCESS(groupFilename, F_OK) == -1) {
        printf("分组 '%s' 不存在。\n", groupName);
        return;
    }

    // 复制符合条件的行到分组文件
    copyLine("customers.csv", groupFilename, "Name", customerName);
    printf("已将名为 '%s' 的客户添加到分组 '%s'.\n", customerName, groupName);
}

void adjustCustomer() {
    char oldGroupName[MAX_LENGTH], newGroupName[MAX_LENGTH];
    char customerName[MAX_LENGTH];
    char oldGroupFilename[MAX_LENGTH + 12], newGroupFilename[MAX_LENGTH + 12];

    infoInput(oldGroupName, sizeof(oldGroupName), "请输入原分组名称：");
    snprintf(oldGroupFilename, sizeof(oldGroupFilename), "groups/%s.csv", oldGroupName);
    infoInput(customerName, sizeof(customerName), "请输入客户名称：");
    if (!alreadyExists(oldGroupFilename, customerName)) {
        printf("客户 '%s' 不存在于原分组 '%s' 中。\n", customerName, oldGroupName);
        return;
    }

    if (ACCESS(oldGroupFilename, F_OK) == -1) {
        printf("分组 '%s' 不存在该文件夹中。\n", oldGroupName);
        return;
    }

    printf("请选择操作：\n1. 复制客户\n2. 移动客户\n3. 删除客户\n请输入选择（1-3）：");
    char action[MAX_LENGTH];
    getInput(action, sizeof(action));
    system(SYSTEM_CLEAR);

    if (!isOneChar(action)) {
        printf("无效的操作选择。\n");
        return;
    }
    switch (action[0]) {
    case '1':  // 复制客户
    case '2':  // 移动客户
        infoInput(newGroupName, sizeof(newGroupName), "请输入目标分组名称：");
        snprintf(newGroupFilename, sizeof(newGroupFilename), "groups/%s.csv", newGroupName);
        if (ACCESS(newGroupFilename, F_OK) == -1) {
            printf("目标分组 '%s' 不存在。\n", newGroupName);
            return;
        }
        copyLine(oldGroupFilename, newGroupFilename, "Name", customerName);
        if (action[0] == '2') {  // 如果是移动，还需要从原分组中删除
            if (removeEntry(oldGroupFilename, customerName)) {
                printf("客户 '%s' 移动成功。\n", customerName);
            } else {
                printf("移动客户 '%s' 失败。\n", customerName);
            }
        }
        break;
    case '3':  // 删除客户
        if (removeEntry(oldGroupFilename, customerName)) {
            printf("客户 '%s' 删除成功。\n", customerName);
        } else {
            printf("删除客户 '%s' 失败。\n", customerName);
        }
        break;
    default:
        printf("无效的操作选择。\n");
        return;
    }
    printf("操作成功完成。\n");
}

// end widgets/group_manage.c