// widgets/info_manage.c
#include "../header.h"

void infoManageWidget();
void addEmployee();
void addCustomer();
void addContact();
void changeEmployee();
void changeCustomer();
void changeContact();
void saveEmployeeToFile(Employee employee);
void saveCustomerToFile(Customer customer);
void saveContactToFile(ContactPerson contact);
void displayEmployee(Employee employee);
void displayCustomer(Customer customer);
void displayContact(ContactPerson contact);

void infoManageWidget() {
    initializeInfoFile("employees.csv", "Name|||Gender|||Birthday|||Email|||Phone|||Representative");
    initializeInfoFile("customers.csv", "Name|||Region|||Address|||LegalRepresentative|||Scale|||BusinessContactLevel|||Email|||Phone");
    initializeInfoFile("contacts.csv", "Name|||Gender|||Birthday|||Email|||Phone|||Representative");
    while(true) {
        printf("\n您好，经理！\n");
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
                addEmployee();
                break;
            case '2':

                break;
            case '3':
                removeRecord("employees.csv", "输入要删除的业务员姓名: ");
                break;
            case '4':
                addCustomer();
                break;
            case '5':

                break;
            case '6':
                removeRecord("customers.csv", "输入要删除的客户姓名: ");
                break;
            case '7':
                addContact();
                break;
            case '8':

                break;
            case '9':
                removeRecord("contacts.csv", "输入要删除的联络员姓名: ");
                break;
            case '0':
                return;  // 返回主菜单
            default:
                printf("无效的选项，请重新输入。\n");
        }
    }
}

void addEmployee() {
    Employee newEmployee;
    addEntry(1, "employees.csv", "请输入业务员姓名：", &newEmployee, NULL, NULL);
    saveEmployeeToFile(newEmployee);
    displayEmployee(newEmployee);
    printf("业务员信息已添加。\n");
}

void addCustomer() {
    Customer newCustomer;
    addEntry(2, "customers.csv", "请输入客户姓名：",NULL, &newCustomer, NULL);
    saveCustomerToFile(newCustomer);
    displayCustomer(newCustomer);
    printf("客户信息已添加。\n");
}

void addContact() {
    ContactPerson newContact;
    addEntry(3, "contacts.csv", "请输入联络员姓名：", NULL, NULL, &newContact);
    saveContactToFile(newContact);
    displayContact(newContact);
    printf("联络员信息已添加。\n");
}

void changeEmployee(){

}

void changeCustomer(){
}

void changeContact(){
}

void saveEmployeeToFile(Employee employee) {
    FILE *file = fopen("employees.csv", "a");
    if (!file) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s|||%s|||%s|||%s|||%s|||%s\n",
        employee.name,
        employee.gender,
        employee.birthday,
        employee.email,
        employee.phone,
        employee.representative
    );
    fclose(file);
}

void saveCustomerToFile(Customer customer) {
    FILE *file = fopen("customers.csv", "a");
    if (!file) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s|||%s|||%s|||%s|||%s|||%s|||%s|||%s\n",
        customer.name,
        customer.region,
        customer.address,
        customer.legalRepresentative,
        customer.scale,
        customer.businessContactLevel,
        customer.email,
        customer.phone
    );
    fclose(file);
}

void saveContactToFile(ContactPerson contact) {
    FILE *file = fopen("contacts.csv", "a");
    if (!file) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s|||%s|||%s|||%s|||%s|||%s\n",
        contact.name,
        contact.gender,
        contact.birthday,
        contact.email,
        contact.phone,
        contact.representative
    );
    fclose(file);
}

void displayEmployee(Employee employee) {
    printf("\n显示业务员信息:\n");
    printf("姓名: %-20s\n", employee.name);
    printf("性别: %-10s\n", employee.gender);
    printf("生日: %-15s\n", employee.birthday);
    printf("电子邮件: %-25s\n", employee.email);
    printf("电话: %-15s\n", employee.phone);
    printf("代表联络公司: %-20s\n", employee.representative);
}

void displayCustomer(Customer customer) {
    printf("\n显示客户信息:\n");
    printf("姓名: %-20s\n", customer.name);
    printf("区域: %-20s\n", customer.region);
    printf("地址: %-30s\n", customer.address);
    printf("法人: %-20s\n", customer.legalRepresentative);
    printf("规模: %-10s\n", customer.scale);
    printf("业务联系程度: %-15s\n", customer.businessContactLevel);
    printf("电子邮件: %-25s\n", customer.email);
    printf("电话: %-15s\n", customer.phone);
}

void displayContact(ContactPerson contact) {
    printf("\n显示联络员信息:\n");
    printf("姓名: %-20s\n", contact.name);
    printf("性别: %-10s\n", contact.gender);
    printf("生日: %-15s\n", contact.birthday);
    printf("电子邮件: %-25s\n", contact.email);
    printf("电话: %-15s\n", contact.phone);
    printf("代表公司: %-20s\n", contact.representative);
}

// end widgets/info_manage.c