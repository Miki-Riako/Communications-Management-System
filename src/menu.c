// menu.c
#include "widgets/info_manage.c"
#include "widgets/customer_assign.c"
#include "widgets/group_manage.c"
#include "widgets/records_manage.c"
#include "widgets/info_enquiry.c"
#include "widgets/info_sort.c"
#include "widgets/info_statistics.c"
#include "widgets/records_analysis.c"
#include "widgets/system_setting.c"

void managerMenuWidget();
void employeeMenuWidget();
void exitSystem();

void managerMenuWidget() {
    while(true) {
        printf("\n\n通信管理系统\n\n");
        printf("您好，经理！\n");
        printf("1. 信息管理\n");
        printf("2. 客户分配\n");
        printf("3. 分组管理\n");
        printf("4. 信息查询\n");
        printf("5. 信息排序\n");
        printf("6. 信息统计\n");
        printf("7. 记录分析\n");
        printf("8. 系统维护\n");
        printf("9. 退出系统\n");
        printf("请选择一个操作（1-9）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);

        if (!isOneChar(get)) {
            printf("无效的选项，请重新选择。\n");
            continue;  // 继续循环等待有效输入
        }
        switch(get[0]) {
        case '1':
            infoManageWidget();
            break;
        case '2':
            customerAssignWidget();
            break;
        case '3':
            groupManageWidget();
            break;
        case '4':
            infoEnquiryWidget();
            break;
        case '5':
            infoSortWidget();
            break;
        case '6':
            infoStatisticsWidget();
            break;
        case '7':
            recordsAnalysisWidget();
            break;
        case '8':
            systemSettingWidget();
            break;
        case '9':
            exitSystem();
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
    }
}

void employeeMenuWidget() {
    while(true) {
        printf("\n\n通信管理系统\n\n");
        printf("您好，业务员%s！\n", User);
        printf("1. 信息查询\n");
        printf("2. 信息排序\n");
        printf("3. 信息统计\n");
        printf("4. 记录管理\n");
        printf("5. 记录分析\n");
        printf("6. 系统维护\n");
        printf("7. 退出系统\n");
        printf("请选择一个操作（1-7）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);

        if (!isOneChar(get)) {
            printf("无效的选项，请重新选择。\n");
            continue;  // 继续循环等待有效输入
        }
        switch(get[0]) {
        case '1':
            infoEnquiryWidget();
            break;
        case '2':
            infoSortWidget();
            break;
        case '3':
            infoStatisticsWidget();
            break;
        case '4':
            recordsManageWidget();
            break;
        case '5':
            recordsAnalysisWidget();
            break;
        case '6':
            systemSettingWidget();
            break;
        case '7':
            exitSystem();
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
    }
}

void exitSystem() {
    printf("感谢使用，再见！\n");
    exit(0);
}

// end menu.c