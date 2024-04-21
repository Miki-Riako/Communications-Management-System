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
void freeNodeList_cus(node_cus *node);
void freeNodeList_ctp(node_ctp *node);
void freeNodeList_emp(node_emp *node);
void freeNodeList_rec(node_rec *node);
void freeAll(head_node *head);

void xorEncryptDecrypt(const char *input, size_t length, char *output);
bool verify(const char *username, const char *password);
bool matchRegex(const char *password);
bool matchMail(const char *email);
bool matchPhone(const char *phone);
bool matchScale(const char *scale);
bool matchContactLevel(const char *contactLevel);
bool matchDate(const char *date);
bool matchTime(const char *time);
bool matchDuration(const char *duration);

bool isEmpty(const char *input);
bool isOneChar(const char *input);
void clearBuffer();
void getInput(char *input, int buffer_size);
char *splitLine(char *input, const char *delim, int num);
bool isSameString(const char *str1, const char *str2);
void cleanField(char *field);
void infoInput(char *input, int buffer_size, const char *prompt);
void inputTheName(char *name, int buffer_size, const char *prompt);
void addEntry(int section, const char *filename, const char *prompt, Employee *employee, Customer *customer, ContactPerson *contact);
void addColumn(char *fullLine, const char *newOne);
void printNode_cus(node_cus *node);
void printNode_ctp(node_ctp *node);
void printNode_emp(node_emp *node);
void printNode_rec(node_rec *node);
void printNodeList(head_node *node, int choice);
int beforeInfo(head_node *head, const char *prompt);

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
void customerAssignWidget();
void addAssignment();
void changeAssignment();
void removeAssignment();
void displayAssignment();

static void on_addAssignment_clicked(GtkWidget *widget, gpointer data);
static void on_changeAssignment_clicked(GtkWidget *widget, gpointer data);
static void on_removeAssignment_clicked(GtkWidget *widget, gpointer data);
static void on_displayAssignment_clicked(GtkWidget *widget, gpointer data);
void on_backToManagerMenu_clicked(GtkWidget *widget, gpointer data);

// group_manage
void groupManageWidget();
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


// info_manage
void infoManageWidget();
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
void infoEnquiryWidget();
int selectSearchAttribute(int which);
void simpleQuery(head_node *head);
void combinedQuery(head_node *head);
void fuzzyQuery(head_node *head);

static void on_simpleQuery_clicked(GtkWidget *widget, gpointer data);
static void on_combinedQuery_clicked(GtkWidget *widget, gpointer data);
static void on_fuzzyQuery_clicked(GtkWidget *widget, gpointer data);

// info_sort
void infoSortWidget();
void defaultSort(head_node *head);

// record_manage
void recordsManageWidget();
void addRecord();
void changeRecord();
void showRecord();
void displayRecord(Record record);

// system_setting
void systemSettingWidget();
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
