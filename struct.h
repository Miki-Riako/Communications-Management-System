#include <stdio.h>

// 定义数组的最大尺寸
#define MAX_PHONE_NUMBERS 10 // 最多电话数量
#define MAX_GROUPS 10        // 最多分组数量
#define MAX_NAME_LENGTH 100  // 名称的最大长度
#define MAX_ADDRESS_LENGTH 200 // 地址的最大长度
#define MAX_EMAIL_LENGTH 100   // 邮箱的最大长度
#define MAX_COMMUNICATION_RECORDS 100 // 通信记录的最大数量

// 定义客户规模的枚举类型
typedef enum { SMALL, MEDIUM, LARGE } CustomerSize;

// 定义业务联系程度的枚举类型
typedef enum { LOW, MEDIUM, HIGH } ContactDegree;

// 定义客户所在区域的枚举类型
typedef enum { NORTHEAST, NORTH, EAST, SOUTH, CENTRAL, NORTHWEST, SOUTHWEST } Region;

// 日期时间结构体
typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
} DateTime;

// 电话号码结构体
typedef struct {
    char phoneNumbers[MAX_PHONE_NUMBERS][MAX_NAME_LENGTH]; // 电话号码数组
    int phoneNumberCount; // 电话号码数量
} PhoneNumbers;

// 分组成员结构体
typedef struct {
    char groups[MAX_GROUPS][MAX_NAME_LENGTH]; // 分组数组
    int groupCount; // 分组数量
} GroupMemberships;

// 客户结构体
typedef struct {
    char name[MAX_NAME_LENGTH]; // 客户名称
    Region region; // 客户所在区域，使用枚举类型
    char address[MAX_ADDRESS_LENGTH]; // 客户地址
    char legalRepresentative[MAX_NAME_LENGTH]; // 客户公司法人
    CustomerSize size; // 客户规模
    ContactDegree contactDegree; // 与本公司业务联系程度
    char email[MAX_EMAIL_LENGTH]; // 客户公司邮箱
    PhoneNumbers phoneNumbers; // 客户电话号码
    GroupMemberships memberships; // 客户分组信息
} Customer;

// 联络员结构体
typedef struct {
    char name[MAX_NAME_LENGTH]; // 姓名
    char gender; // 性别
    DateTime birthdate; // 生日
    char email[MAX_EMAIL_LENGTH]; // 电子邮箱
    PhoneNumbers phoneNumbers; // 电话号码
} ContactPerson;

// 业务员结构体
typedef struct {
    char name[MAX_NAME_LENGTH]; // 姓名
    char gender; // 性别
    DateTime birthdate; // 生日
    char email[MAX_EMAIL_LENGTH]; // 电子邮箱
    PhoneNumbers phoneNumbers; // 电话号码
} Salesperson;

// 通信记录结构体
typedef struct {
    char customerName[MAX_NAME_LENGTH]; // 客户公司名称
    char contactPersonName[MAX_NAME_LENGTH]; // 客户联络员名称
    DateTime communicationTime; // 通信时间
    int durationMinutes; // 通信时长（分钟）
    char content[MAX_NAME_LENGTH]; // 通信内容（文字记录，假设记录较短，如果记录较长可以使用动态内存或更大的数组）
} CommunicationRecord;

// 通信管理系统结构体，用来存储所有记录
typedef struct {
    CommunicationRecord records[MAX_COMMUNICATION_RECORDS]; // 通信记录数组
    int recordCount; // 通信记录数量
} CommunicationManagementSystem;

// 根据需要添加额外的结构或定义
