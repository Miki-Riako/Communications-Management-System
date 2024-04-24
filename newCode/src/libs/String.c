// String.c
#include "../header.h"
// 检验输入是否为空
bool isEmpty(const char *input) { return ((input == NULL) ||(input[0] == '\0')); }

// 检验输入是否为单个字符
bool isOneChar(const char *input) { return (strlen(input) == 1); }

// 清除缓冲区
void clearBuffer() { while (getchar() != '\n'); }

// 字符变数字
int charToInt(char c) { return (int)(c - '0'); }

// 获取字符串
bool getInput(char *input, int buffer_size) {
    GtkWidget *dialog, *entry, *content_area;
    GtkEntryBuffer *entry_buffer;

    // 创建一个对话框窗口，带有 OK 和 Cancel 按钮
    dialog = gtk_dialog_new_with_buttons("请输入",
                                         NULL, // 无父窗口
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "_OK", GTK_RESPONSE_OK,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // 创建一个文本输入框
    entry_buffer = gtk_entry_buffer_new(NULL, 0);
    entry = gtk_entry_new_with_buffer(entry_buffer);
    gtk_container_add(GTK_CONTAINER(content_area), entry);
    
    // 显示所有控件
    gtk_widget_show_all(dialog);

    // 运行对话框
    int response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_OK) {
        const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
        strncpy(input, text, buffer_size - 1);
        input[buffer_size - 1] = '\0';  // 确保字符串是空终止的

        // 清理
        gtk_widget_destroy(dialog);
        while (gtk_events_pending()) {
            gtk_main_iteration();
        }
        return true;
    } else {
        fprintf(stderr, "获取输入失败或用户取消输入\n");
        input[0] = '\0';  // 如果用户取消，返回一个空字符串
        
        // 清理
        gtk_widget_destroy(dialog);
        while (gtk_events_pending()) {
            gtk_main_iteration();
        }
        return false;
    }

}

// 函数用于检查并去除字符串末尾的换行符
void stripNewline(char *str) {
    if (str == NULL) return; // 如果字符串为空，直接返回
    size_t len = strlen(str); // 获取字符串的长度
    if (len > 0 && str[len - 1] == '\n') { // 如果字符串的最后一个字符是换行符
        str[len - 1] = '\0'; // 替换为字符串结束符
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
bool infoInput(char *input, int buffer_size, const char *prompt) {
    GtkWidget *dialog, *entry, *label, *content_area;

    // 创建对话框
    dialog = gtk_dialog_new_with_buttons("Input",
                                         NULL,  // 没有父窗口
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "_OK", GTK_RESPONSE_OK,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // 创建输入框和标签
    entry = gtk_entry_new();
    label = gtk_label_new(prompt);
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_container_add(GTK_CONTAINER(content_area), entry);

    // 显示所有控件
    gtk_widget_show_all(dialog);

    // 运行对话框并等待用户响应
    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
        const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
        strncpy(input, text, buffer_size - 1);
        input[buffer_size - 1] = '\0';  // 确保空终止

        // 清理和关闭对话框
        gtk_widget_destroy(dialog);
        while (gtk_events_pending()) gtk_main_iteration();

        return true;
    } else {
        // printf("取消输入(input为“ ”)\n");
        strcpy(input, " "); // 安全处理

        // 清理和关闭对话框
        gtk_widget_destroy(dialog);
        while (gtk_events_pending()) gtk_main_iteration();

        return false;
    }
}

// 输入非空姓名
void inputTheName(char *name, int buffer_size, const char *prompt) {
    GtkWidget *dialog, *entry, *label, *content_area;

    // 创建对话框
    dialog = gtk_dialog_new_with_buttons("输入名称",
                                         NULL,  // 没有父窗口
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "_OK", GTK_RESPONSE_OK,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

    // 创建输入框和标签
    entry = gtk_entry_new();
    label = gtk_label_new(prompt);
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_container_add(GTK_CONTAINER(content_area), entry);

    // 显示所有控件
    gtk_widget_show_all(dialog);

    // 事件循环
    while (true) {
        int response = gtk_dialog_run(GTK_DIALOG(dialog));
        if (response == GTK_RESPONSE_OK) {
            const char *text = gtk_entry_get_text(GTK_ENTRY(entry));
            strncpy(name, text, buffer_size - 1);
            name[buffer_size - 1] = '\0';  // 确保空终止

            // 去除可能的前后空白字符
            g_strstrip(name);

            if (name[0] != '\0' && !isSameString(name, " ")) {
                break;  // 有效输入
            } else {
                GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(dialog),
                    GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                    GTK_MESSAGE_ERROR,
                    GTK_BUTTONS_OK,
                    "请输入一个有效的名字。");
                gtk_dialog_run(GTK_DIALOG(error_dialog));
                gtk_widget_destroy(error_dialog);
            }
        } else {
            // 用户选择取消或关闭对话框
            printf("取消输入(name为“ ”)\n");

            strcpy(name, " ");
            break;
        }
    }

    // 清理
    gtk_widget_destroy(dialog);
}

// 添加新的用户实例
void addEntry(int section, const char *filename, const char *prompt, Employee *employee, Customer *customer, ContactPerson *contact) {
    entryWidgets.section = section;
    entryWidgets.filename = filename;
    entryWidgets.employee = employee;
    entryWidgets.customer = customer;
    entryWidgets.contact = contact;
    entryWidgets.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(entryWidgets.window), prompt);
    gtk_window_set_default_size(GTK_WINDOW(entryWidgets.window), 500, 400);
    gtk_container_set_border_width(GTK_CONTAINER(entryWidgets.window), 10);
    gtk_window_set_position(GTK_WINDOW(entryWidgets.window), GTK_WIN_POS_CENTER);  // 设置窗口在屏幕中间
    
    entryWidgets.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(entryWidgets.window), entryWidgets.grid);
    gtk_widget_set_halign(entryWidgets.grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(entryWidgets.grid, GTK_ALIGN_CENTER);
    gtk_grid_set_row_spacing(GTK_GRID(entryWidgets.grid), 10);  // 设置行间距
    gtk_grid_set_column_spacing(GTK_GRID(entryWidgets.grid), 10);  // 设置列间距


    // 公共字段
    entryWidgets.name_entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("姓名:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.name_entry, 1, 0, 1, 1);

    // 条件字段
    if (entryWidgets.section == 1) { // 业务员
        entryWidgets.gender_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("性别:"), 0, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.gender_entry, 1, 1, 1, 1);

        entryWidgets.birthday_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("生日（YYYY-MM-DD）:"), 0, 2, 1, 1);
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
    } else if(entryWidgets.section == 2) {  // 客户
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
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("客户规模（大、中、小）:"), 0, 4, 1, 1);
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
    } else if(entryWidgets.section == 3) {  //联络员
        entryWidgets.gender_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("性别:"), 0, 1, 1, 1);
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), entryWidgets.gender_entry, 1, 1, 1, 1);

        entryWidgets.birthday_entry = gtk_entry_new();
        gtk_grid_attach(GTK_GRID(entryWidgets.grid), gtk_label_new("生日（YYYY-MM-DD）:"), 0, 2, 1, 1);
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
        const char *region_const = convert_to_utf8(gtk_entry_get_text(GTK_ENTRY(entryWidgets->region_entry)));

        const char *address_const = convert_to_utf8(gtk_entry_get_text(GTK_ENTRY(entryWidgets->address_entry)));
        const char *legalRepresentative_const = convert_to_utf8(gtk_entry_get_text(GTK_ENTRY(entryWidgets->legal_rep_entry)));
        const char *scale_const = convert_to_utf8(gtk_entry_get_text(GTK_ENTRY(entryWidgets->scale_entry)));
        const char *businessContactLevel_const = convert_to_utf8(gtk_entry_get_text(GTK_ENTRY(entryWidgets->contact_level_entry)));
        strncpy(entryWidgets->customer->region,region_const,MAX_LENGTH);
        entryWidgets->customer->region[strcspn(entryWidgets->customer->region, "\n")] = 0;
        strncpy(entryWidgets->customer->address,address_const,MAX_LENGTH);
        entryWidgets->customer->address[strcspn(entryWidgets->customer->address, "\n")] = 0;
        strncpy(entryWidgets->customer->legalRepresentative,legalRepresentative_const,MAX_LENGTH);
        entryWidgets->customer->legalRepresentative[strcspn(entryWidgets->customer->legalRepresentative, "\n")] = 0;
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
        const char *gender_const = convert_to_utf8(gtk_entry_get_text(GTK_ENTRY(entryWidgets->gender_entry)));
        const char *birthday_const = convert_to_utf8(gtk_entry_get_text(GTK_ENTRY(entryWidgets->birthday_entry)));
        strncpy(gender,gender_const,MAX_LENGTH);
        gender[strcspn(gender, "\n")] = 0;
        if (isEmpty(gender)) strcpy(gender, " ");
        
        if (!isSameString(gender, " ") && !matchGender(gender)) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(entryWidgets->window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "性别格式不正确，请重新输入。");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }
        strncpy(birthday,birthday_const,MAX_LENGTH);
        birthday[strcspn(birthday, "\n")] = 0;
        if (isEmpty(birthday)) strcpy(birthday, " ");
        printf("birthday Converted string: %s\n", birthday);
        if (!isSameString(birthday, " ") && !matchDate(birthday)) {
            GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(entryWidgets->window),
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "日期格式不正确，请重新输入。");
            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
            return;
        }
    }


    const char *email_const = convert_to_utf8(gtk_entry_get_text(GTK_ENTRY(entryWidgets->email_entry)));        
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

    const char *phone_const = convert_to_utf8(gtk_entry_get_text(GTK_ENTRY(entryWidgets->phone_entry)));        
    strncpy(phone,phone_const,MAX_LENGTH);
    phone[strcspn(phone, "\n")] = 0;
    if (isEmpty(phone)) strcpy(phone, " ");
    printf("phone Converted string: %s\n", phone);  // debug
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
    
    const char *representative_const;
    switch (entryWidgets->section) {
    case 1:
        representative_const = convert_to_utf8(gtk_entry_get_text(GTK_ENTRY(entryWidgets->representative_entry)));
        strcpy(entryWidgets->employee->representative,representative_const);
        entryWidgets->employee->representative[strcspn(entryWidgets->employee->representative, "\n")] = 0;
        if (isEmpty(entryWidgets->employee->representative)) strcpy(entryWidgets->employee->representative, " ");
        // saveEmployeeToFile(*(entryWidgets->employee));
        char fullLine[6 * MAX_LENGTH + 15];
        memset(fullLine, 0, sizeof(fullLine));  // 初始化 fullLine 为零
        strcpy(fullLine, userName);
        addColumn(fullLine, gender);
        addColumn(fullLine, birthday);
        addColumn(fullLine, email);
        addColumn(fullLine, phone);
        addColumn(fullLine, representative_const);
        writeLineToFile("employees.csv", fullLine);
        // displayEmployee(*(entryWidgets->employee));
        GtkWidget *newdialog, *newlabel, *newcontent_area;
        
        newdialog = gtk_dialog_new_with_buttons("显示业务员信息",
                                            NULL,
                                            GTK_DIALOG_MODAL,
                                            "_OK", GTK_RESPONSE_OK,
                                            NULL);

        newcontent_area = gtk_dialog_get_content_area(GTK_DIALOG(newdialog));

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
                userName,
                gender,
                birthday,
                email,
                phone,
                representative_const);

        newlabel = gtk_label_new(info);
        gtk_container_add(GTK_CONTAINER(newcontent_area), newlabel);

        gtk_widget_show_all(newdialog);
        gtk_dialog_run(GTK_DIALOG(newdialog));
        gtk_widget_destroy(newdialog);
        break;
    case 2:
        // strncpy(entryWidgets->customer->name, userName,MAX_LENGTH);
        // strncpy(entryWidgets->customer->email, email,MAX_LENGTH);
        // strncpy(entryWidgets->customer->phonWe, phone,MAX_LENGTH);
        // saveCustomerToFile(*(entryWidgets->customer));
        ;
        char fullLine2[8 * MAX_LENGTH + 21];
        strcpy(fullLine2, userName);
        addColumn(fullLine2, entryWidgets->customer->region);
        addColumn(fullLine2, entryWidgets->customer->address);
        addColumn(fullLine2, entryWidgets->customer->legalRepresentative);
        addColumn(fullLine2, entryWidgets->customer->scale);
        addColumn(fullLine2, entryWidgets->customer->businessContactLevel);
        addColumn(fullLine2, email);
        addColumn(fullLine2, phone);

        writeLineToFile("customers.csv", fullLine2);
        // displayCustomer(*(entryWidgets->customer));
        GtkWidget *newdialog2, *newlabel2, *newcontent_area2;
        newdialog2 = gtk_dialog_new_with_buttons("显示客户信息",
                                            NULL,
                                            GTK_DIALOG_MODAL,
                                            "_OK", GTK_RESPONSE_OK,
                                            NULL);
        newcontent_area2 = gtk_dialog_get_content_area(GTK_DIALOG(newdialog2));

        char info1[1024];
        snprintf(info1, sizeof(info1),
                "\n显示客户信息:\n"
                "姓名: %-20.20s\n"
                "区域: %-20.20s\n"
                "地址: %-30.30s\n"
                "法人: %-20.20s\n"
                "规模: %-10.10s\n"
                "业务联系程度: %-15.15s\n"
                "电子邮件: %-25.25s\n"
                "电话: %-15.15s\n",
                userName,
                entryWidgets->customer->region,
                entryWidgets->customer->address,
                entryWidgets->customer->legalRepresentative,
                entryWidgets->customer->scale,
                entryWidgets->customer->businessContactLevel,
                email,
                phone);

        newlabel2 = gtk_label_new(info1);
        gtk_container_add(GTK_CONTAINER(newcontent_area2), newlabel2);

        gtk_widget_show_all(newdialog2);
        gtk_dialog_run(GTK_DIALOG(newdialog2));
        gtk_widget_destroy(newdialog2);
        break;
    case 3:
        strncpy(entryWidgets->contact->name, userName,MAX_LENGTH);
        strncpy(entryWidgets->contact->gender, gender,MAX_LENGTH);
        strncpy(entryWidgets->contact->birthday, birthday,MAX_LENGTH);
        strncpy(entryWidgets->contact->email, email,MAX_LENGTH);
        strncpy(entryWidgets->contact->phone, phone,MAX_LENGTH);
        
        representative_const = convert_to_utf8(gtk_entry_get_text(GTK_ENTRY(entryWidgets->representative_entry)));
        strncpy(entryWidgets->contact->representative,representative_const,MAX_LENGTH);
        entryWidgets->contact->representative[strcspn(entryWidgets->contact->representative, "\n")] = 0;
        if (isEmpty(entryWidgets->contact->representative)) strcpy(entryWidgets->contact->representative, " ");
        
        // saveContactToFile(*(entryWidgets->contact));
        char fullLine3[6 * MAX_LENGTH + 15];
        strcpy(fullLine3, userName);
        addColumn(fullLine3, gender);
        addColumn(fullLine3, birthday);
        addColumn(fullLine3, email);
        addColumn(fullLine3, phone);
        addColumn(fullLine3, entryWidgets->contact->representative);

        writeLineToFile("contacts.csv", fullLine3);

        // displayContact(*(entryWidgets->contact));
        GtkWidget *newdialog3, *newlabel3, *newcontent_area3;
        
        newdialog3 = gtk_dialog_new_with_buttons("显示联络员信息",
                                            NULL,
                                            GTK_DIALOG_MODAL,
                                            "_OK", GTK_RESPONSE_OK,
                                            NULL);
        newcontent_area3 = gtk_dialog_get_content_area(GTK_DIALOG(newdialog3));

        char info2[1024];
        snprintf(info2, sizeof(info2),
                "\n显示联络员信息:\n"
                "姓名: %-20.20s\n"
                "性别: %-10.10s\n"
                "生日: %-15.15s\n"
                "电子邮件: %-25.25s\n"
                "电话: %-15.15s\n"
                "代表公司: %-20.20s\n",
                userName,
                gender,
                birthday,
                email,
                phone,
                entryWidgets->contact->representative);

        newlabel3 = gtk_label_new(info2);
        gtk_container_add(GTK_CONTAINER(newcontent_area3), newlabel3);

        gtk_widget_show_all(newdialog3);
        gtk_dialog_run(GTK_DIALOG(newdialog3));
        gtk_widget_destroy(newdialog3);
        break;
    default:
        return;
    }
    gtk_widget_destroy(entryWidgets->window);
    return;
}

void on_cancel_save_clicked(GtkWidget *widget, EntryWidgets *entryWidgets)
{
    gtk_widget_destroy(entryWidgets->window);
}

// 增加后一列
void addColumn(char *fullLine, const char *newOne) {
    strcat(fullLine, "|||");
    strcat(fullLine, newOne);
}

// 显示一个小菜单
int beforeInfo(head_node *head, const char *prompt) {
    GtkWidget *dialog, *content_area, *combo_box;
    GtkWindow *parent_window = NULL;
    int response_id;
    int result = -1;
    int index;
    if(IsManager) {
        dialog = gtk_dialog_new_with_buttons("选择数据类型",
                                            parent_window,
                                            GTK_DIALOG_MODAL,
                                            "_OK", GTK_RESPONSE_OK,
                                            "_Cancel",GTK_RESPONSE_CANCEL,
                                            NULL);
        content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));

        // 创建下拉框
        combo_box = gtk_combo_box_text_new();
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "客户");
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "联络人");
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo_box), "业务员");
        gtk_combo_box_set_active(GTK_COMBO_BOX(combo_box), 0); // 设置默认选项为第一项
        gtk_container_add(GTK_CONTAINER(content_area), combo_box);

        gtk_widget_show_all(dialog);

        // 运行对话框
        response_id = gtk_dialog_run(GTK_DIALOG(dialog));
        index = gtk_combo_box_get_active(GTK_COMBO_BOX(combo_box));
        gtk_widget_destroy(dialog);
    } else {
        response_id = GTK_RESPONSE_OK;
        index = 0;
    }
    
    if (response_id == GTK_RESPONSE_OK) {
        
        switch (index) {
            case 0:
                if (head->is_cus) {
                    return 0;
                } else {
                    dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_ERROR,
                                                GTK_BUTTONS_OK,
                                                "无法%s客户信息。",prompt);
                    gtk_window_set_title(GTK_WINDOW(dialog), "错误");
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy(dialog);
                    return -1;
                }
                break;
            case 1:
                if (IsManager && head->is_ctp) {
                    return 1;
                } else {
                    dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_ERROR,
                                                GTK_BUTTONS_OK,
                                                "无法%s联络人信息。",prompt);
                    gtk_window_set_title(GTK_WINDOW(dialog), "错误");
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy(dialog);
                    return -1;
                }
                break;
            case 2:
                if (IsManager && head->is_emp) {
                    return 2;
                } else {
                    dialog = gtk_message_dialog_new(NULL,
                                                GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                                GTK_MESSAGE_ERROR,
                                                GTK_BUTTONS_OK,
                                                "无法%s业务员信息。",prompt);
                    gtk_window_set_title(GTK_WINDOW(dialog), "错误");
                    gtk_dialog_run(GTK_DIALOG(dialog));
                    gtk_widget_destroy(dialog);   
                    return -1;
                }
                break;
            default:
                show_info_dialog(NULL,"无效的选择。"); 
                return -1;
        }
    }
}

// 打印客户信息
void printNode_cus(GtkTextBuffer *buffer,node_cus *node) {
    char heading[MAX_LENGTH*9];
    snprintf(heading,sizeof(heading),"%s - %s - %s - %s - %s - %s - %s - %s\n", 
        node->customer.name,
        node->customer.region,
        node->customer.address, 
        node->customer.legalRepresentative,
        node->customer.scale, 
        node->customer.businessContactLevel,
        node->customer.email,
        node->customer.phone);
    gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
}

// 打印联络人信息
void printNode_ctp(GtkTextBuffer *buffer,node_ctp *node) {
    char heading[MAX_LENGTH*7];
    snprintf(heading,sizeof(heading),"%s - %s - %s - %s - %s - %s\n", 
        node->contactPerson.name,
        node->contactPerson.gender,
        node->contactPerson.birthday, 
        node->contactPerson.email,
        node->contactPerson.phone,
        node->contactPerson.representative);
    gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
}

// 打印业务员信息
void printNode_emp(GtkTextBuffer *buffer,node_emp *node) {
    char heading[MAX_LENGTH*7];
    snprintf(heading,sizeof(heading),"%s - %s - %s - %s - %s - %s\n", 
        node->employee.name,
        node->employee.gender,
        node->employee.birthday, 
        node->employee.email,
        node->employee.phone,
        node->employee.representative);
    gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
}

// 打印通信记录信息
void printNode_rec(GtkTextBuffer *buffer,node_rec *node) {
    char heading[MAX_LENGTH*8];
    snprintf(heading,sizeof(heading),"%s - %s - %s - %s - %s - %s - %s\n", 
        node->record.user,
        node->record.companyName,
        node->record.contactName,
        node->record.date, 
        node->record.time,
        node->record.duration,
        node->record.content);
    gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
}

void printHeading(GtkTextBuffer *buffer,int which) {
    const char *heading;
    switch (which) {
    case 0:
        heading = "客户名 - 地区 - 地址 - 法人 - 规模 - 联系等级 - 邮箱 - 电话\n";
        break;
    case 1:
        heading = "联络人名称 - 性别 - 生日 - 邮箱 - 电话 - 代表公司\n";
        break;
    case 2:
        heading = "业务员名称 - 性别 - 生日 - 邮箱 - 电话 - 代表公司\n";
        break;
    case 3:
        heading = "管理用户 - 公司名称 - 联络人 - 日期 - 时间 - 时长 - 通信内容\n";
        break;
    default:
        heading = "无效类型\n";
        break;
    }
    gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
}


// 打印需要的链表内容
void printNodeList(GtkTextBuffer *buffer,head_node *head, int choice) {
    const char *heading;
    if (head == NULL || head->is_empty) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                   GTK_DIALOG_DESTROY_WITH_PARENT,
                                                   GTK_MESSAGE_ERROR,
                                                   GTK_BUTTONS_OK,
                                                   "没有可显示的数据。");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    switch (choice) {
    case 0:  // 客户信息
        if (head->is_cus) {
            node_cus *current = head->next_cus;
            heading = "客户名 - 地区 - 地址 - 法人 - 规模 - 联系等级 - 邮箱 - 电话\n";
            gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
            while (current != NULL) {
                printNode_cus(buffer,current);
                current = current->next;
            }
        } else {
            heading = "没有可显示的客户信息。\n";
        }
        break;
    case 1:  // 联络人信息
        if (head->is_ctp) {
            node_ctp *current = head->next_ctp;
            heading = "联络人名称 - 性别 - 生日 - 邮箱 - 电话 - 代表公司\n";
            gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
            while (current != NULL) {
                printNode_ctp(buffer,current);
                current = current->next;
            }
        } else {
            heading = "没有可显示的联络人信息。\n";
        }
        break;
    case 2:  // 业务员信息
        if (head->is_emp) {
            node_emp *current = head->next_emp;
            heading = "业务员名称 - 性别 - 生日 - 邮箱 - 电话 - 代表公司\n";
            gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
            while (current != NULL) {
                printNode_emp(buffer,current);
                current = current->next;
            }
        } else {
            heading = "没有可显示的业务员信息。\n";
        }
        break;
    case 3:  // 通信记录
        if (head->is_rec) {
            node_rec *current = head->next_rec;
            heading = "管理用户 - 公司名称 - 联络人 - 日期 - 时间 - 时长 - 通信内容\n";
            gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
            while (current != NULL) {
                printNode_rec(buffer,current);
                current = current->next;
            }
        } else {
            heading = "没有可显示的通信记录信息。\n";
        }
        break;
    default:
        heading = "无效的选项。\n";
        break;
    }
    gtk_text_buffer_insert_at_cursor(buffer, heading, -1);
}

int selectSearchAttribute(int which) {
    char index = '0';
    char message[MAX_LENGTH];
    
    switch (which) {
    case 0: // 客户
        snprintf(message,sizeof(message),"请选择属性：(1. 名称 2. 地区 3. 地址 4. 法人 5. 规模 6. 联系等级 7. 邮箱 8. 电话)\n");
        index = '8';
        break;
    case 1: // 联络人
    case 2: // 业务员
        snprintf(message,sizeof(message),"请选择属性：(1. 名称 2. 性别 3. 生日 4. 邮箱 5. 电话 6. 代表公司)\n");
        index = '6';
        break;
    case 3: // 通信记录
        snprintf(message,sizeof(message),"请选择属性：(1. 管理用户 2. 公司名称 3. 联络人 4. 日期 5. 时间 6. 时长 7. 通信内容)\n");
        index = '7';
    default: break;
    }
    char get[MAX_LENGTH];
    int ret = infoInput(get, sizeof(get), message);
    if(!ret) {
        return -2;
    } else if (!isOneChar(get) || get[0] < '1' || get[0] > index) {
        return -1;
    } else {
        return charToInt(get[0]) - 1;
    }
}

char* convert_to_utf8(const char* input) {
    iconv_t cd = iconv_open("UTF-8", "ISO-8859-1"); // 确保编码名称正确
    if (cd == (iconv_t)-1) {
        perror("iconv_open failed");
        return NULL;
    }

    size_t in_len = strlen(input);
    size_t out_len = in_len * 2; // 预估UTF-8的长度最多为原长度的两倍
    char* output = malloc(out_len + 1);
    if (!output) {
        perror("malloc failed");
        iconv_close(cd);
        return NULL;
    }

    char* out_ptr = output;
    char** in_ptr_temp = (char**) &input; // 强制转换以匹配iconv的期望类型

    size_t result = iconv(cd, in_ptr_temp, &in_len, &out_ptr, &out_len);
    if (result == (size_t)-1) {
        perror("iconv failed");
        free(output);
        iconv_close(cd);
        return NULL;
    }

    *out_ptr = '\0';
    iconv_close(cd);
    return output;
}