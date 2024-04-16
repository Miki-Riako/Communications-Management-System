// 用户是否已经存在
bool alreadyExists(const char *filename, const char *name) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开文件失败");
        return false;
    }

    char line[MAX_LENGTH * 4];
    bool exists = false;
    while (fgets(line, sizeof(line), file)) {
        char file_username[MAX_LENGTH];
        sscanf(line, "%254[^|||]", file_username);
        if (strcmp(name, file_username) == 0) {
            exists = true;
            break;
        }
    }
    fclose(file);
    return exists;
}

// 某行是否存在
bool lineExists(const char *filename, const char *lineToCheck) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("打开文件失败");
        return false;
    }

    char line[MAX_LENGTH * 4];
    bool exists = false;
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(lineToCheck, line) == 0) {
            exists = true;
            break;
        }
    }
    fclose(file);
    return exists;
}

// 初始化创建文件
void initializeInfoFile(const char *path, const char *header) {
    FILE *file = fopen(path, "r");
    if (!file) {
        file = fopen(path, "w");
        if (file) {
            if (!isEmpty(header)) fprintf(file, "%s\n", header);
            fclose(file);
        } else {
            fprintf(stderr, "Error creating file %s\n", path);
        }
    } else {
        fclose(file);
    }
}

// 不输出内容的remove
bool removeEntry(const char *filename, const char *delName) {
    char buffer[MAX_LENGTH];
    FILE *fp, *fp_temp;

    fp = fopen(filename, "r");
    if (!fp) {
        printf("无法打开文件 %s\n", filename);
        return false;
    }

    fp_temp = fopen("temp.csv", "w");
    if (!fp_temp) {
        printf("无法创建临时文件\n");
        fclose(fp);
        return false;
    }

    while (fgets(buffer, MAX_LENGTH, fp) != NULL) {
        // 检查是否包含要删除的用户名
        char* found = strstr(buffer, delName);
        if (found != buffer) { // 确保是从行首开始匹配用户名
            fprintf(fp_temp, "%s", buffer);
        }
    }

    fclose(fp);
    fclose(fp_temp);

    remove(filename);
    rename("temp.csv", filename);
    return true;
}

// 删除头标题的行
void removeRecord(const char *filename, const char *prompt) {
    char delName[MAX_LENGTH];

    while (true) {
        printf("%s", prompt); // 显示删除提示信息
        getInput(delName, sizeof(delName));
        if (!isEmpty(delName)) {
            if (alreadyExists(filename, delName)) {
                break;
            } else {
                printf("记录不存在！\n");
            }
        } else {
            printf("请输入一个有效的名字。\n");
        }
    }

    if (removeEntry(filename, delName)) {
        printf("记录删除成功。\n");
    } else {
        printf("记录删除失败。\n");
    }
}

// 将一行写入一个文件
void writeLineToFile(const char *filename, const char *data) {
    FILE *file = fopen(filename, "a"); // 以追加模式打开文件
    if (!file) {
        perror("打开文件失败");
        return;
    }
    fprintf(file, "%s\n", data);
    fclose(file);
}
