// header.h
#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <regex.h>

#define DEBUG_MODE true
#define SECRET_KEY "AAAAA-AAAAA-AAAAA-AAAAA-AAAAA"
#define SYSTEM_CLEAR "clear" // if in windows, change the clear to cls

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
    char companyName[MAX_LENGTH];             // 客户公司名称
    char contactName[MAX_LENGTH];             // 客户联络员名称
    char date[MAX_LENGTH];                    // 日期 YYYY-MM-DD
    char time[MAX_LENGTH];                    // 时间 HH:MM:SS
    char duration[MAX_LENGTH];                // 通信时长（分钟）
    char content[MAX_LENGTH];                 // 通信内容
} CommunicationRecord;

char User[MAX_LENGTH];
bool IsManager = false;

bool alreadyExists(const char *filename, const char *username);
bool lineExists(const char *filename, const char *lineToCheck);
void initializeInfoFile(const char *path, const char *header);
bool removeEntry(const char *filename, const char *delName);
void removeRecord(const char *filename, const char *prompt);
void writeLineToFile(const char *filename, const char *data);
void xorEncryptDecrypt(const char *input, size_t length, char *output);
bool matchRegex(const char *password);
bool matchMail(const char *email);
bool matchPhone(const char *phone);
bool isEmpty(const char *input);
bool isOneChar(const char *input);
void clearBuffer();
void getInput(char *input, int buffer_size);
bool isSameString(const char *str1, const char *str2);
void infoInput(char *input, int buffer_size, const char *prompt);
void inputTheName(char *name, int buffer_size, const char *prompt);
void addEntry(int section, const char *filename, const char *prompt, Employee *employee, Customer *customer, ContactPerson *contact);
void addColumn(char *fullLine, const char *newOne);

#include "libs/String.c"
#include "libs/BasciIO.c"
#include "libs/Regex.c"

#endif
