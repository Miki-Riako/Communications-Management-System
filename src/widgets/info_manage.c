// widgets/info_manage.c
#include "../header.c"

void infoManageWidget();
void initializeInfoFile();

void infoManageWidget() {
    initializeInfoFile();
    while(true) {
        printf("您好！管理员%s\n", User);
        printf("1. 增加业务员信息\n");
        printf("2. 修改业务员信息\n");
        printf("3. 删除业务员信息\n");
        printf("4. 增加客户信息\n");
        printf("5. 修改客户信息\n");
        printf("6. 删除客户信息\n");
        printf("7. 增加客户联络员信息\n");
        printf("8. 修改客户联络员信息\n");
        printf("9. 删除客户联络员信息\n");
        printf("0. 退出系统\n");
        printf("请选择一个操作（0-9）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);

        if (!isOneChar(get)) {
            printf("无效的选项，请重新选择。\n");
            continue;  // 继续循环等待有效输入
        }
        switch (get[0]) {
            case '1':

                break;
            case '2':

                break;
            case '3':

                break;
            case '4':

                break;
            case '5':

                break;
            case '6':

                break;
            case '7':

                break;
            case '8':

                break;
            case '9':

                break;
            case '0':
                return;  // 返回主菜单
            default:
                printf("无效的选项，请重新输入。\n");
        }
    }
}

void initializeInfoFile() {
    FILE *file
    
    file = fopen("employees.csv", "r");
    if (!file) {
        file = fopen("employees.csv", "w");
        if (!file) {
            perror("创建业务员文件失败");
        } else {
            fprintf(file, "Name|||Gender|||Birthday|||Email|||Phone|||Representative\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }

    file = fopen("customers.csv", "r");
    if (!file) {
        file = fopen("customers.csv", "w");
        if (!file) {
            perror("创建客户文件失败");
        } else {
            fprintf(file, "Name|||Region|||Address|||LegalRepresentative|||Scale|||BusinessContactLevel|||Email|||Phone\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }

file = fopen("contacts.csv", "r");
    if (!file) {
        file = fopen("contacts.csv", "w");
        if (!file) {
            perror("创建联系人文件失败");
        } else {
            fprintf(file, "Name|||Gender|||Birthday|||Email|||Phone|||Representative\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }
}



// end widgets/info_manage.c