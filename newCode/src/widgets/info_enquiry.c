// widgets/info_enquiry.c
#include "../header.h"

void infoEnquiryWidget() {
    initializeAll();
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
        printf("\n信息查询系统\n");
        printf("1. 简单查询\n");
        printf("2. 组合查询\n");
        printf("3. 模糊查询\n");
        printf("4. 返回\n");
        printf("请选择一个操作：（1-4）");
        
        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);
        
        if (!isOneChar(get)) {
            printf("无效的选择，请重新输入。\n");
            continue;
        }
        switch (get[0]) {
        case '1':
            simpleQuery(head);
            break;
        case '2':
            combinedQuery(head);
            break;
        case '3':
            fuzzyQuery(head);
            break;
        case '4':
            printf("正在返回，请稍等。\n");
            freeAll(head);
            printf("返回成功。\n");
            return;
        default:
            printf("无效的选择，请重新输入。\n");
            break;
        }
    }
}

int selectSearchAttribute(int which) {
    char index = '6';
    switch (which) {
    case '0': // 客户
        printf("1. 名称\n2. 地区\n3. 地址\n4. 法人\n5. 规模\n6. 联系等级\n7. 邮箱\n8. 电话\n");
        index = 8;
        break;
    case '1': // 联络人
    case '2': // 业务员
        printf("1. 名称\n2. 性别\n3. 生日\n4. 邮箱\n5. 电话\n6. 代表公司\n");
        break;
    }
    char get[MAX_LENGTH];
    infoInput(get, sizeof(get), "请选择属性以进行搜索：\n");
    if (!isOneChar(get) || get[0] < '1' || get[0] > index) {
        printf("无效的选择，请重新输入。\n");
        return -1;
    } else {
        return get[0] - '0' - 1;
    }
}

void simpleQuery(head_node *head) {
    int which = beforeInfo(head, "查询");
    if (which == -1) return;  // 无效的查询类型或无数据类型被选中

    char queryValue[MAX_LENGTH];
    bool found = false;
    int attributeIndex = selectSearchAttribute(which);

    if (attributeIndex == -1) {
        printf("无效的属性选择。\n");
        return;
    }

    // 获取用户想要搜索的值
    infoInput(queryValue, sizeof(queryValue), "请输入搜索值：");

    printf("搜索中，请您耐心等待。\n");
    head_node *newHead = (head_node *)malloc(sizeof(head_node));  // 分配内存
    if (!newHead) {
        fprintf(stderr, "内存分配失败！\n");
        return;
    }
    loadFile(head);  // 加载数据
    if (newHead->is_empty) printf("没有加载到任何数据。\n");

    // 根据用户选择决定查询内容和显示格式
    switch (which) {
    case 0: { // 查询客户
        // searchCustomers(newHead->next_cus, queryValue, attributeIndex);
        // infoInput(queryName, sizeof(queryName), "请输入要查询的客户名称：");
        // node_cus *cusNode = head->next_cus;
        // printf("客户名 - 地区 - 地址 - 法人 - 规模 - 联系等级 - 邮箱 - 电话\n");
        // while (cusNode != NULL) {
        //     if (isSameString(cusNode->customer.name, queryName)) {
        //         printNode_cus(cusNode);
        //         found = true;
        //     }
        //     cusNode = cusNode->next;
        // }
        // break;
    } case 1: { // 查询联络人
        // infoInput(queryName, sizeof(queryName), "请输入要查询的联络人名称：");
        // node_ctp *ctpNode = head->next_ctp;
        // printf("联络人名称 - 性别 - 生日 - 邮箱 - 电话 - 代表公司\n");
        // while (ctpNode != NULL) {
        //     if (isSameString(ctpNode->contactPerson.name, queryName)) {
        //         printNode_ctp(ctpNode);
        //         found = true;
        //     }
        //     ctpNode = ctpNode->next;
        // }
        // break;
    } case 2: { // 查询业务员
        // infoInput(queryName, sizeof(queryName), "请输入要查询的业务员名称：");
        // node_emp *empNode = head->next_emp;
        // printf("业务员名称 - 性别 - 生日 - 邮箱 - 电话 - 代表公司\n");
        // while (empNode != NULL) {
        //     if (isSameString(empNode->employee.name, queryName)) {
        //         printNode_emp(empNode);
        //         found = true;
        //     }
        //     empNode = empNode->next;
        // }
        // break;
    }}
    if (!found) {
        printf("没有找到匹配的信息。\n");
    }
}
    // } case 3: { // 查询记录
    //     infoInput(queryName, sizeof(queryName), "请输入要查询的公司名称：");
    //     node_rec *recNode = head->next_rec;
    //     printf("管理用户 - 公司名称 - 联络人 - 日期 - 时间 - 时长 - 通信内容\n");
    //     while (recNode != NULL) {
    //         if (isSameString(recNode->record.companyName, queryName)) {
    //             printNode_rec(recNode);
    //             found = true;
    //         }
    //         recNode = recNode->next;
    //     }
    //     break;
    // }

void combinedQuery(head_node *head) {
    int which = beforeInfo(head, "查询");
    if (which == -1) return;
}

void fuzzyQuery(head_node *head) {
    int which = beforeInfo(head, "查询");
    if (which == -1) return;
}


// end widgets/info_enquiry.c