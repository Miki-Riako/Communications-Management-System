// header.h
#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <regex.h>

#define SECRET_KEY "secret_key_secret_key_secret_key_secret_key_secret_key"
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
    char representative[MAX_LENGTH];          // 联络员代表业务员
} ContactPerson;
typedef struct {
    char name[MAX_LENGTH];                    // 业务员名称
    char gender[MAX_LENGTH];                  // 业务员性别
    char birthday[MAX_LENGTH];                // 业务员生日
    char email[MAX_LENGTH];                   // 业务员邮箱
    char phone[MAX_LENGTH];                   // 业务员联络电话
    char representative[MAX_LENGTH];          // 业务员代表联络员
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

#include "support.h"
#endif
