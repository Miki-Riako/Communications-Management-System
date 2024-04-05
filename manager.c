// manager.c
#include "manager.h"
#include <stdio.h>
#include <string.h>

void AddCustomer(CommunicationManagementSystem *system, Customer customer) {
    // 确保还有空间添加新客户
    if (system->customerCount < MAX_CUSTOMERS) {
        // 添加新客户到数组中
        system->customers[system->customerCount] = customer;
        system->customerCount++;
        printf("客户 '%s' 已添加。\n", customer.name);
    } else {
        printf("错误：客户列表已满。\n");
    }
}

void UpdateCustomer(CommunicationManagementSystem *system, Customer customer) {
    // 查找并更新客户信息
    for (int i = 0; i < system->customerCount; i++) {
        if (strcmp(system->customers[i].name, customer.name) == 0) {
            system->customers[i] = customer;
            printf("客户 '%s' 的信息已更新。\n", customer.name);
            return;
        }
    }
    printf("错误：未找到客户 '%s'。\n", customer.name);
}

void DeleteCustomer(CommunicationManagementSystem *system, const char *customerName) {
    // 查找并删除指定客户
    for (int i = 0; i < system->customerCount; i++) {
        if (strcmp(system->customers[i].name, customerName) == 0) {
            // 移动数组中的元素以覆盖被删除的客户
            for (int j = i; j < system->customerCount - 1; j++) {
                system->customers[j] = system->customers[j + 1];
            }
            system->customerCount--;
            printf("客户 '%s' 已删除。\n", customerName);
            return;
        }
    }
    printf("错误：未找到客户 '%s'。\n", customerName);
}

Customer* GetCustomer(CommunicationManagementSystem *system, const char *customerName) {
    // 查找指定的客户
    for (int i = 0; i < system->customerCount; i++) {
        if (strcmp(system->customers[i].name, customerName) == 0) {
            return &system->customers[i];
        }
    }
    printf("错误：未找到客户 '%s'。\n", customerName);
    return NULL;
}

// ... 其他函数实现 ...

// 需要注意的是，具体的函数实现会依赖于CommunicationManagementSystem的定义，
// 这些代码假设CommunicationManagementSystem结构体包含一个能够存储Customer结构体数组的成员，
// 以及一个用于追踪已存储客户数量的计数器。
