// widgets/info_manage.c
#include "../header.h"

void infoManageWidget(GtkWidget *parent) {
    initializeInfoFile("employees.csv", "Name|||Gender|||Birthday|||Email|||Phone|||Representative");
    initializeInfoFile("customers.csv", "Name|||Region|||Address|||LegalRepresentative|||Scale|||BusinessContactLevel|||Email|||Phone");
    initializeInfoFile("contacts.csv", "Name|||Gender|||Birthday|||Email|||Phone|||Representative");

    infoManageWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(infoManageWidgets.window), "通信管理系统 - 经理菜单 - 信息管理");
    gtk_window_set_default_size(GTK_WINDOW(infoManageWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(infoManageWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(infoManageWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间

    infoManageWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(infoManageWidgets.window), infoManageWidgets.grid);
    gtk_widget_set_halign(infoManageWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(infoManageWidgets.grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(infoManageWidgets.grid), 10);  // 设置行间距
    gtk_grid_set_column_spacing(GTK_GRID(infoManageWidgets.grid), 10);  // 设置列间距


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
    
    WidgetPair *widgetPair = g_slice_new(WidgetPair);
    widgetPair->parentWindow = parent;
    widgetPair->currentWindow = infoManageWidgets.window;
    infoManageWidgets.back_btn = gtk_button_new_with_label("返回");
    g_signal_connect(infoManageWidgets.back_btn, "clicked", G_CALLBACK(on_back_clicked), widgetPair);
    gtk_grid_attach(GTK_GRID(infoManageWidgets.grid), infoManageWidgets.back_btn, 0, 9, 2, 1);
    
    gtk_widget_show_all(infoManageWidgets.window);
}

void addEmployee() {
    Employee newEmployee;
    addEntry(1, "employees.csv", "请输入业务员信息：", &newEmployee, NULL, NULL);
}


void addCustomer() {
    Customer newCustomer;
    addEntry(2, "customers.csv", "请输入客户信息：",NULL, &newCustomer, NULL);
}

void addContact() {
    ContactPerson newContact;
    addEntry(3, "contacts.csv", "请输入联络员信息：", NULL, NULL, &newContact);
}

void changeEmployee(){
    char name[MAX_LENGTH];
    inputTheName(name, sizeof(name), "请输入要修改的业务员姓名：");

    // 检查员工是否存在
    if (!alreadyExists("employees.csv", name)) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "业务员信息未找到。");
        gtk_window_set_title(GTK_WINDOW(dialog), "修改失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
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
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "无法删除原有员工记录。");
        gtk_window_set_title(GTK_WINDOW(dialog), "删除失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // 添加更新后的新记录
    Employee newEmployee;
    addEntry(1, "employees_backup.csv", "请输入新的业务员信息：", &newEmployee, NULL, NULL);

    // 移除原文件并将临时文件重命名
    remove("employees.csv");
    rename("employees_backup.csv", "employees.csv");

    saveEmployeeToFile(newEmployee);
    // displayEmployee(newEmployee);
    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                GTK_MESSAGE_INFO,
                                GTK_BUTTONS_OK,
                                "业务员信息已更新。");
    gtk_window_set_title(GTK_WINDOW(dialog), "修改成功");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void changeCustomer(){
    char name[MAX_LENGTH];
    inputTheName(name, sizeof(name), "请输入要修改的客户姓名：");

    // 检查客户是否存在
    if (!alreadyExists("customers.csv", name)) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "客户信息未找到。");
        gtk_window_set_title(GTK_WINDOW(dialog), "修改失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
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
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "无法删除原有客户记录。");
        gtk_window_set_title(GTK_WINDOW(dialog), "删除失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // 添加更新后的新记录
    Customer newCustomer;
    addEntry(2, "customers_backup.csv", "请输入新的客户姓名：", NULL, &newCustomer, NULL);

    // 移除原文件并将临时文件重命名
    remove("customers.csv");
    rename("customers_backup.csv", "customers.csv");

    saveCustomerToFile(newCustomer);

    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                GTK_MESSAGE_INFO,
                                GTK_BUTTONS_OK,
                                "客户信息已更新。");
    gtk_window_set_title(GTK_WINDOW(dialog), "修改成功");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void changeContact(){
    char name[MAX_LENGTH];
    inputTheName(name, sizeof(name), "请输入要修改的联络员姓名：");

    // 检查联系人是否存在
    if (!alreadyExists("contacts.csv", name)) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "联系人信息未找到。");
        gtk_window_set_title(GTK_WINDOW(dialog), "修改失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
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
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_ERROR,
                                    GTK_BUTTONS_OK,
                                    "无法删除原有联系人记录。");
        gtk_window_set_title(GTK_WINDOW(dialog), "删除失败");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    // 添加更新后的新记录
    ContactPerson newContact;
    addEntry(3, "contacts_backup.csv", "请输入新的联系人姓名：", NULL, NULL, &newContact);

    // 移除原文件并将临时文件重命名
    remove("contacts.csv");
    rename("contacts_backup.csv", "contacts.csv");
    saveContactToFile(newContact);

    GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                GTK_MESSAGE_INFO,
                                GTK_BUTTONS_OK,
                                "联系人信息已更新。");
    gtk_window_set_title(GTK_WINDOW(dialog), "修改成功");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void saveEmployeeToFile(Employee employee) {
    char fullLine[6 * MAX_LENGTH + 15];
    memset(fullLine, 0, sizeof(fullLine));  // 初始化 fullLine 为零

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
    GtkWidget *dialog, *label, *content_area;
    GtkWindow *parent_window = NULL;  // 如果有主窗口，此处应设置为相应的 GtkWindow 指针

    dialog = gtk_dialog_new_with_buttons("显示业务员信息",
                                         parent_window,
                                         GTK_DIALOG_MODAL,
                                         "_OK", GTK_RESPONSE_OK,
                                         NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    printf("%s",employee.name);
    printf("%s",employee.birthday);
    printf("%s",employee.email);
    printf("%s",employee.gender);
    printf("%s",employee.phone);
    printf("%s",employee.representative);

    // 创建并设置标签内容
    char info[1024];
    snprintf(info, sizeof(info),
             "\n显示业务员信息:\n"
             "姓名: %-20.20s\n"
             "性别: %-10.10s\n"
             "生日: %-15.15s\n" 
             "电子邮件: %-25.25s\n" 
             "电话: %-15.15s\n"
             "代表联络公司: %-20.20s\n", 
             employee.name,
             employee.gender,
             employee.birthday,
             employee.email,
             employee.phone,
             employee.representative);

    label = gtk_label_new(info);
    gtk_container_add(GTK_CONTAINER(content_area), label);

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void displayCustomer(Customer customer) {
    GtkWidget *dialog, *label, *content_area;
    GtkWindow *parent_window = NULL;  // 如果有主窗口，此处应设置为相应的 GtkWindow 指针
    dialog = gtk_dialog_new_with_buttons("显示客户信息",
                                         parent_window,
                                         GTK_DIALOG_MODAL,
                                         "_OK", GTK_RESPONSE_OK,
                                         NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // 创建并设置标签内容
    char info[1024];
    snprintf(info, sizeof(info),
             "\n显示客户信息:\n"
             "姓名: %-20.20s\n"
             "区域: %-20.20s\n"
             "地址: %-30.30s\n"
             "法人: %-20.20s\n"
             "规模: %-10.10s\n"
             "业务联系程度: %-15.15s\n"
             "电子邮件: %-25.25s\n"
             "电话: %-15.15s\n",
             customer.name,
             customer.region,
             customer.address,
             customer.legalRepresentative,
             customer.scale,
             customer.businessContactLevel,
             customer.email,
             customer.phone);

    label = gtk_label_new(info);
    gtk_container_add(GTK_CONTAINER(content_area), label);

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


void displayContact(ContactPerson contact) {
    GtkWidget *dialog, *label, *content_area;
    GtkWindow *parent_window = NULL;  // 如果有主窗口，此处应设置为相应的 GtkWindow 指针

    dialog = gtk_dialog_new_with_buttons("显示联络员信息",
                                         parent_window,
                                         GTK_DIALOG_MODAL,
                                         "_OK", GTK_RESPONSE_OK,
                                         NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // 创建并设置标签内容
    char info[1024];
    snprintf(info, sizeof(info),
             "\n显示联络员信息:\n"
             "姓名: %-20.20s\n"
             "性别: %-10.10s\n"
             "生日: %-15.15s\n"
             "电子邮件: %-25.25s\n"
             "电话: %-15.15s\n"
             "代表公司: %-20.20s\n",
             contact.name,
             contact.gender,
             contact.birthday,
             contact.email,
             contact.phone,
             contact.representative);

    label = gtk_label_new(info);
    gtk_container_add(GTK_CONTAINER(content_area), label);

    gtk_widget_show_all(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
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

// end widgets/info_manage.c