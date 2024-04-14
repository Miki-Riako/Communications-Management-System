// setsystem.c
#include "initialize.h"

void initializeSettingFile();
void initializeSetting();
void setSystem();
void updateSetting(const char *key, int value);
void changePassword();
void toggleDatabaseOption();
void toggleFileOption();
void enableBackup();
void loadFilesIntoMemory();

bool isStoredInDatabase = false;
bool isStoredInFile = false;
bool isBackupEnabled = false;
bool isLoadedIntoMemory = false;

void initializeSettingFile() {
    FILE *file;
    const char *filename = "setting.ini";

    // 尝试打开文件，检查是否存在
    file = fopen(filename, "r");
    if (file == NULL) {
        // 文件不存在，创建文件并写入默认值
        file = fopen(filename, "w");
        if (file == NULL) {
            perror("Failed to create setting file");
            return;
        }
        fprintf(file, "isStoredInDatabase=0\n");
        fprintf(file, "isStoredInFile=1\n");
        fprintf(file, "isBackupEnabled=0\n");
        fprintf(file, "isLoadedIntoMemory=0\n");
        fclose(file);
    } else {
        // 文件已存在，关闭文件，不需要写入
        fclose(file);
    }
}

void initializeSetting() {
    FILE *file;
    char line[256];
    const char *filename = "setting.ini";

    // 确保配置文件已初始化
    initializeSettingFile();

    // 打开文件读取配置
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open setting file");
        return;
    }
    while (fgets(line, sizeof(line), file) != NULL) {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");
        if (strcmp(key, "isStoredInDatabase") == 0) {
            isStoredInDatabase = atoi(value);
        } else if (strcmp(key, "isStoredInFile") == 0) {
            isStoredInFile = atoi(value);
        } else if (strcmp(key, "isBackupEnabled") == 0) {
            isBackupEnabled = atoi(value);
        } else if (strcmp(key, "isLoadedIntoMemory") == 0) {
            isLoadedIntoMemory = atoi(value);
        }
    }
    fclose(file);
}

void setSystem() {
    while (true) {
        initializeSetting();
        printf("\n系统设置\n\n");
        printf("1. 修改密码\n");
        if (isStoredInDatabase) {
            printf("2. 已开启储存至数据库，点击关闭\n");
        } else {
            printf("2. 未开启储存至数据库，点击开启\n");
        }
        if (isStoredInFile) {
            printf("3. 已开启储存至本地文件，点击关闭\n");
        } else {
            printf("3. 未开启储存至本地文件，点击开启\n");
        }
        if (isBackupEnabled) {
            printf("4. 已开启备份功能，点击关闭\n");
        } else {
            printf("4. 未开启备份功能，点击开启\n");
        }
        if (isLoadedIntoMemory) {
            printf("5. 已加载文件到内存，点击关闭\n");
        } else {
            printf("5. 未加载文件到内存，点击开启\n");
        }
        printf("加载文件到内存会在每次启动时将本地文件提取至内存层\n");
        printf("会导致程序启动时更慢，但是操作文件时更快\n");
        printf("6. 返回主菜单\n");

        printf("请选择一个操作（1-6）：");
        char choice;
        scanf(" %c", &choice);
        getchar();  // 清除缓冲区中的残留输入

        system(SYSTEM_CLEAR);
        switch(choice) {
            case '1':
                changePassword();
                break;
            case '2':
                toggleDatabaseOption();
                break;
            case '3':
                toggleFileOption();
                break;
            case '4':
                enableBackup();
                break;
            case '5':
                loadFilesIntoMemory();
                break;
            case '6':
                return;
            default:
                printf("无效的选择，请重新输入。\n");
        }
    }
}

void updateSetting(const char *key, int value) {
    FILE *file = fopen("setting.ini", "w");  // Open file in write mode to overwrite
    if (file == NULL) {
        perror("Failed to open settings file for update");
        return;
    }
    fprintf(file, "isStoredInDatabase=%d\n", isStoredInDatabase);
    fprintf(file, "isStoredInFile=%d\n", isStoredInFile);
    fprintf(file, "isBackupEnabled=%d\n", isBackupEnabled);
    fprintf(file, "isLoadedIntoMemory=%d\n", isLoadedIntoMemory);
    fclose(file);
}

void changePassword() {
    FILE *file = fopen("managers.csv", "r+");
    if (!file) {
        perror("无法打开用户文件");
        return;
    }

    char line[256];
    long pos = 0;
    bool found = false;
    while (fgets(line, sizeof(line), file)) {
        char *tmp = strdup(line);  // 复制一行，因为 strtok 会修改原字符串
        char *username = strtok(tmp, "|||");
        if (strcmp(username, User) == 0) {
            found = true;
            printf("请输入新密码：");
            string newPassword;
            scanf("%s", newPassword);

            // XOR 加密新密码（如果之前使用了加密）
            string encryptedPassword;
            xorEncryptDecrypt(newPassword, strlen(newPassword), encryptedPassword);

            // 定位到这一行的开头
            fseek(file, pos, SEEK_SET);
            fprintf(file, "%s|||%s\n", User, encryptedPassword);  // 写回新密码
            break;
        }
        free(tmp);  // 释放复制的字符串
        pos = ftell(file);  // 更新当前文件位置，以便重新写入
    }

    if (!found) {
        printf("未找到用户名：%s\n", User);
    }

    fclose(file);
}

void toggleDatabaseOption() {
    isStoredInDatabase = !isStoredInDatabase;  // 反转数据库存储状态
    updateSetting("isStoredInDatabase", isStoredInDatabase);
    printf("存储至数据库选项已%s。\n", isStoredInDatabase ? "开启" : "关闭");
}

void toggleFileOption() {
    isStoredInFile = !isStoredInFile;  // 反转数据库存储状态
    updateSetting("isStoredInFile", isStoredInFile);
    printf("存储至本地文件选项已%s。\n", isStoredInFile ? "开启" : "关闭");
}

void enableBackup() {
    isBackupEnabled = !isBackupEnabled;  // 反转备份功能状态
    updateSetting("isBackupEnabled", isBackupEnabled);
    printf("备份功能已%s。\n", isBackupEnabled ? "开启" : "关闭");
}

void loadFilesIntoMemory() {
    isLoadedIntoMemory = !isLoadedIntoMemory;  // 反转加载到内存状态
    updateSetting("isLoadedIntoMemory", isLoadedIntoMemory);
    printf("加载文件到内存已%s。\n", isLoadedIntoMemory ? "开启" : "关闭");
}


