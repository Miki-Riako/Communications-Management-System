// widgets/customer_assign.c
#include "../header.h"

void customerAssignWidget();
void addAssignment();
void modifyAssignment();
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
            
            break;
        case '3':
            
            break;
        case '4':
            
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

// Modifies an existing customer assignment
void changeAssignment() {
    printf("实现修改客户分配的逻辑。\n");
    // Implement the logic to modify an existing customer assignment
}

// Deletes an existing customer assignment
void removeAssignment() {
    printf("实现删除客户分配的逻辑。\n");
    // Implement the logic to delete an existing customer assignment
}

// Displays customers assigned to an employee
void displayAssignment() {
    printf("显示分配给业务员的客户。\n");
    // Implement the logic to display customers assigned to an employee
}



// end widgets/customer_assign.c