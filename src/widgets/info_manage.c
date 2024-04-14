// widgets/info_manage.c
#include "../header.h"

void infoManageWidget();
void initializeInfoFile(const char *path, const char *header);
void addEmployeeWidget();
void addCustomerWidget();
void addContactWidget();

void infoManageWidget() {
    initializeInfoFile("employees.csv", "Name|||Gender|||Birthday|||Email|||Phone|||Representative");
    initializeInfoFile("customers.csv", "Name|||Region|||Address|||LegalRepresentative|||Scale|||BusinessContactLevel|||Email|||Phone");
    initializeInfoFile("contacts.csv", "Name|||Gender|||Birthday|||Email|||Phone|||Representative");
    while(true) {
        printf("您好，经理！\n");
        printf("1. 增加业务员信息\n");
        printf("2. 修改业务员信息\n");
        printf("3. 删除业务员信息\n");
        printf("4. 增加客户信息\n");
        printf("5. 修改客户信息\n");
        printf("6. 删除客户信息\n");
        printf("7. 增加客户联络员信息\n");
        printf("8. 修改客户联络员信息\n");
        printf("9. 删除客户联络员信息\n");
        printf("0. 退出系统\n");
        printf("请选择一个操作（0-9）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);

        if (!isOneChar(get)) {
            printf("无效的选项，请重新选择。\n");
            continue;  // 继续循环等待有效输入
        }
        switch (get[0]) {
            case '1':
                addEmployeeWidget();
                break;
            case '2':

                break;
            case '3':

                break;
            case '4':
                addCustomerWidget();
                break;
            case '5':

                break;
            case '6':

                break;
            case '7':
                addContactWidget();
                break;
            case '8':

                break;
            case '9':

                break;
            case '0':
                return;  // 返回主菜单
            default:
                printf("无效的选项，请重新输入。\n");
        }
    }
}

void initializeInfoFile(const char *path, const char *header) {
    FILE *file = fopen(path, "r");
    if (!file) {
        file = fopen(path, "w");
        if (file) {
            fprintf(file, "%s\n", header);
            fclose(file);
        } else {
            fprintf(stderr, "Error creating file %s\n", path);
        }
    } else {
        fclose(file);
    }
}

void addEmployeeWidget() {
    Employee newEmployee;

    infoInput(newEmployee.name, sizeof(newEmployee.name), "输入业务员姓名: ");
    infoInput(newEmployee.gender, sizeof(newEmployee.gender), "输入业务员性别: ");
    infoInput(newEmployee.birthday, sizeof(newEmployee.birthday), "输入业务员生日: ");
    while (true) {
        infoInput(newEmployee.email, sizeof(newEmployee.email), "输入业务员电子邮件: ");
        if (isSameString(newEmployee.email, " ") || matchMail(newEmployee.email)) {
            break;
        } else {
            printf("电子邮件格式不正确，请重新输入。\n");
        }
    }

    while (true) {
        infoInput(newEmployee.phone, sizeof(newEmployee.phone), "输入业务员电话: ");
        if (isSameString(newEmployee.email, " ") || matchPhone(newEmployee.phone)) {
            break;
        } else {
            printf("电话号码格式不正确，请重新输入。\n");
        }
    }

    infoInput(newEmployee.representative, sizeof(newEmployee.representative), "输入业务员代表的公司: ");

    system(SYSTEM_CLEAR); // 清屏
    // saveEmployeeToFile(newEmployee);
    // displayEmployee(newEmployee);
    printf("业务员信息已添加.\n");
}

void addCustomerWidget() {
    Customer newCustomer;

    infoInput(newCustomer.name, sizeof(newCustomer.name), "输入客户姓名: ");
    infoInput(newCustomer.region, sizeof(newCustomer.region), "输入客户所在区域: ");
    infoInput(newCustomer.address, sizeof(newCustomer.address), "输入客户地址: ");
    infoInput(newCustomer.legalRepresentative, sizeof(newCustomer.legalRepresentative), "输入客户公司法人: ");
    infoInput(newCustomer.scale, sizeof(newCustomer.scale), "输入客户规模（大、中、小）: ");
    infoInput(newCustomer.businessContactLevel, sizeof(newCustomer.businessContactLevel), "输入与本公司业务联系程度（高、中、低）: ");
    while (true) {
        infoInput(newCustomer.email, sizeof(newCustomer.email), "输入客户电子邮件: ");
        if (isSameString(newCustomer.email, " ") || matchMail(newCustomer.email)) {
            break;
        } else {
            printf("电子邮件格式不正确，请重新输入。\n");
        }
    }

    while (true) {
        infoInput(newCustomer.phone, sizeof(newCustomer.phone), "输入客户电话: ");
        if (isSameString(newCustomer.email, " ") || matchPhone(newCustomer.phone)) {
            break;
        } else {
            printf("电话号码格式不正确，请重新输入。\n");
        }
    }

    system(SYSTEM_CLEAR);
    // saveCustomerToFile(newCustomer);
    // displayCustomer(newCustomer);
    printf("客户信息已添加.\n");
}

void addContactWidget() {
    ContactPerson newContact;

    infoInput(newContact.name, sizeof(newContact.name), "输入联络员姓名: ");
    infoInput(newContact.gender, sizeof(newContact.gender), "输入联络员性别: ");
    infoInput(newContact.birthday, sizeof(newContact.birthday), "输入联络员生日: ");

    while (true) {
        infoInput(newContact.email, sizeof(newContact.email), "输入联络员电子邮件: ");
        if (isSameString(newContact.email, " ") || matchMail(newContact.email)) {
            break;
        } else {
            printf("电子邮件格式不正确，请重新输入。\n");
        }
    }

    while (true) {
        infoInput(newContact.phone, sizeof(newContact.phone), "输入联络员电话: ");
        if (isSameString(newContact.phone, " ") || matchPhone(newContact.phone)) {
            break;
        } else {
            printf("电话号码格式不正确，请重新输入。\n");
        }
    }

    infoInput(newContact.representative, sizeof(newContact.representative), "输入联络员代表的公司: ");

    system(SYSTEM_CLEAR); // 清屏
    // saveContactPersonToFile(newContact);
    // displayContactPerson(newContact);
    printf("联络员信息已添加.\n");
}

// end widgets/info_manage.c