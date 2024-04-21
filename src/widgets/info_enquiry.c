// widgets/info_enquiry.c
#include "../header.h"

void infoEnquiryWidget();
int selectSearchAttribute(int which);
bool searchOnes(head_node *head, char *query, int attrIndex, int which);
void simpleQuery(head_node *head);
void combinedQuery(head_node *head);
void fuzzyQuery(head_node *head);

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
    case 0: // 客户
        printf("1. 名称\n2. 地区\n3. 地址\n4. 法人\n5. 规模\n6. 联系等级\n7. 邮箱\n8. 电话\n");
        index = '8';
        break;
    case 1: // 联络人
    case 2: // 业务员
        printf("1. 名称\n2. 性别\n3. 生日\n4. 邮箱\n5. 电话\n6. 代表公司\n");
        break;
    }
    char get[MAX_LENGTH];
    infoInput(get, sizeof(get), "请选择属性以进行搜索：\n");
    if (!isOneChar(get) || get[0] < '1' || get[0] > index) {
        printf("无效的选择\n");
        return -1;
    } else {
        return get[0] - '0' - 1;
    }
}

bool searchOnes(head_node *head, char *query, int attrIndex, int which) {
    bool found = false;
    switch (which) {
    case 0: // 客户
        node_cus *cusNode = head->next_cus;
        while (cusNode) {
            char *toCompare = NULL;
            switch (attrIndex) {
            case 0:
                toCompare = cusNode->customer.name;
                break;
            case 1:
                toCompare = cusNode->customer.region;
                break;
            case 2:
                toCompare = cusNode->customer.address;
                break;
            case 3:
                toCompare = cusNode->customer.legalRepresentative;
                break;
            case 4:
                toCompare = cusNode->customer.scale;
                break;
            case 5:
                toCompare = cusNode->customer.businessContactLevel;
                break;
            case 6:
                toCompare = cusNode->customer.email;
                break;
            case 7:
                toCompare = cusNode->customer.phone;
                break;
            default:
                printf("无效的属性选择。\n");
                return false;
            }
            if (toCompare && isSameString(toCompare, query)) {
                printNode_cus(cusNode);
                found = true;
            }
            cusNode = cusNode->next;
        }
        return found;
    case 1: // 联络人
        node_ctp *ctpNode = head->next_ctp;
        while (ctpNode) {
            char *toCompare = NULL;
            switch (attrIndex) {
            case 0:
                toCompare = ctpNode->contactPerson.name;
                break;
            case 1:
                toCompare = ctpNode->contactPerson.gender;
                break;
            case 2:
                toCompare = ctpNode->contactPerson.birthday;
                break;
            case 3:
                toCompare = ctpNode->contactPerson.email;
                break;
            case 4:
                toCompare = ctpNode->contactPerson.phone;
                break;
            case 5:
                toCompare = ctpNode->contactPerson.representative;
                break;
            default:
                printf("无效的属性选择。\n");
                return false;
            }
            if (toCompare && isSameString(toCompare, query)) {
                printNode_ctp(ctpNode);
                found = true;
            }
            ctpNode = ctpNode->next;
        }
        return found;
    case 2: // 业务员
        node_emp *empNode = head->next_emp;
        while (empNode) {
            char *toCompare = NULL;
            switch (attrIndex) {
            case 0:
                toCompare = empNode->employee.name;
                break;
            case 1:
                toCompare = empNode->employee.gender;
                break;
            case 2:
                toCompare = empNode->employee.birthday;
                break;
            case 3:
                toCompare = empNode->employee.email;
                break;
            case 4:
                toCompare = empNode->employee.phone;
                break;
            case 5:
                toCompare = empNode->employee.representative;
                break;
            default:
                printf("无效的属性选择。\n");
                return false;
            }
            if (toCompare && isSameString(toCompare, query)) {
                printNode_emp(empNode);
                found = true;
            }
            empNode = empNode->next;
        }
        return found;
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

    // 根据用户选择决定查询内容和显示格式
    printHeading(which);
    found = searchOnes(head, queryValue, attributeIndex, which);
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