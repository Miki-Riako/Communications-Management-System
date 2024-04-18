// widgets/customer_assign.c
#include "../header.h"

void customerAssignWidget();
void addAssignment();
void changeAssignment();
void removeAssignment();
void displayAssignment();

// Main widget for customer assignment management
void customerAssignWidget() {
    initializeInfoFile("assignments.csv", "Employee|||Customer");
    while (true) {
        printf("\n客户分配管理\n");
        printf("1. 分配客户\n");
        printf("2. 修改客户分配\n");
        printf("3. 删除客户分配\n");
        printf("4. 查看分配的客户\n");
        printf("5. 返回\n");
        printf("请选择操作（1-5）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);

        if (!isOneChar(get)) {
            printf("无效的选择，请重新输入。\n");
            continue;
        }
        switch (get[0]) {
        case '1':
            addAssignment();
            break;
        case '2':
            changeAssignment();
            break;
        case '3':
            removeAssignment();
            break;
        case '4':
            displayAssignment();
            break;
        case '5':
            return;
        default:
            printf("无效的选项，请重新输入。\n");
            break;
        }
    }
}

void addAssignment() {
    char employeeName[MAX_LENGTH], customerName[MAX_LENGTH];
    char fullLine[MAX_LENGTH * 2 + 4];

    inputTheName(employeeName, sizeof(employeeName), "请输入业务员的名称：");
    inputTheName(customerName, sizeof(customerName), "请输入客户的名称：");

    strcpy(fullLine, employeeName);
    addColumn(fullLine, customerName);

    // 检查是否已经存在这个分配
    if (lineExists("assignments.csv", fullLine)) {
        printf("这个分配已经存在：%s -> %s\n", employeeName, customerName);
    } else {
        writeLineToFile("assignments.csv", fullLine);
        printf("客户分配成功：%s -> %s\n", employeeName, customerName);
    }
}

void changeAssignment() {
    char oldEmployeeName[MAX_LENGTH], oldCustomerName[MAX_LENGTH];
    char newEmployeeName[MAX_LENGTH], newCustomerName[MAX_LENGTH];
    char oldLine[MAX_LENGTH * 2 + 4];
    char newLine[MAX_LENGTH * 2 + 4];

    // 获取原始业务员和客户的名称
    inputTheName(oldEmployeeName, sizeof(oldEmployeeName), "请输入原始业务员的名称：");
    inputTheName(oldCustomerName, sizeof(oldCustomerName), "请输入原始客户的名称：");

    strcpy(oldLine, oldEmployeeName);
    addColumn(oldLine, oldCustomerName);

    // 检查原始组合是否存在
    if (!lineExists("assignments.csv", oldLine)) {
        printf("分配不存在：%s -> %s\n", oldEmployeeName, oldCustomerName);
        return;
    }

    // 获取新业务员和客户的名称
    inputTheName(newEmployeeName, sizeof(newEmployeeName), "请输入新的业务员的名称：");
    inputTheName(newCustomerName, sizeof(newCustomerName), "请输入新的客户的名称：");

    strcpy(newLine, newEmployeeName);
    addColumn(newLine, newCustomerName);

    // 删除原始组合
    if (removeLineInFile("assignments.csv", oldLine)) {
        // 添加新组合
        writeLineToFile("assignments.csv", newLine);
        printf("成功更新分配：%s -> %s\n", newEmployeeName, newCustomerName);
    } else {
        printf("更新分配失败。\n");
    }
}

void removeAssignment() {
    char employeeName[MAX_LENGTH], customerName[MAX_LENGTH];
    char fullLine[MAX_LENGTH * 2 + 4];

    inputTheName(employeeName, sizeof(employeeName), "请输入业务员的名称：");
    inputTheName(customerName, sizeof(customerName), "请输入客户的名称：");

    strcpy(fullLine, employeeName);
    addColumn(fullLine, customerName);

    if (!lineExists("assignments.csv", fullLine)) {
        printf("未找到该分配：%s -> %s\n", employeeName, customerName);
    } else {
        // 删除分配
        if (removeLineInFile("assignments.csv", fullLine)) {
            printf("客户分配删除成功：%s -> %s\n", employeeName, customerName);
        } else {
            printf("客户分配删除失败。\n");
        }
    }
}

void displayAssignment() {
    FILE *file = fopen("assignments.csv", "r");
    if (!file) {
        perror("打开文件失败");
        return;
    }
    char line[MAX_LENGTH];
    printf("当前的业务员和客户配对如下：\n");
    while (fgets(line, sizeof(line), file)) {
        char *delimiter = strstr(line, "|||");
        if (delimiter != NULL) {
            *delimiter = '\0';  // 将分隔符替换为字符串终结符，从而分割字符串
            printf("%s -> %s", line, delimiter + 3); // 输出前后部分
        } else {
            printf("格式错误： %s\n", line);
        }
    }
    fclose(file);
}

// end widgets/customer_assign.c