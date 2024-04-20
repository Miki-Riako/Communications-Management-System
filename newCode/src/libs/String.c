// String.c
#include "../header.h"
// 检验输入是否为空
bool isEmpty(const char *input) { return (input[0] == '\0'); }

// 检验输入是否为单个字符
bool isOneChar(const char *input) { return (strlen(input) == 1); }

// 清除缓冲区
void clearBuffer() { while (getchar() != '\n'); }

// 获取字符串
void getInput(char *input, int buffer_size) {
    if (fgets(input, buffer_size, stdin) != NULL) {
        input[strcspn(input, "\n")] = 0; // 去除 fgets 捕获的换行符
    } else {
        fprintf(stderr, "Error reading input.\n");
    }
}

// 切割函数但是会手动分配内存（少用）
char *splitLine(char *input, const char *delim, int num) {
    int count = 0;
    const char *start = input;
    const char *end = input;

    // 遍历整个字符串
    while (*end != '\0') {
        if (strncmp(end, delim, strlen(delim)) == 0) {
            if (count == num) {
                // 在找到的分割点处截断，返回起始部分
                int length = end - start;
                char *result = malloc(length + 1); // 分配内存
                if (result == NULL) return NULL; // 检查内存分配是否成功
                memcpy(result, start, length); // 复制内容
                result[length] = '\0'; // 设置结束符
                return result;
            }
            ++count; // 增加计数器
            end += strlen(delim); // 跳过分隔符
            start = end; // 更新开始位置
        } else {
            ++end; // 移动到下一个字符
        }
    }

    // 处理最后一段
    if (count == num) {
        return strdup(start); // 返回剩余部分的副本
    }

    return "";
}

// 是相同的字符串
bool isSameString(const char *str1, const char *str2) { return (strcmp(str1, str2) == 0); }

// 这个函数负责去除字段末尾可能的分隔符和空白字符
void cleanField(char *field) {
    char *end = field + strlen(field) - 1;
    while (end > field && (isspace((unsigned char)*end) || *end == '|' || *end == '\n' || *end == '\r')) {
        *end = '\0';
        --end;
    }
}

// 信息写入
void infoInput(char *input, int buffer_size, const char *prompt) {
    printf("%s", prompt);
    if (fgets(input, buffer_size, stdin) == NULL) {
        printf("错误：无法读取输入。\n");
        strcpy(input, " "); // 安全处理
        return;
    }

    input[strcspn(input, "\n")] = 0;  // 移除尾部的换行符
    if (isEmpty(input)) strcpy(input, " ");
}

// 输入非空姓名
void inputTheName(char *name, int buffer_size, const char *prompt) {
    while (true) {
        infoInput(name, buffer_size, prompt);
        if (!isSameString(name, " ")) {
            break;
        } else {
            printf("请输入一个有效的名字。\n");
        }
    }
}

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *name_entry;
    GtkWidget *gender_entry;
    GtkWidget *birthday_entry;
    GtkWidget *email_entry;
    GtkWidget *phone_entry;
    GtkWidget *region_entry;
    GtkWidget *address_entry;
    GtkWidget *legal_rep_entry;
    GtkWidget *scale_entry;
    GtkWidget *contact_level_entry;
    GtkWidget *representative_entry;
    GtkWidget *save_entry_button;
    GtkWidget *cancel_button;
    int section;
    const char *filename;
    Employee *employee;
    Customer *customer;
    ContactPerson *contact;
} EntryWidgets;
EntryWidgets entryWidgets;
static void on_save_entry_clicked(GtkWidget *widget, EntryWidgets *entryWidgets);
static void on_cancel_save_clicked(GtkWidget *widget, EntryWidgets *entryWidgets);

// 添加新的用户实例
void addEntry(int section, const char *filename, const char *prompt, Employee *employee, Customer *customer, ContactPerson *contact) {
    gtk_init(NULL, NULL);
    entryWidgets.section = section;
    entryWidgets.filename = filename;
    entryWidgets.employee = employee;
    entryWidgets.customer = customer;
    entryWidgets.contact = contact;
    entryWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(entryWidgets.window), "添加用户界面");
    gtk_window_set_default_size(GTK_WINDOW(entryWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(entryWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(entryWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    g_signal_connect(entryWidgets.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    entryWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(entryWidgets.window), entryWidgets.grid);
    gtk_widget_set_halign(entryWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(entryWidgets.grid, GTK_ALIGN_CENTER);
    // 公共字段
    entryWidgets.name_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("姓名:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.name_entry, 1, 0, 1, 1);

    // 条件字段
    if (entryWidgets.section == 1) {
        entryWidgets.gender_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("性别:"), 0, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.gender_entry, 1, 1, 1, 1);

        entryWidgets.birthday_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("生日:"), 0, 2, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.birthday_entry, 1, 2, 1, 1);
    
        entryWidgets.email_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("邮件:"), 0, 3, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.email_entry, 1, 3, 1, 1);

        entryWidgets.phone_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("电话:"), 0, 4, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.phone_entry, 1, 4, 1, 1);
    
        entryWidgets.representative_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("业务员代表的公司:"), 0, 5, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.representative_entry, 1, 5, 1, 1);
    
        // 保存按钮
        entryWidgets.save_entry_button = gtk_button_new_with_label("保存");
        g_signal_connect(entryWidgets.save_entry_button, "clicked", G_CALLBACK(on_save_entry_clicked), &entryWidgets);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.save_entry_button, 0, 6, 1, 1);

        // 取消按钮
        entryWidgets.save_entry_button = gtk_button_new_with_label("取消");
        g_signal_connect(entryWidgets.save_entry_button, "clicked", G_CALLBACK(on_cancel_save_clicked), &entryWidgets);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.save_entry_button, 1, 6, 1, 1);
    } else if(entryWidgets.section == 2) {
        entryWidgets.region_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("客户所在区域:"), 0, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.region_entry, 1, 1, 1, 1);

        entryWidgets.address_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("客户公司地址:"), 0, 2, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.address_entry, 1, 2, 1, 1);
    
        entryWidgets.legal_rep_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("客户公司法人:"), 0, 3, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.legal_rep_entry, 1, 3, 1, 1);

        entryWidgets.scale_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("客户规模:"), 0, 4, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.scale_entry, 1, 4, 1, 1);
    
        entryWidgets.contact_level_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("客户业务联系程度（高、中、低）:"), 0, 5, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.contact_level_entry, 1, 5, 1, 1);

        entryWidgets.email_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("邮件:"), 0, 6, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.email_entry, 1, 6, 1, 1);

        entryWidgets.phone_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("电话:"), 0, 7, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.phone_entry, 1, 7, 1, 1);  
    
        // 保存按钮
        entryWidgets.save_entry_button = gtk_button_new_with_label("保存");
        g_signal_connect(entryWidgets.save_entry_button, "clicked", G_CALLBACK(on_save_entry_clicked), &entryWidgets);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.save_entry_button, 0, 8, 1, 1);

        // 取消按钮
        entryWidgets.save_entry_button = gtk_button_new_with_label("取消");
        g_signal_connect(entryWidgets.save_entry_button, "clicked", G_CALLBACK(on_cancel_save_clicked), &entryWidgets);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.save_entry_button, 1, 8, 1, 1);
    } else if(entryWidgets.section == 3) {
        entryWidgets.gender_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("性别:"), 0, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.gender_entry, 1, 1, 1, 1);

        entryWidgets.birthday_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("生日:"), 0, 2, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.birthday_entry, 1, 2, 1, 1);

        entryWidgets.email_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("邮件:"), 0, 3, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.email_entry, 1, 3, 1, 1);

        entryWidgets.phone_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("电话:"), 0, 4, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.phone_entry, 1, 4, 1, 1);
    
        entryWidgets.representative_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("联络员代表的公司:"), 0, 5, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.representative_entry, 1, 5, 1, 1);
    
        // 保存按钮
        entryWidgets.save_entry_button = gtk_button_new_with_label("保存");
        g_signal_connect(entryWidgets.save_entry_button, "clicked", G_CALLBACK(on_save_entry_clicked), &entryWidgets);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.save_entry_button, 0, 6, 1, 1);

        // 取消按钮
        entryWidgets.save_entry_button = gtk_button_new_with_label("取消");
        g_signal_connect(entryWidgets.save_entry_button, "clicked", G_CALLBACK(on_cancel_save_clicked), &entryWidgets);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.save_entry_button, 1, 6, 1, 1);

    }
    else {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "添加身份错误。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    gtk_widget_show_all(entryWidgets.window);
    gtk_main();
}

static void on_save_entry_clicked(GtkWidget *widget, EntryWidgets *entryWidgets) { 
    char userName[MAX_LENGTH];
    char gender[MAX_LENGTH];
    char birthday[MAX_LENGTH];
    char email[MAX_LENGTH];
    char phone[MAX_LENGTH];

    const char *userName_const = gtk_entry_get_text(GTK_ENTRY(entryWidgets->name_entry));
    strncpy(userName,userName_const,MAX_LENGTH);
    userName[strcspn(userName, "\n")] = 0;
    if (isEmpty(userName)) strcpy(userName, " ");

    if (alreadyExists(entryWidgets->filename, userName)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(entryWidgets->window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "姓名已存在，请重新输入。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    if (entryWidgets->section == 2) {
        const char *scale_const = gtk_entry_get_text(GTK_ENTRY(entryWidgets->scale_entry));
        const char *businessContactLevel_const = gtk_entry_get_text(GTK_ENTRY(entryWidgets->contact_level_entry));
        
        strncpy(entryWidgets->customer->scale,scale_const,MAX_LENGTH);
        entryWidgets->customer->scale[strcspn(entryWidgets->customer->scale, "\n")] = 0;
        if (isEmpty(entryWidgets->customer->scale)) strcpy(entryWidgets->customer->scale, " ");
        strncpy(entryWidgets->customer->businessContactLevel,businessContactLevel_const,MAX_LENGTH);
        entryWidgets->customer->businessContactLevel[strcspn(entryWidgets->customer->businessContactLevel, "\n")] = 0;
        if (isEmpty(entryWidgets->customer->businessContactLevel)) strcpy(entryWidgets->customer->businessContactLevel, " ");
        if (!isSameString(entryWidgets->customer->scale, " ") && !matchScale(entryWidgets->customer->scale)) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(entryWidgets->window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "客户规模格式不正确，请重新输入。");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }
        if (!isSameString(entryWidgets->customer->businessContactLevel, " ") && !matchContactLevel(entryWidgets->customer->businessContactLevel)) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(entryWidgets->window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "客户业务联系程度格式不正确，请重新输入。");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }
    } else { // section == 1 || section == 3
        const char *gender_const = gtk_entry_get_text(GTK_ENTRY(entryWidgets->gender_entry));
        const char *birthday_const = gtk_entry_get_text(GTK_ENTRY(entryWidgets->birthday_entry));
        
        strncpy(gender,gender_const,MAX_LENGTH);
        gender[strcspn(gender, "\n")] = 0;
        if (isEmpty(gender)) strcpy(gender, " ");
        strncpy(birthday,birthday_const,MAX_LENGTH);
        birthday[strcspn(birthday, "\n")] = 0;
        if (isEmpty(birthday)) strcpy(birthday, " ");
    }


    const char *email_const = gtk_entry_get_text(GTK_ENTRY(entryWidgets->email_entry));        
    strncpy(email,email_const,MAX_LENGTH);
    email[strcspn(email, "\n")] = 0;
    if (isEmpty(email)) strcpy(email, " ");
    if (!isSameString(email, " ") && !matchMail(email)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(entryWidgets->window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "电子邮件格式不正确，请重新输入。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    const char *phone_const = gtk_entry_get_text(GTK_ENTRY(entryWidgets->phone_entry));        
    strncpy(phone,phone_const,MAX_LENGTH);
    phone[strcspn(phone, "\n")] = 0;
    if (isEmpty(phone)) strcpy(phone, " ");
    if (!isSameString(phone, " ") && !matchPhone(phone)) {
        GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(entryWidgets->window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "电话号码格式不正确，请重新输入。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }
    
    switch (entryWidgets->section) {
    case 1:
        strcpy(entryWidgets->employee->name, userName);
        strcpy(entryWidgets->employee->gender, gender);
        strcpy(entryWidgets->employee->birthday, birthday);
        strcpy(entryWidgets->employee->email, email);
        strcpy(entryWidgets->employee->phone, phone);

        const char *representative_const = gtk_entry_get_text(GTK_ENTRY(entryWidgets->representative_entry));
        strncpy(entryWidgets->employee->representative,representative_const,MAX_LENGTH);
        entryWidgets->employee->representative[strcspn(entryWidgets->employee->representative, "\n")] = 0;
        if (isEmpty(entryWidgets->employee->representative)) strcpy(entryWidgets->employee->representative, " ");
        saveEmployeeToFile(*entryWidgets->employee);
        displayEmployee(*entryWidgets->employee);
        break;
    case 2:
        strcpy(entryWidgets->customer->name, userName);
        strcpy(entryWidgets->customer->email, email);
        strcpy(entryWidgets->customer->phone, phone);
        saveCustomerToFile(*entryWidgets->customer);
        displayCustomer(*entryWidgets->customer);
        break;
    case 3:
        strcpy(entryWidgets->contact->name, userName);
        strcpy(entryWidgets->contact->gender, gender);
        strcpy(entryWidgets->contact->birthday, birthday);
        strcpy(entryWidgets->contact->email, email);
        strcpy(entryWidgets->contact->phone, phone);
        infoInput(entryWidgets->contact->representative, sizeof(entryWidgets->contact->representative), "输入联络员代表的公司: ");
        
        strncpy(entryWidgets->contact->representative,representative_const,MAX_LENGTH);
        entryWidgets->contact->representative[strcspn(entryWidgets->contact->representative, "\n")] = 0;
        if (isEmpty(entryWidgets->contact->representative)) strcpy(entryWidgets->contact->representative, " ");
        saveContactToFile(*entryWidgets->contact);
        displayContact(*entryWidgets->contact);
        break;
    default:
        return;
    }
    gtk_widget_hide(entryWidgets->window);
    return;
}

void on_cancel_save_clicked(GtkWidget *widget, EntryWidgets *entryWidgets)
{
    gtk_widget_hide(entryWidgets->window);
}

// 增加后一列
void addColumn(char *fullLine, const char *newOne) {
    strcat(fullLine, "|||");
    strcat(fullLine, newOne);
}

// 打印客户信息
void printNode_cus(node_cus *node) {
    printf("%s - %s - %s - %s - %s - %s - %s - %s\n", 
        node->customer.name,
        node->customer.region,
        node->customer.address, 
        node->customer.legalRepresentative,
        node->customer.scale, 
        node->customer.businessContactLevel,
        node->customer.email,
        node->customer.phone
    );
}

// 打印联络人信息
void printNode_ctp(node_ctp *node) {
    printf("%s - %s - %s - %s - %s - %s\n", 
        node->contactPerson.name,
        node->contactPerson.gender,
        node->contactPerson.birthday, 
        node->contactPerson.email,
        node->contactPerson.phone,
        node->contactPerson.representative
    );
}

// 打印业务员信息
void printNode_emp(node_emp *node) {
    printf("%s - %s - %s - %s - %s - %s\n", 
        node->employee.name,
        node->employee.gender,
        node->employee.birthday, 
        node->employee.email,
        node->employee.phone,
        node->employee.representative
    );
}

// 打印通信记录信息
void printNode_rec(node_rec *node) {
    printf("%s - %s - %s - %s - %s - %s - %s\n", 
        node->record.user,
        node->record.companyName,
        node->record.contactName,
        node->record.date, 
        node->record.time,
        node->record.duration,
        node->record.content
    );
}

// 显示一个小菜单
int beforeInfo(head_node *head, const char *prompt) {
    char get[MAX_LENGTH];
    if (IsManager) {
        printf("请选择%s的数据类型：\n", prompt);
        printf("1. 客户\n");
        printf("2. 联络人\n");
        printf("3. 业务员\n");
        printf("输入选项：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);
        
        if (!isOneChar(get)) {
            printf("无效的选择\n");
            return -1;
        }
    } else {
        get[0] = '1';
    }

    switch (get[0]) {
    case '1':
        if (head->is_cus) {
            return 0;
        } else {
            printf("无法%s客户信息。\n", prompt);
            return -1;
        }
    case '2':
        if (IsManager && head->is_ctp) {
            return 1;
        } else {
            printf("无法%s联络人信息。\n", prompt);
            return -1;
        }
    case '3':
        if (IsManager && head->is_emp) {
            return 2;
        } else {
            printf("无法%s业务员信息。\n", prompt);
            return -1;
        }
    // case '4':
    //     if (IsManager && head->is_rec) {
    //         return 3;
    //     } else {
    //         printf("无法%s记录信息。\n", prompt);
    //         return -1;
    //     }
    default:
        printf("无效的选择。\n");
        return -1;
    }
}

// 打印需要的链表内容
void printNodeList(head_node *head, int choice) {
    if (head == NULL || head->is_empty) {
        printf("没有可显示的数据。\n");
        return;
    }

    switch (choice) {
    case 0:  // 客户信息
        if (head->is_cus) {
            node_cus *current = head->next_cus;
            printf("客户名 - 地区 - 地址 - 法人 - 规模 - 联系等级 - 邮箱 - 电话\n");
            while (current != NULL) {
                printNode_cus(current);
                current = current->next;
            }
        } else {
            printf("没有可显示的客户信息。\n");
        }
        break;
    case 1:  // 联络人信息
        if (head->is_ctp) {
            node_ctp *current = head->next_ctp;
            printf("联络人名称 - 性别 - 生日 - 邮箱 - 电话 - 代表公司\n");
            while (current != NULL) {
                printNode_ctp(current);
                current = current->next;
            }
        } else {
            printf("没有可显示的联络人信息。\n");
        }
        break;
    case 2:  // 业务员信息
        if (head->is_emp) {
            node_emp *current = head->next_emp;
            printf("业务员名称 - 性别 - 生日 - 邮箱 - 电话 - 代表公司\n");
            while (current != NULL) {
                printNode_emp(current);
                current = current->next;
            }
        } else {
            printf("没有可显示的业务员信息。\n");
        }
        break;
    case 3:  // 通信记录
        if (head->is_rec) {
            node_rec *current = head->next_rec;
            printf("管理用户 - 公司名称 - 联络人 - 日期 - 时间 - 时长 - 通信内容\n");
            while (current != NULL) {
                printNode_rec(current);
                current = current->next;
            }
        } else {
            printf("没有可显示的通信记录信息。\n");
        }
        break;
    default:
        printf("无效的选项。\n");
        break;
    }
}