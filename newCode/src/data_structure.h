// data_structure.h
#ifndef DATA_STRUCTRUE_H
#define DATA_STRUCTRUE_H
#include "header.h"

#define MAX_LENGTH 255
typedef struct {
    char name[MAX_LENGTH];                    // 客户名称
    char region[MAX_LENGTH];                  // 客户所在区域
    char address[MAX_LENGTH];                 // 客户地址
    char legalRepresentative[MAX_LENGTH];     // 客户公司法人
    char scale[MAX_LENGTH];                   // 客户规模
    char businessContactLevel[MAX_LENGTH];    // 与本公司业务联系程度
    char email[MAX_LENGTH];                   // 客户公司邮箱
    char phone[MAX_LENGTH];                   // 客户公司联络电话
} Customer;
typedef struct {
    char name[MAX_LENGTH];                    // 联络员名称
    char gender[MAX_LENGTH];                  // 联络员性别
    char birthday[MAX_LENGTH];                // 联络员生日
    char email[MAX_LENGTH];                   // 联络员邮箱
    char phone[MAX_LENGTH];                   // 联络员联络电话
    char representative[MAX_LENGTH];          // 联络员代表的公司
} ContactPerson;
typedef struct {
    char name[MAX_LENGTH];                    // 业务员名称
    char gender[MAX_LENGTH];                  // 业务员性别
    char birthday[MAX_LENGTH];                // 业务员生日
    char email[MAX_LENGTH];                   // 业务员邮箱
    char phone[MAX_LENGTH];                   // 业务员联络电话
    char representative[MAX_LENGTH];          // 业务员联络员公司
} Employee;
typedef struct {
    char user[MAX_LENGTH];                    // 用户
    char companyName[MAX_LENGTH];             // 客户公司名称
    char contactName[MAX_LENGTH];             // 客户联络员名称
    char date[MAX_LENGTH];                    // 日期 YYYY-MM-DD
    char time[MAX_LENGTH];                    // 时间 HH:MM:SS
    char duration[MAX_LENGTH];                // 通信时长（分钟）
    char content[MAX_LENGTH];                 // 通信内容
} Record;

typedef struct {
    GtkWidget *parentWindow;
    GtkWidget *currentWindow;
} WidgetPair;

typedef struct {
    GtkWindow *parent_window;
    const gchar *message;
} DialogData;


// login
typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *loginManager_btn;
    GtkWidget *loginEmployee_btn;
    GtkWidget *register_btn;
    GtkWidget *quit_btn;
} StartWidgets;
StartWidgets startWidgets;

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *password_entry;
    GtkWidget *confirmLoginManager_btn;
    GtkWidget *backToStart_btn;
    int chance;
} LoginManagerWidgets;
LoginManagerWidgets loginManagerWidgets;

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *username_label;
    GtkWidget *username_entry;
    GtkWidget *password_label;
    GtkWidget *password_entry;
    GtkWidget *confirmLoginManager_btn;
    GtkWidget *backToStart_btn;
}LoginEmployeeWidgets;
LoginEmployeeWidgets loginEmployeeWidgets;

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *username_label;
    GtkWidget *username_entry;
    GtkWidget *password_label;
    GtkWidget *password_entry;
    GtkWidget *confirmRegister_btn;
    GtkWidget *backToStart_btn;
}RegisterWidgets;
RegisterWidgets registerWidgets;

// menu
typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *infoManage_btn;
    GtkWidget *customerAssign_btn;
    GtkWidget *groupManage_btn;
    GtkWidget *infoInquiry_btn;
    GtkWidget *sortedInfoDisplay_btn;
    GtkWidget *infoStatistic_btn;
    GtkWidget *analysisRecord_btn;
    GtkWidget *systemSetting_btn;
    GtkWidget *exit_btn;
} ManagerMenuWidgets;
ManagerMenuWidgets managerMenuWidgets;

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *infoEnquiry_btn;
    GtkWidget *infoSort_btn;
    GtkWidget *recordsManage_btn;
    GtkWidget *systemSetting_btn;
    GtkWidget *exit_btn;
} EmployeeMenuWidgets;
EmployeeMenuWidgets employeeMenuWidgets;

// customer_assign
typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *addAssignment_btn;
    GtkWidget *changeAssignment_btn;
    GtkWidget *removeAssignment_btn;
    GtkWidget *displayAssignment_btn;
    GtkWidget *backToManagerMenu_btn;
} CustomerAssignWidgets;
CustomerAssignWidgets customerAssignWidgets;

// group_manage
typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *addGroup_btn;
    GtkWidget *changeGroup_btn;
    GtkWidget *removeGroup_btn;
    GtkWidget *showGroups_btn;
    GtkWidget *divideCustomer_btn;
    GtkWidget *adjustCustomer_btn;
    GtkWidget *backTo_btn;
    GtkWidget *changeContact_btn;
    GtkWidget *removeContactRecord_btn;
    GtkWidget *backToManageMenu_btn;
} GroupManageWidgets;
GroupManageWidgets groupManageWidgets;

// info_enquiry
typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *simpleQuery_btn;
    GtkWidget *combinedQuery_btn;
    GtkWidget *fuzzyQuery_btn;
    GtkWidget *back_btn;
} InfoEnquiryWidgets;
InfoEnquiryWidgets infoEnquiryWidgets;

// info_manage
typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *addEmployee_btn;
    GtkWidget *changeEmployee_btn;
    GtkWidget *removeEmployeeRecord_btn;
    GtkWidget *addCustomer_btn;
    GtkWidget *changeCustomer_btn;
    GtkWidget *removeCustomerRecord_btn;
    GtkWidget *addContact_btn;
    GtkWidget *changeContact_btn;
    GtkWidget *removeContactRecord_btn;
    GtkWidget *back_btn;
} InfoManageWidgets;
InfoManageWidgets infoManageWidgets;

// info_sort
typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *defaultSort_btn;
    GtkWidget *simpleSort_btn;
    GtkWidget *combinedSort_btn;
    GtkWidget *recordSort_btn;
    GtkWidget *back_btn;
} InfoSortWidgets;
InfoSortWidgets infoSortWidgets;

// record_manage
typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *addRecord_btn;
    GtkWidget *changeRecord_btn;
    GtkWidget *showRecord_btn;
    GtkWidget *back_btn;
} RecordsManageWidgets;
RecordsManageWidgets recordsManageWidgets;


// system_setting
typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *changePassword_btn;
    GtkWidget *resetPassword_btn;
    GtkWidget *backupData_btn;
    GtkWidget *restoreData_btn;
    GtkWidget *backToManageMenu_btn;
} SystemSettingWidgets;
SystemSettingWidgets systemSettingWidgets;



typedef struct node_cus{
    Customer customer;
    struct node_cus *next;
} node_cus;
typedef struct node_ctp{
    ContactPerson contactPerson;
    struct node_ctp *next;
} node_ctp;
typedef struct node_emp{
    Employee employee;
    struct node_emp *next;
} node_emp;
typedef struct node_rec{
    Record record;
    struct node_rec *next;
} node_rec;

typedef struct head_node{ // 头结点
    bool is_empty;
    bool is_cus;
    bool is_ctp;
    bool is_emp;
    bool is_rec;
    node_cus *next_cus;
    node_ctp *next_ctp;
    node_emp *next_emp;
    node_rec *next_rec;
} head_node;

extern char User[];
extern bool IsManager;

#endif
// end data_structure.h