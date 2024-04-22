// header.h
#ifndef MY_HEADER_H
#define MY_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <regex.h>
#include <gtk/gtk.h>
#include "data_structure.h"

#define DEBUG_MODE true
#define SECRET_KEY "AAAAA-AAAAA-AAAAA-AAAAA-AAAAA"

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

// Algorithem
int mapScaleToPriority(const char *scale);
int mapContactLevelToPriority(const char *level);
bool compareNodeCus(node_cus *a, node_cus *b, int attrIndex, bool ascending);
bool compareNodeCtp(node_ctp *a, node_ctp *b, int attrIndex, bool ascending);
bool compareNodeEmp(node_emp *a, node_emp *b, int attrIndex, bool ascending);
bool compareNodeRec(node_rec *a, node_rec *b, int attrIndex, bool ascending);
void sort(int which, head_node *head, int attrIndex, bool ascending);
void beforeSort(head_node *head, int which, int *attributeIndex, bool *isAscending);
void combinedSortHelper(head_node *head, int which);
void countCombinedAttributes(head_node *head, int *attrIndexes, int numAttrs, int which);
char* getCustomerAttribute(Customer *customer, int attrIndex);
char* getContactPersonAttribute(ContactPerson *contact, int attrIndex);
char* getEmployeeAttribute(Employee *employee, int attrIndex);
char* getRecordAttribute(Record *record, int attrIndex);
bool performQueryIteration(head_node *head, head_node **headA, head_node **headB, int which, bool *first);

// BasicIO
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

// Memory
void initializeHeadNode(head_node *head);
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
void freeAll(GtkWidget *widget,head_node *head);
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
bool getInput(char *input, int buffer_size);
void stripNewline(char *str);
char *splitLine(char *input, const char *delim, int num);
bool isSameString(const char *str1, const char *str2);
void cleanField(char *field);
bool infoInput(char *input, int buffer_size, const char *prompt);
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




// String
static void on_save_entry_clicked(GtkWidget *widget, EntryWidgets *entryWidgets);
static void on_cancel_save_clicked(GtkWidget *widget, EntryWidgets *entryWidgets);


// all widget
void on_back_clicked(GtkWidget *widget, WidgetPair *pair);

void show_info_dialog(GtkWidget *widget, const gchar *message);


// login
void startWidget();
void loginManagerWidget();
void loginEmployeeWidget();
void registerWidget();
bool verify(const char *username, const char *password);
static void on_loginManager_clicked(GtkWidget *widget, gpointer data);
static void on_loginEmployee_clicked(GtkWidget *widget, gpointer data);
static void on_register_clicked(GtkWidget *widget, gpointer data);
static void on_quit_clicked(GtkWidget *widget, gpointer data);
static void on_confirm_loginManager_clicked(GtkWidget *widget, gpointer data);
static void on_backtoStart_clicked(GtkWidget *widget, gpointer data);
static void on_confirm_loginEmployee_clicked(GtkWidget *widget, gpointer data);
static void on_confirm_Register_clicked(GtkWidget *widget, gpointer data);

// menu
void managerMenuWidget();
void employeeMenuWidget();
void exitSystem();
void on_infoManager_clicked(GtkWidget *widget, gpointer data);
void on_customerAssign_clicked(GtkWidget *widget, gpointer data);
void on_groupManage_clicked(GtkWidget *widget, gpointer data);
void on_infoEnquiry_clicked(GtkWidget *widget, gpointer data);
void on_infoSort_clicked(GtkWidget *widget, gpointer data);
void on_infoStatistic_clicked(GtkWidget *widget, gpointer data);
void on_analysisRecord_clicked(GtkWidget *widget, gpointer data);
void on_systemSetting_clicked(GtkWidget *widget, gpointer data);
void on_exit_clicked(GtkWidget *widget, gpointer data);

void on_recordManage_clicked(GtkWidget *widget, gpointer data);



// customer_assign
void customerAssignWidget(GtkWidget *parent);
void addAssignment();
void changeAssignment();
void removeAssignment();
void displayAssignment();

static void on_addAssignment_clicked(GtkWidget *widget, gpointer data);
static void on_changeAssignment_clicked(GtkWidget *widget, gpointer data);
static void on_removeAssignment_clicked(GtkWidget *widget, gpointer data);
static void on_displayAssignment_clicked(GtkWidget *widget, gpointer data);

// group_manage
void groupManageWidget(GtkWidget *parent);
void createDirectory(const char *path);
void createGroup(const char *groupName);
void regionGroup(const char *groupName);
void scaleGroup(const char *groupName);
void contactGroup(const char *groupName);
void addGroup();
void changeGroup();
void removeGroup();
void showGroups();
void divideCustomer();
void adjustCustomer();

static void on_addGroup_clicked(GtkWidget *widget, gpointer data);
static void on_changeGroup_clicked(GtkWidget *widget, gpointer data);
static void on_removeGroup_clicked(GtkWidget *widget, gpointer data);
static void on_showGroups_clicked(GtkWidget *widget, gpointer data);
static void on_divideCustomer_clicked(GtkWidget *widget, gpointer data);
static void on_adjustCustomer_clicked(GtkWidget *widget, gpointer data);

// info_enquiry
void infoEnquiryWidget(GtkWidget *parent);
bool searchOnes(head_node *head, head_node *copyList, char *query, int attrIndex, int which, int how);
bool howToSearch(const char *toCompare, const char *query, int how);
void simpleQuery(head_node *head);
void combinedQuery(head_node *head);
void fuzzyQuery(head_node *head);

// info_manage
void infoManageWidget(GtkWidget *parent);
void addEmployee();
void addCustomer();
void addContact();
void changeEmployee();
void changeCustomer();
void changeContact();
void saveEmployeeToFile(Employee employee);
void saveCustomerToFile(Customer customer);
void saveContactToFile(ContactPerson contact);
void displayEmployee(Employee employee);
void displayCustomer(Customer customer);
void displayContact(ContactPerson contact);

static void on_addEmployee_clicked(GtkWidget *widget, gpointer data);
static void on_changeEmployee_clicked(GtkWidget *widget, gpointer data);
static void on_removeEmployeeRecord_clicked(GtkWidget *widget, gpointer data);
static void on_addCustomer_clicked(GtkWidget *widget, gpointer data);
static void on_changeCustomer_clicked(GtkWidget *widget, gpointer data);
static void on_removeCustomerRecord_clicked(GtkWidget *widget, gpointer data);
static void on_addContact_clicked(GtkWidget *widget, gpointer data);
static void on_changeContact_clicked(GtkWidget *widget, gpointer data);
static void on_removeContactRecord_clicked(GtkWidget *widget, gpointer data);

// info_enquiry
void infoEnquiryWidget(GtkWidget *parent);
int selectSearchAttribute(int which);
void simpleQuery(head_node *head);
void combinedQuery(head_node *head);
void fuzzyQuery(head_node *head);

static void on_simpleQuery_clicked(GtkWidget *widget, gpointer data);
static void on_combinedQuery_clicked(GtkWidget *widget, gpointer data);
static void on_fuzzyQuery_clicked(GtkWidget *widget, gpointer data);

// info_sort
void infoSortWidget(GtkWidget *parent);
void defaultSort(head_node *head);

void on_defaultSort_clicked(GtkWidget *widget, gpointer data);
void on_simpleSort_clicked(GtkWidget *widget, gpointer data);
void on_combinedSort_clicked(GtkWidget *widget, gpointer data);
static void on_infoSortBack_clicked(GtkWidget *widget, gpointer data);

// info_statistics
void infoStatisticsWidget(GtkWidget *parent);
void simpleStatistics(head_node *head);
void combinedStatistics(head_node *head);
void presetStatistics(head_node *head);
void conditionalStatistics(head_node *head);
void countAttributesByConditions(head_node *head, int *attrIndexes, char conditionValues[][MAX_LENGTH], int numConditions, int which);
void countAttributes(head_node *head, int attrIndex, int which);

void on_simpleStatistics_clicked(GtkWidget *widget, gpointer data);
void on_combinedStatistics_clicked(GtkWidget *widget, gpointer data);
void on_presetStatistics_clicked(GtkWidget *widget, gpointer data);
void on_conditionalStatistics_clicked(GtkWidget *widget, gpointer data);
static void on_infoStatisticsBack_clicked(GtkWidget *widget, gpointer data);

// record_analysis
void recordsAnalysisWidget(GtkWidget *parent);
void enquiryRecords(head_node *head);
void sortRecords(head_node *head);
void statisticsRecords(head_node *head);

void on_enquiryRecords_clicked(GtkWidget *widget, gpointer data);
void on_sortRecords_clicked(GtkWidget *widget, gpointer data);
void on_statisticsRecords_clicked(GtkWidget *widget, gpointer data);
static void on_recordAnalysisBack_clicked(GtkWidget *widget, gpointer data);

// record_manage
void recordsManageWidget(GtkWidget *parent);
void addRecord();
void changeRecord();
void showRecord();
void displayRecord(Record record);

void on_addRecord_clicked(GtkWidget *widget, gpointer data);
void on_changeRecord_clicked(GtkWidget *widget, gpointer data);
void on_showRecord_clicked(GtkWidget *widget, gpointer data);

// system_setting
void systemSettingWidget(GtkWidget *parent);
bool changeUserPassword(const char *username, const char *newEncryptedPassword);
void changePassword();
void resetPassword();
void backupData();
void restoreData();

static void on_changePassword_clicked(GtkWidget *widget, gpointer data);
static void on_resetPassword_clicked(GtkWidget *widget, gpointer data);
static void on_backupData_clicked(GtkWidget *widget, gpointer data);
static void on_restoreData_clicked(GtkWidget *widget, gpointer data);

#endif
