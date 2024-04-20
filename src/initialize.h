// initialize.h
#ifndef INITIALIZE_H
#define INITIALIZE_H

#include "header.h"

void initializeCustomerFile() {
    FILE *file = fopen("customers.csv", "r");
    if (!file) { // 文件不存在，创建新文件
        file = fopen("customers.csv", "w");
        if (!file) {
            perror("创建客户文件失败");
        } else {
            fprintf(file, "Name|||Region|||Address|||LegalRepresentative|||Scale|||BusinessContactLevel|||Email|||Phone\n");
            fclose(file);
        }
    } else {
        fclose(file); // 文件已存在，关闭文件
    }
}

void initializeCommunicationFile() {
    FILE *file = fopen("communication_records.csv", "r");
    if (!file) { 
        file = fopen("communication_records.csv", "w");
        if (!file) {
            perror("创建通信记录文件失败");
        } else {
            fprintf(file, "CompanyName|||ContactName|||Date|||Time|||Duration|||Content\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }
}

#endif