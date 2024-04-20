// widgets/info_manage.c
#include "../header.h"


void infoManageWidget() {
    initializeInfoFile("employees.csv", "Name|||Gender|||Birthday|||Email|||Phone|||Representative");
    initializeInfoFile("customers.csv", "Name|||Region|||Address|||LegalRepresentative|||Scale|||BusinessContactLevel|||Email|||Phone");
    initializeInfoFile("contacts.csv", "Name|||Gender|||Birthday|||Email|||Phone|||Representative");
    
    gtk_init(NULL,NULL);

    infoManageWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(infoManageWidgets.window), "通信管理系统 - 经理菜单 - 信息管理");
    gtk_window_set_default_size(GTK_WINDOW(infoManageWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(infoManageWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(infoManageWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(infoManageWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    infoManageWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(infoManageWidgets.window), infoManageWidgets.grid);
    gtk_widget_set_halign(infoManageWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(infoManageWidgets.grid, GTK_ALIGN_CENTER);

    infoManageWidgets.addEmployee_btn = gtk_button_new_with_label("增加业务员信息");
    g_signal_connect(infoManageWidgets.addEmployee_btn, "clicked", G_CALLBACK(on_addEmployee_clicked), NULL);
    gtk_grid_attach(GTK_GRID(infoManageWidgets.grid), infoManageWidgets.addEmployee_btn, 0, 0, 2, 1);

    infoManageWidgets.changeEmployee_btn = gtk_button_new_with_label("修改业务员信息");
    g_signal_connect(infoManageWidgets.changeEmployee_btn, "clicked", G_CALLBACK(on_changeEmployee_clicked), NULL);
    gtk_grid_attach(GTK_GRID(infoManageWidgets.grid), infoManageWidgets.changeEmployee_btn, 0, 1, 2, 1);

    infoManageWidgets.removeEmployeeRecord_btn = gtk_button_new_with_label("删除业务员信息");
    g_signal_connect(infoManageWidgets.removeEmployeeRecord_btn, "clicked", G_CALLBACK(on_removeEmployeeRecord_clicked), NULL);
    gtk_grid_attach(GTK_GRID(infoManageWidgets.grid), infoManageWidgets.removeEmployeeRecord_btn, 0, 2, 2, 1);

    infoManageWidgets.addCustomer_btn = gtk_button_new_with_label("增加客户信息");
    g_signal_connect(infoManageWidgets.addCustomer_btn, "clicked", G_CALLBACK(on_addCustomer_clicked), NULL);
    gtk_grid_attach(GTK_GRID(infoManageWidgets.grid), infoManageWidgets.addCustomer_btn, 0, 3, 2, 1);
    
    infoManageWidgets.changeCustomer_btn = gtk_button_new_with_label("修改客户信息");
    g_signal_connect(infoManageWidgets.changeCustomer_btn, "clicked", G_CALLBACK(on_changeCustomer_clicked), NULL);
    gtk_grid_attach(GTK_GRID(infoManageWidgets.grid), infoManageWidgets.changeCustomer_btn, 0, 4, 2, 1);
    
    infoManageWidgets.removeCustomerRecord_btn = gtk_button_new_with_label("删除客户信息");
    g_signal_connect(infoManageWidgets.removeCustomerRecord_btn, "clicked", G_CALLBACK(on_removeCustomerRecord_clicked), NULL);
    gtk_grid_attach(GTK_GRID(infoManageWidgets.grid), infoManageWidgets.removeCustomerRecord_btn, 0, 5, 2, 1);
    
    infoManageWidgets.addContact_btn = gtk_button_new_with_label("增加联络员信息");
    g_signal_connect(infoManageWidgets.addContact_btn, "clicked", G_CALLBACK(on_addContact_clicked), NULL);
    gtk_grid_attach(GTK_GRID(infoManageWidgets.grid), infoManageWidgets.addContact_btn, 0, 6, 2, 1);
    
    infoManageWidgets.changeContact_btn = gtk_button_new_with_label("修改联络员信息");
    g_signal_connect(infoManageWidgets.changeContact_btn, "clicked", G_CALLBACK(on_changeContact_clicked), NULL);
    gtk_grid_attach(GTK_GRID(infoManageWidgets.grid), infoManageWidgets.changeContact_btn, 0, 7, 2, 1);
    
    infoManageWidgets.removeContactRecord_btn = gtk_button_new_with_label("删除联络员信息");
    g_signal_connect(infoManageWidgets.removeContactRecord_btn, "clicked", G_CALLBACK(on_removeContactRecord_clicked), NULL);
    gtk_grid_attach(GTK_GRID(infoManageWidgets.grid), infoManageWidgets.removeContactRecord_btn, 0, 8, 2, 1);
    
    infoManageWidgets.backToManage_btn = gtk_button_new_with_label("返回");
    g_signal_connect(infoManageWidgets.backToManage_btn, "clicked", G_CALLBACK(on_backToManage_clicked), NULL);
    gtk_grid_attach(GTK_GRID(infoManageWidgets.grid), infoManageWidgets.backToManage_btn, 0, 9, 2, 1);
    
    gtk_widget_show_all(infoManageWidgets.window);
    gtk_main();
    
    
    // while(true) {
    //     printf("\n信息管理\n");
    //     printf("1. 增加业务员信息\n");
    //     printf("2. 修改业务员信息\n");
    //     printf("3. 删除业务员信息\n");
    //     printf("4. 增加客户信息\n");
    //     printf("5. 修改客户信息\n");
    //     printf("6. 删除客户信息\n");
    //     printf("7. 增加客户联络员信息\n");
    //     printf("8. 修改客户联络员信息\n");
    //     printf("9. 删除客户联络员信息\n");
    //     printf("0. 返回\n");
    //     printf("请选择一个操作（0-9）：");

    //     char get[MAX_LENGTH];
    //     getInput(get, sizeof(get));
    //     system(SYSTEM_CLEAR);

    //     if (!isOneChar(get)) {
    //         printf("无效的选项，请重新选择。\n");
    //         continue;  // 继续循环等待有效输入
    //     }
    //     switch (get[0]) {
    //     case '1':
    //         addEmployee();
    //         break;
    //     case '2':
    //         changeEmployee();
    //         break;
    //     case '3':
    //         removeRecord("employees.csv", "输入要删除的业务员姓名: ");
    //         break;
    //     case '4':
    //         addCustomer();
    //         break;
    //     case '5':
    //         changeCustomer();
    //         break;
    //     case '6':
    //         removeRecord("customers.csv", "输入要删除的客户姓名: ");
    //         break;
    //     case '7':
    //         addContact();
    //         break;
    //     case '8':
    //         changeContact();
    //         break;
    //     case '9':
    //         removeRecord("contacts.csv", "输入要删除的联络员姓名: ");
    //         break;
    //     case '0':
    //         return;  // 返回主菜单
    //     default:
    //         printf("无效的选项，请重新输入。\n");
    //     }
    // }
}

void addEmployee() {
    Employee newEmployee;
    addEntry(1, "employees.csv", "请输入业务员姓名：", &newEmployee, NULL, NULL);
    // saveEmployeeToFile(newEmployee);
    // displayEmployee(newEmployee);
    // printf("业务员信息已添加。\n");
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
    char name[MAX_LENGTH];
    inputTheName(name, sizeof(name), "请输入要修改的业务员姓名：");

    // 检查员工是否存在
    if (!alreadyExists("employees.csv", name)) {
        printf("业务员信息未找到。\n");
        return;
    }

    // 创建更新用的临时文件
    FILE *fp = fopen("employees.csv", "r");
    FILE *fp_temp = fopen("employees_backup.csv", "w");
    char buffer[MAX_LENGTH];

    while (fgets(buffer, sizeof(buffer), fp)) {
        char currentName[MAX_LENGTH];
        sscanf(buffer, "%254[^|||]", currentName);
        if (strcmp(name, currentName) != 0) {
            fputs(buffer, fp_temp);
        }
    }

    fclose(fp);
    fclose(fp_temp);

    // 删除原有员工记录
    if (!removeEntry("employees_backup.csv", name)) {
        printf("无法删除原有员工记录。\n");
        return;
    }

    // 添加更新后的新记录
    Employee newEmployee;
    addEntry(1, "employees_backup.csv", "请输入新的业务员姓名：", &newEmployee, NULL, NULL);

    // 移除原文件并将临时文件重命名
    remove("employees.csv");
    rename("employees_backup.csv", "employees.csv");

    saveEmployeeToFile(newEmployee);
    displayEmployee(newEmployee);
    printf("业务员信息已更新。\n");
}

void changeCustomer(){
    char name[MAX_LENGTH];
    printf("请输入要修改的客户姓名：");
    getInput(name, sizeof(name));

    // 检查客户是否存在
    if (!alreadyExists("customers.csv", name)) {
        printf("客户信息未找到。\n");
        return;
    }

    // 创建更新用的临时文件
    FILE *fp = fopen("customers.csv", "r");
    FILE *fp_temp = fopen("customers_backup.csv", "w");
    char buffer[MAX_LENGTH];

    while (fgets(buffer, sizeof(buffer), fp)) {
        char currentName[MAX_LENGTH];
        sscanf(buffer, "%254[^|||]", currentName);
        if (strcmp(name, currentName) != 0) {
            fputs(buffer, fp_temp);
        }
    }

    fclose(fp);
    fclose(fp_temp);

    // 删除原有客户记录
    if (!removeEntry("customers_backup.csv", name)) {
        printf("无法删除原有客户记录。\n");
        return;
    }

    // 添加更新后的新记录
    Customer newCustomer;
    addEntry(2, "customers_backup.csv", "请输入新的客户姓名：", NULL, &newCustomer, NULL);

    // 移除原文件并将临时文件重命名
    remove("customers.csv");
    rename("customers_backup.csv", "customers.csv");

    saveCustomerToFile(newCustomer);
    displayCustomer(newCustomer);
    printf("客户信息已更新。\n");
}

void changeContact(){
    char name[MAX_LENGTH];
    printf("请输入要修改的联系人姓名：");
    getInput(name, sizeof(name));

    // 检查联系人是否存在
    if (!alreadyExists("contacts.csv", name)) {
        printf("联系人信息未找到。\n");
        return;
    }

    // 创建更新用的临时文件
    FILE *fp = fopen("contacts.csv", "r");
    FILE *fp_temp = fopen("contacts_backup.csv", "w");
    char buffer[MAX_LENGTH];

    while (fgets(buffer, sizeof(buffer), fp)) {
        char currentName[MAX_LENGTH];
        sscanf(buffer, "%254[^|||]", currentName);
        if (strcmp(name, currentName) != 0) {
            fputs(buffer, fp_temp);
        }
    }

    fclose(fp);
    fclose(fp_temp);

    // 删除原有联系人记录
    if (!removeEntry("contacts_backup.csv", name)) {
        printf("无法删除原有联系人记录。\n");
        return;
    }

    // 添加更新后的新记录
    ContactPerson newContact;
    addEntry(3, "contacts_backup.csv", "请输入新的联系人姓名：", NULL, NULL, &newContact);

    // 移除原文件并将临时文件重命名
    remove("contacts.csv");
    rename("contacts_backup.csv", "contacts.csv");

    saveContactToFile(newContact);
    displayContact(newContact);
    printf("联系人信息已更新。\n");
}

void saveEmployeeToFile(Employee employee) {
    char fullLine[6 * MAX_LENGTH + 15];
    
    strcpy(fullLine, employee.name);
    addColumn(fullLine, employee.gender);
    addColumn(fullLine, employee.birthday);
    addColumn(fullLine, employee.email);
    addColumn(fullLine, employee.phone);
    addColumn(fullLine, employee.representative);
    
    writeLineToFile("employees.csv", fullLine);
}

void saveCustomerToFile(Customer customer) {
    char fullLine[8 * MAX_LENGTH + 21];
    
    strcpy(fullLine, customer.name);
    addColumn(fullLine, customer.region);
    addColumn(fullLine, customer.address);
    addColumn(fullLine, customer.legalRepresentative);
    addColumn(fullLine, customer.scale);
    addColumn(fullLine, customer.businessContactLevel);
    addColumn(fullLine, customer.email);
    addColumn(fullLine, customer.phone);

    writeLineToFile("customers.csv", fullLine);
}

void saveContactToFile(ContactPerson contact) {
    char fullLine[6 * MAX_LENGTH + 15];
    
    strcpy(fullLine, contact.name);
    addColumn(fullLine, contact.gender);
    addColumn(fullLine, contact.birthday);
    addColumn(fullLine, contact.email);
    addColumn(fullLine, contact.phone);
    addColumn(fullLine, contact.representative);

    writeLineToFile("contacts.csv", fullLine);
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

static void on_addEmployee_clicked(GtkWidget *widget, gpointer data) {
    addEmployee();
}
static void on_changeEmployee_clicked(GtkWidget *widget, gpointer data) {
    changeEmployee();
}
static void on_removeEmployeeRecord_clicked(GtkWidget *widget, gpointer data) {
    removeRecord("employees.csv", "输入要删除的业务员姓名: ");
}
static void on_addCustomer_clicked(GtkWidget *widget, gpointer data) {
    addCustomer();
}
static void on_changeCustomer_clicked(GtkWidget *widget, gpointer data) {
    changeCustomer();
}
static void on_removeCustomerRecord_clicked(GtkWidget *widget, gpointer data) {
    removeRecord("customers.csv", "输入要删除的客户姓名: ");
}
static void on_addContact_clicked(GtkWidget *widget, gpointer data) {
    addContact();
}
static void on_changeContact_clicked(GtkWidget *widget, gpointer data) {
    changeContact();
}
static void on_removeContactRecord_clicked(GtkWidget *widget, gpointer data) {
    removeRecord("contacts.csv", "输入要删除的联络员姓名: ");
}
static void on_backToManage_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(infoManageWidgets.window);
    gtk_widget_show(managerMenuWidgets.window);
}
// end widgets/info_manage.c