#include "login.c"

void addCustomer();
void viewCustomers();
void addCommunicationRecord();
void viewCommunicationRecords();
void exitSystem();

int main(void) {
    int choice;
    login();
    while(1) {
        printf("\n\n通信管理系统\n\n");
        printf("1. 添加客户信息\n");
        printf("2. 查看客户信息\n");
        printf("3. 添加通信记录\n");
        printf("4. 查看通信记录\n");
        printf("5. 退出系统\n");
        printf("请选择一个操作（1-5）：");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                viewCustomers();
                break;
            case 3:
                addCommunicationRecord();
                break;
            case 4:
                viewCommunicationRecords();
                break;
            case 5:
                exitSystem();
                return 0;
            default:
                printf("无效的选择，请重新输入。\n");
        }
    }
    return 0;
}

void addCustomer() {
    printf("功能尚未实现。\n");
}

void viewCustomers() {
    printf("功能尚未实现。\n");
}

void addCommunicationRecord() {
    printf("功能尚未实现。\n");
}

void viewCommunicationRecords() {
    printf("功能尚未实现。\n");
}

void exitSystem() {
    printf("感谢使用，再见！\n");
}
