// main.c
#include "login.c"
#include "changecustomer.c"
#include "changecommunicationrecord.c"

#include "setsystem.c"

void exitSystem();

int main(void) {
    system(SYSTEM_CLEAR);
    login();
    while(true) {
        bool flag = false;
        printf("\n\n通信管理系统\n\n");
        printf("1. 修改客户信息\n");
        printf("2. 修改通信记录\n");
        printf("3. 查询信息\n");
        printf("4. 统计信息\n");
        printf("5. 设置\n");
        printf("6. 退出系统\n");
        printf("请选择一个操作（1-6）：");
        string choice;
        scanf("%254s", choice);
        system(SYSTEM_CLEAR);
        if (strlen(choice) != 1) {
            printf("无效的选项，请重新选择。\n");
            continue;  // 继续循环等待有效输入
        }
        switch(choice[0]) {
        case '1':
            changeCustomer();
            break;
        case '2':
            changeCommunicationRecord();
            break;
        case '3':
            // queryInformation();
            break;
        case '4':
            // statisticsInformation();
            break;
        case '5':
            if (IsManager) {
                setSystem();
            } else {
                printf("无法权限进行设置操作。\n");
            }
            break;
        case '6':
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
