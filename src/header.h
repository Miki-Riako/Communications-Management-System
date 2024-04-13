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
    char name[MAX_LENGTH];
    char address[MAX_LENGTH];
    char email[MAX_LENGTH];
    char phone[MAX_LENGTH];
} Customer;
typedef struct {
    char companyName[MAX_LENGTH];
    char contactName[MAX_LENGTH];
    char date[MAX_LENGTH];
    char duration[MAX_LENGTH];
    char content[MAX_LENGTH];
} CommunicationRecord;

#endif
