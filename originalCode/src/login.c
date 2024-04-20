// login.c
#include "header.h"
#include "menu.c"

void startWidget();
void loginManagerWidget();
void loginEmployeeWidget();
void registerWidget();

void startWidget() {
    initializeInfoFile("user.csv", "");
    while (true) {
        printf("登入中...\n");
        printf("请选择角色：\n");
        printf("1. 公司经理\n");
        printf("2. 公司业务员\n");
        printf("3. 注册业务员\n");
        printf("4. 退出程序\n");
        printf("请输入选择的角色数字（1-4）：");

        char get[MAX_LENGTH];
        getInput(get, sizeof(get));
        system(SYSTEM_CLEAR);

        if (!isOneChar(get)) {
            printf("无效的选项，请重新选择。\n");
            continue;  // 继续循环等待有效输入
        }
        switch (get[0]) {
        case '1':
            loginManagerWidget();
            break;
        case '2':
            loginEmployeeWidget();
            break;
        case '3':
            registerWidget();
            break;
        case '4':
            printf("程序已退出。\n");
            exit(0);
        default:
            printf("无效的选项，请重新选择。\n");
        }
    }
}

void loginManagerWidget() {
    for (int i = 0; i < 3; ++i) {
        char password[MAX_LENGTH];

        printf("请输入公司密钥：");
        getInput(password, sizeof(password));

        system(SYSTEM_CLEAR);
        if (isSameString(password, SECRET_KEY) || DEBUG_MODE) {
            printf("登录成功！欢迎, 经理!\n");
            strcpy(User, "Manager");
            IsManager = true;
            managerMenuWidget();
            return;
        } else {
            printf("登录失败，密码错误。还剩下%d次机会。\n", 3 - i);
        }
    }
    printf("尝试使用密钥登录失败，系统关闭。\n");
    exit(0);
}

void loginEmployeeWidget() {
    char username[MAX_LENGTH];
    char password[MAX_LENGTH], confirmPassword[MAX_LENGTH];
    char encryptedPassword[MAX_LENGTH * 2];

    // 获取用户输入
    printf("请输入用户名：");
    getInput(username, sizeof(username));

    printf("请输入密码：");
    getInput(password, sizeof(password));
    xorEncryptDecrypt(password, strlen(password), encryptedPassword); // 加密用户密码

    system(SYSTEM_CLEAR);

    // 验证登录
    if (verify(username, encryptedPassword) || DEBUG_MODE) {
        printf("登录成功！欢迎, %s!\n", username);
        strcpy(User, username);
        IsManager = false;
        employeeMenuWidget();
        return;
    } else {
        printf("登录失败，用户名或密码错误。\n");
    }
}

void registerWidget() {
    FILE *file;
    char line[MAX_LENGTH * 3];
    char username[MAX_LENGTH];
    char password[MAX_LENGTH], confirmPassword[MAX_LENGTH];
    char encryptedPassword[MAX_LENGTH * 2];
    char role[MAX_LENGTH];

    printf("创建新用户.\n");

    while (true) {
        infoInput(username, sizeof(username), "请输入用户名：");
        if (isEmpty(username)) {
            printf("用户名不能为空。\n");
            continue;
        } else if (alreadyExists("user.csv", username)) {
            printf("用户已存在.\n");
            continue;
        } else {
            break;
        }
    }

    while (true) {
        infoInput(password, sizeof(password), "请输入新密码：");
        if (!matchRegex(password)) {
            printf("密码不符合要求。必须至少8个字符且包含大写字母、小写字母、数字、标点符号中的两种。\n");
            continue;
        }

        infoInput(confirmPassword, sizeof(confirmPassword), "请再次输入新密码以确认：");
        if (!isSameString(password, confirmPassword)) {
            printf("两次输入的密码不匹配。\n");
            continue;
        } else {
            xorEncryptDecrypt(password, strlen(password), encryptedPassword);
            break;
        }
    }

    file = fopen("user.csv", "r");
    if (!file) {
        perror("打开文件失败");
        return;
    }

    // 检查用户名是否已存在
    if (alreadyExists("user.csv", username)) {
        printf("用户已存在.\n");
        return;
    }

    char fullLine[MAX_LENGTH * 3 + 4];
    strcpy(fullLine, username);
    addColumn(fullLine, encryptedPassword);
    writeLineToFile("user.csv", fullLine);
    printf("用户注册成功.\n");

    printf("要现在就添加用户的信息吗？（Y?）\n");
    char get[MAX_LENGTH];
    getInput(get, sizeof(get));
    if (get[0] == 'Y' || get[0] == 'y') {
        Employee newEmployee;
        addEntry(1, "employees.csv", "请输入业务员姓名：", &newEmployee, NULL, NULL);
        saveEmployeeToFile(newEmployee);
        displayEmployee(newEmployee);
        printf("业务员信息已添加。\n");
    }
    system(SYSTEM_CLEAR);
}

// end login.c