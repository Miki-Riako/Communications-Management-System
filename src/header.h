// header.h
#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <regex.h>
#include <termios.h>
#include <unistd.h>

#define DEBUG_MODE true
#define SECRET_KEY "AAAAA-AAAAA-AAAAA-AAAAA-AAAAA"
#define MAX_LENGTH 255

#ifdef _WIN32
    // In windows
    #include <direct.h>
    #include <io.h>
    #define SYSTEM_CLEAR "cls"
    #define ACCESS _access
    #define F_OK 0
    #define CREATE_DIRECTORY(path) (_mkdir(path))
    
#else
    // In Unix
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <unistd.h>
    #define SYSTEM_CLEAR "clear"
    #define ACCESS access
    #define CREATE_DIRECTORY(path) (mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
#endif

#include "data_structure.h"

bool howToSearch(const char *toCompare, const char *query, int how);
bool searchOnes(head_node *head, head_node *copyList, char *query, int attrIndex, int which, int how);
bool performQueryIteration(head_node *head, head_node **headA, head_node **headB, int which, bool *first);
int mapScaleToPriority(const char *scale);
int mapContactLevelToPriority(const char *level);
bool compareNodeCus(node_cus *a, node_cus *b, int attrIndex, bool ascending);
bool compareNodeCtp(node_ctp *a, node_ctp *b, int attrIndex, bool ascending);
bool compareNodeEmp(node_emp *a, node_emp *b, int attrIndex, bool ascending);
bool compareNodeRec(node_rec *a, node_rec *b, int attrIndex, bool ascending);
void sort(int which, head_node *head, int attrIndex, bool ascending);
void beforeSort(head_node *head, int which, int *attributeIndex, bool *isAscending);
void combinedSortHelper(head_node *head, int which);
void countAttributes(head_node *head, int attrIndex, int which);
void countCombinedAttributes(head_node *head, int *attrIndexes, int numAttrs, int which);
void countAttributesByConditions(head_node *head, int *attrIndexes, char conditionValues[][MAX_LENGTH], int numConditions, int which);
char* getCustomerAttribute(Customer *customer, int attrIndex);
char* getContactPersonAttribute(ContactPerson *contact, int attrIndex);
char* getEmployeeAttribute(Employee *employee, int attrIndex);
char* getRecordAttribute(Record *record, int attrIndex);

bool alreadyExists(const char *filename, const char *username);
bool lineExists(const char *filename, const char *lineToCheck);
void initializeInfoFile(const char *path, const char *header);
bool removeEntry(const char *filename, const char *delName);
void removeRecord(const char *filename, const char *prompt);
void writeLineToFile(const char *filename, const char *data);
bool removeLineInFile(const char *filename, const char *data);
void copyLine(const char *sourceFilename, const char *destinationFilename, const char *columnName, const char *targetValue);
bool copyFile(const char *sourcePath, const char *destinationPath);
void loadFile(head_node *head);
void loadFile_record(head_node *head);
void loadCustomerData(const char *filename, const char *customerName, head_node *head);
void loadCustomers(const char *filename, head_node *head);
void loadContactPersons(const char *filename, head_node *head);
void loadEmployees(const char *filename, head_node *head);
void initializeAll();

void loadRecords(const char *filename, head_node *head);
void appendNode_cus(head_node *head, Customer customer);
void appendNode_ctp(head_node *head, ContactPerson contact);
void appendNode_emp(head_node *head, Employee employee);
void appendNode_rec(head_node *head, Record record);
void linkNode_cus(head_node *head, node_cus *newNode);
void linkNode_ctp(head_node *head, node_ctp *newNode);
void linkNode_emp(head_node *head, node_emp *newNode);
void linkNode_rec(head_node *head, node_rec *newNode);
node_cus *copyNode_cus(node_cus *original);
node_ctp *copyNode_ctp(node_ctp *original);
node_emp *copyNode_emp(node_emp *original);
node_rec *copyNode_rec(node_rec *original);
void freeNodeList_cus(node_cus *node);
void freeNodeList_ctp(node_ctp *node);
void freeNodeList_emp(node_emp *node);
void freeNodeList_rec(node_rec *node);
void freeAll(head_node *head);
void swapLists(head_node **headA, head_node **headB);
void clearList(head_node *head);

void xorEncryptDecrypt(const char *input, size_t length, char *output);
bool verify(const char *username, const char *password);
bool matchRegex(const char *password);
bool matchMail(const char *email);
bool matchPhone(const char *phone);
bool matchGender(const char *gender);
bool matchScale(const char *scale);
bool matchContactLevel(const char *contactLevel);
bool matchDate(const char *date);
bool matchTime(const char *time);
bool matchDuration(const char *duration);

bool isEmpty(const char *input);
bool isOneChar(const char *input);
void clearBuffer();
int charToInt(char c);
void getInput(char *input, int buffer_size);
void stripNewline(char *str);
char *splitLine(char *input, const char *delim, int num);
bool isSameString(const char *str1, const char *str2);
void cleanField(char *field);
void infoInput(char *input, int buffer_size, const char *prompt);
void inputTheName(char *name, int buffer_size, const char *prompt);
void addEntry(int section, const char *filename, const char *prompt, Employee *employee, Customer *customer, ContactPerson *contact);
void addColumn(char *fullLine, const char *newOne);
void printHeading(int which);
void printNode_cus(node_cus *node);
void printNode_ctp(node_ctp *node);
void printNode_emp(node_emp *node);
void printNode_rec(node_rec *node);
void printNodeList(head_node *node, int choice);
int beforeInfo(head_node *head, const char *prompt);
int selectSearchAttribute(int which);

#include "libs/Algorithms.h"
#include "libs/BasciIO.h"
#include "libs/Memory.h"
#include "libs/Regex.h"
#include "libs/String.h"

#endif
