// header.h
#ifndef MY_HEADER_H
#define MY_HEADER_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <regex.h>

#define MAIL_REGEX "/^[A-Za-z\d]+([-_.][A-Za-z\d]+)*@([A-Za-z\d]+[-.]){1,2}[A-Za-z\d]{2,5}$/g"
#define SYSTEM_CLEAR "clear"
// if in windows, change the clear to cls

#define MAX_LENGTH 255

typedef char string[MAX_LENGTH];
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
    char companyName[MAX_LENGTH];
    char contactName[MAX_LENGTH];
    char date[MAX_LENGTH];
    char duration[MAX_LENGTH];
    char content[MAX_LENGTH];
} CommunicationRecord;

#endif
