#ifndef MANAGER_H
#define MANAGER_H
// manager.h
#include "struct.h" // 包含之前定义的结构体

// 经理添加客户信息
void AddCustomer(CommunicationManagementSystem *system, Customer customer);

// 经理更新客户信息
void UpdateCustomer(CommunicationManagementSystem *system, Customer customer);

// 经理删除客户信息
void DeleteCustomer(CommunicationManagementSystem *system, char *customerName);

// 经理查看客户信息
Customer* GetCustomer(CommunicationManagementSystem *system, char *customerName);

// 经理添加联络员信息
void AddContactPerson(CommunicationManagementSystem *system, ContactPerson contact);

// 经理更新联络员信息
void UpdateContactPerson(CommunicationManagementSystem *system, ContactPerson contact);

// 经理删除联络员信息
void DeleteContactPerson(CommunicationManagementSystem *system, char *contactName);

// 经理查看联络员信息
ContactPerson* GetContactPerson(CommunicationManagementSystem *system, char *contactName);

// 经理添加业务员信息
void AddSalesperson(CommunicationManagementSystem *system, Salesperson salesperson);

// 经理更新业务员信息
void UpdateSalesperson(CommunicationManagementSystem *system, Salesperson salesperson);

// 经理删除业务员信息
void DeleteSalesperson(CommunicationManagementSystem *system, char *salespersonName);

// 经理查看业务员信息
Salesperson* GetSalesperson(CommunicationManagementSystem *system, char *salespersonName);

// 经理查看通信记录
CommunicationRecord* GetCommunicationRecords(CommunicationManagementSystem *system, char *customerName);

// 经理分析通信记录的内容，可能会涉及到统计分析等功能
void AnalyzeCommunicationRecords(CommunicationManagementSystem *system);

// 这里可以根据实际需求继续添加其他的函数声明





#endif