// widgets/info_sort.c
#include "../header.h"

void infoSortWidget();
void defaultSort(head_node *head);

void infoSortWidget() {
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
    case 0: {
        node_cus *cus = head->next_cus;
        printf("客户信息列表：\n");
        printf("名称 - 地区 - 地址 - 法人 - 规模 - 联系程度 - 邮箱 - 电话\n");
        while (cus != NULL) {
            printf("%s - %s - %s - %s - %s - %s - %s - %s\n",
                cus->customer.name,
                cus->customer.region,
                cus->customer.address,
                cus->customer.legalRepresentative,
                cus->customer.scale,
                cus->customer.businessContactLevel,
                cus->customer.email,
                cus->customer.phone
            );
            cus = cus->next;
        }
        break;
    } case 1: {
        node_ctp *ctp = head->next_ctp;
        printf("联络人信息列表：\n");
        printf("名称 - 性别 - 生日 - 邮箱 - 电话 - 代表公司\n");
        while (ctp != NULL) {
            printf("%s - %s - %s - %s - %s - %s\n",
                ctp->contactPerson.name,
                ctp->contactPerson.gender,
                ctp->contactPerson.birthday,
                ctp->contactPerson.email,
                ctp->contactPerson.phone,
                ctp->contactPerson.representative
            );
            ctp = ctp->next;
        }
        break;
    } case 2: {
        node_emp *emp = head->next_emp;
        printf("业务员信息列表：\n");
        printf("名称 - 性别 - 生日 - 邮箱 - 电话 - 代表公司\n");
        while (emp != NULL) {
            printf("%s - %s - %s - %s - %s - %s\n",
                emp->employee.name,
                emp->employee.gender,
                emp->employee.birthday,
                emp->employee.email,
                emp->employee.phone,
                emp->employee.representative
            );
            emp = emp->next;
        }
        break;
    }}
}
    // } case 3: {
    //     node_rec *rec = head->next_rec;
    //     printf("通信记录列表：\n");
    //     printf("管理用户 - 公司名称 - 联络人 - 日期 - 时间 - 时长 - 通信内容\n");
    //     while (rec != NULL) {
    //         printf("%s - %s - %s - %s - %s - %s - %s\n",
    //             rec->record.user,
    //             rec->record.companyName,
    //             rec->record.contactName,
    //             rec->record.date,
    //             rec->record.time,
    //             rec->record.duration,
    //             rec->record.content
    //         );
    //         rec = rec->next;
    //     }
    //     break;

// end widgets/info_sort.c
