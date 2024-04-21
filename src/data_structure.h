// data_structure.h
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



typedef struct { // 键值对
    char value[MAX_LENGTH];
    int count;
} AttributeCount;



char User[MAX_LENGTH];
bool IsManager = false;

// end data_structure.h