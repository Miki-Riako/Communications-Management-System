// main.c
#include "login.c"
#include "addcustomer.c"
#include "viewcustomers.c"
#include "addcommunicationrecord.c"
#include "viewcommunicationrecords.c"

void exitSystem();

int main(void) {
    system(SYSTEM_CLEAR);
    login();
    while(true) {
        bool flag = false;
        printf("\n\n通信管理系统\n\n");
        printf("1. 添加客户信息\n");
        printf("2. 查看客户信息\n");
        printf("3. 添加通信记录\n");
        printf("4. 查看通信记录\n");
        printf("5. 查询信息\n");
        printf("6. 统计信息\n");
        printf("7. 设置\n");
        printf("8. 退出系统\n");
        printf("请选择一个操作（1-8）：");
        string choice;
        scanf("%254s", choice);
        system(SYSTEM_CLEAR);
        if (strlen(choice) != 1) {
            printf("无效的选项，请重新选择。\n");
            continue;  // 继续循环等待有效输入
        }
        switch(choice[0]) {
        case '1':
            addCustomer();
            break;
        case '2':
            viewCustomers();
            break;
        case '3':
            addCommunicationRecord();
            break;
        case '4':
            viewCommunicationRecords();
            break;
        case '5':
            // queryInformation();
            break;
        case '6':
            // statisticsInformation();
            break;
        case '7':
            // setSystem();
            break;
        case '8':
            exitSystem();
            return 0;
        default:
            printf("无效的选择，请重新输入。\n");
            system("pause");
            flag = true;
            break;
        }
        if (flag) {
            continue;
        }
    }
    return 0;
}

void exitSystem() {
    printf("感谢使用，再见！\n");
}
