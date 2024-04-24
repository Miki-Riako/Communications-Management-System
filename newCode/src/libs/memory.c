#include "../header.h"
// 初始化头结点
void initializeHeadNode(head_node *head) {
    if (head) {
        head->is_empty = true;
        head->is_cus = false;
        head->is_ctp = false;
        head->is_emp = false;
        head->is_rec = false;
        head->next_cus = NULL;
        head->next_ctp = NULL;
        head->next_emp = NULL;
        head->next_rec = NULL;
    }
}

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

// 连接结点
void linkNode_cus(head_node *head, node_cus *newNode) {
    if (newNode == NULL) return; // 如果新节点为空，则不执行任何操作
    newNode->next = NULL; // 新节点将被添加到末尾，所以其next指针应该是NULL

    if (head->next_cus == NULL) {
        // 如果链表为空，则新节点即为链表的第一个节点
        head->next_cus = newNode;
        head->is_cus = true;
        head->is_empty = false;
    } else {
        // 遍历到链表的末尾
        node_cus *current = head->next_cus;
        while (current->next != NULL) {
            current = current->next;
        }
        // 将末尾节点的next指针指向新节点
        current->next = newNode;
    }
}
void linkNode_ctp(head_node *head, node_ctp *newNode) {
    if (newNode == NULL) return;
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
}
void linkNode_emp(head_node *head, node_emp *newNode) {
    if (newNode == NULL) return;
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
}
void linkNode_rec(head_node *head, node_rec *newNode) {
    if (newNode == NULL) return;
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
}

// 复制结点
node_cus *copyNode_cus(node_cus *original) {
    if (!original) return NULL;
    node_cus *copy = (node_cus *)malloc(sizeof(node_cus));
    if (copy) {
        // 复制所有字段
        strcpy(copy->customer.name, original->customer.name);
        strcpy(copy->customer.region, original->customer.region);
        strcpy(copy->customer.address, original->customer.address);
        strcpy(copy->customer.legalRepresentative, original->customer.legalRepresentative);
        strcpy(copy->customer.scale, original->customer.scale);
        strcpy(copy->customer.businessContactLevel, original->customer.businessContactLevel);
        strcpy(copy->customer.email, original->customer.email);
        strcpy(copy->customer.phone, original->customer.phone);
        copy->next = NULL;
    }
    return copy;
}
node_ctp *copyNode_ctp(node_ctp *original) {
    if (!original) return NULL;
    node_ctp *copy = (node_ctp *)malloc(sizeof(node_ctp));
    if (copy) {
        // 复制所有字段
        strcpy(copy->contactPerson.name, original->contactPerson.name);
        strcpy(copy->contactPerson.gender, original->contactPerson.gender);
        strcpy(copy->contactPerson.birthday, original->contactPerson.birthday);
        strcpy(copy->contactPerson.email, original->contactPerson.email);
        strcpy(copy->contactPerson.phone, original->contactPerson.phone);
        strcpy(copy->contactPerson.representative, original->contactPerson.representative);
        copy->next = NULL;
    }
    return copy;
}
node_emp *copyNode_emp(node_emp *original) {
    if (!original) return NULL;
    node_emp *copy = (node_emp *)malloc(sizeof(node_emp));
    if (copy) {
        // 复制所有字段
        strcpy(copy->employee.name, original->employee.name);
        strcpy(copy->employee.gender, original->employee.gender);
        strcpy(copy->employee.birthday, original->employee.birthday);
        strcpy(copy->employee.email, original->employee.email);
        strcpy(copy->employee.phone, original->employee.phone);
        strcpy(copy->employee.representative, original->employee.representative);
        copy->next = NULL;
    }
    return copy;
}
node_rec *copyNode_rec(node_rec *original) {
    if (!original) return NULL;
    node_rec *copy = (node_rec *)malloc(sizeof(node_rec));
    if (copy) {
        // 复制所有字段
        strcpy(copy->record.user, original->record.user);
        strcpy(copy->record.companyName, original->record.companyName);
        strcpy(copy->record.contactName, original->record.contactName);
        strcpy(copy->record.date, original->record.date);
        strcpy(copy->record.time, original->record.time);
        strcpy(copy->record.duration, original->record.duration);
        strcpy(copy->record.content, original->record.content);
        copy->next = NULL;
    }
    return copy;
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

// 交换两个链表的位置
void swapLists(head_node **headA, head_node **headB) {
    if (!headA || !headB) return;  // 如果任一链表不存在，直接返回

    // 交换两个链表的所有指针和状态
    head_node *temp = *headA;
    *headA = *headB;
    *headB = temp;
}

// 清空链表
void clearList(head_node *head) {
    if (!head) return;  // 检查头节点是否存在

    // 释放所有节点的子链表
    if (head->is_cus && head->next_cus != NULL) freeNodeList_cus(head->next_cus);
    if (head->is_ctp && head->next_ctp != NULL) freeNodeList_ctp(head->next_ctp);
    if (head->is_emp && head->next_emp != NULL) freeNodeList_emp(head->next_emp);
    if (head->is_rec && head->next_rec != NULL) freeNodeList_rec(head->next_rec);

    // 重置头节点的状态
    head->is_empty = true;
    head->is_cus = false;
    head->is_ctp = false;
    head->is_emp = false;
    head->is_rec = false;
    head->next_cus = NULL;
    head->next_ctp = NULL;
    head->next_emp = NULL;
    head->next_rec = NULL;
}