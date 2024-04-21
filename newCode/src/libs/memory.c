#include "../header.h"

// 创建一个新结点
void appendNode_cus(head_node *head, Customer customer) {
    node_cus *newNode = (node_cus *)malloc(sizeof(node_cus));
    if (newNode) {
        newNode->customer = customer;
        newNode->next = NULL;

        if (head->next_cus == NULL) {
            head->next_cus = newNode;
            head->is_cus = true;
            head->is_empty = false;
        } else {
            node_cus *current = head->next_cus;
            while (current->next != NULL) {  // 遍历到列表末尾
                current = current->next;
            }
            current->next = newNode;  // 在末尾添加新节点
        }
    } else {
        fprintf(stderr, "内存不足！\n");
    }
}
void appendNode_ctp(head_node *head, ContactPerson contact) {
    node_ctp *newNode = (node_ctp *)malloc(sizeof(node_ctp));
    if (newNode) {
        newNode->contactPerson = contact;
        newNode->next = NULL;

        if (head->next_ctp == NULL) {
            head->next_ctp = newNode;
            head->is_ctp = true;
            head->is_empty = false;
        } else {
            node_ctp *current = head->next_ctp;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    } else {
        fprintf(stderr, "内存不足！\n");
    }
}
void appendNode_emp(head_node *head, Employee employee) {
    node_emp *newNode = (node_emp *)malloc(sizeof(node_emp));
    if (newNode) {
        newNode->employee = employee;
        newNode->next = NULL;

        if (head->next_emp == NULL) {
            head->next_emp = newNode;
            head->is_emp = true;
            head->is_empty = false;
        } else {
            node_emp *current = head->next_emp;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    } else {
        fprintf(stderr, "内存不足！\n");
    }
}
void appendNode_rec(head_node *head, Record record) {
    node_rec *newNode = (node_rec *)malloc(sizeof(node_rec));
    if (newNode) {
        newNode->record = record;
        newNode->next = NULL;

        if (head->next_rec == NULL) {
            head->next_rec = newNode;
            head->is_rec = true;
            head->is_empty = false;
        } else {
            node_rec *current = head->next_rec;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newNode;
        }
    } else {
        fprintf(stderr, "内存不足！\n");
    }
}

// 释放所有的内存
void freeNodeList_cus(node_cus *node) {
    while (node != NULL) {
        node_cus *temp = node;
        node = node->next;
        free(temp);
    }
}
void freeNodeList_ctp(node_ctp *node) {
    while (node != NULL) {
        node_ctp *temp = node;
        node = node->next;
        free(temp);
    }
}
void freeNodeList_emp(node_emp *node) {
    while (node != NULL) {
        node_emp *temp = node;
        node = node->next;
        free(temp);
    }
}
void freeNodeList_rec(node_rec *node) {
    while (node != NULL) {
        node_rec *temp = node;
        node = node->next;
        free(temp);
    }
}
void freeAll(GtkWidget *widget,head_node *head) {
    if (!head) return; // 检查是否已经是空指针

    if (head->is_cus) freeNodeList_cus(head->next_cus);
    if (head->is_ctp) freeNodeList_ctp(head->next_ctp);
    if (head->is_emp) freeNodeList_emp(head->next_emp);
    if (head->is_rec) freeNodeList_rec(head->next_rec);

    free(head);  // 最后释放头节点自己
}
