![image-20240405153909181](https://typora4062.oss-cn-beijing.aliyuncs.com/image-20240405153909181.png)



![image-20240405153821162](https://typora4062.oss-cn-beijing.aliyuncs.com/image-20240405153821162.png)

![image-20240405153808194](https://typora4062.oss-cn-beijing.aliyuncs.com/image-20240405153808194.png)

![image-20240405153756291](https://typora4062.oss-cn-beijing.aliyuncs.com/image-20240405153756291.png)

![image-20240405153739126](https://typora4062.oss-cn-beijing.aliyuncs.com/image-20240405153739126.png)

![image-20240405153726917](https://typora4062.oss-cn-beijing.aliyuncs.com/image-20240405153726917.png)

![image-20240405153711898](https://typora4062.oss-cn-beijing.aliyuncs.com/image-20240405153711898.png)

![image-20240405153655231](https://typora4062.oss-cn-beijing.aliyuncs.com/image-20240405153655231.png)

![image-20240405153548219](https://typora4062.oss-cn-beijing.aliyuncs.com/image-20240405153548219.png)

![image-20240405153600000](https://typora4062.oss-cn-beijing.aliyuncs.com/image-20240405153600000.png)

![image-20240405153613210](https://typora4062.oss-cn-beijing.aliyuncs.com/image-20240405153613210.png)



task.json

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Compile GTK+3 Program",
            "type": "shell",
            // "command": "gcc `pkg-config --cflags gtk+-3.0` ${file} -o ${fileDirname}/${fileBasenameNoExtension} `pkg-config --libs gtk+-3.0`",
            //"command": "gcc `pkg-config --cflags gtk+-3.0` *.c -o ${fileDirname} `pkg-config --libs gtk+-3.0`",
            "command": "gcc `pkg-config --cflags gtk+-3.0` -o ${fileDirname}/${fileBasenameNoExtension} main.c manager.c salesperson.c `pkg-config --libs gtk+-3.0`",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "presentation": {
                "reveal": "always",
                "panel": "shared",
                "focus": true
            },
            "problemMatcher": [
                "$gcc"
            ],
            "options": {
                "cwd": "${workspaceFolder}"
            }
        }
    ]
}

```

c_cpp_properties.json

```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": 
            [
                "/usr/include/pango-1.0",
                "/usr/include/gtk-3.0",
                "/usr/include/uuid",
                "/usr/include/glib-2.0",
                "/usr/include/blkid",
                "/usr/include/cairo",
                "/usr/include/gdk-pixbuf-2.0",
                "/usr/include/at-spi2-atk/2.0",
                "/usr/lib/x86_64-linux-gnu/glib-2.0/include",
                "/usr/include/harfbuzz",
                "/usr/include/freetype2",
                "/usr/include/dbus-1.0",
                "/usr/include/gio-unix-2.0",
                "/usr/include/fribidi",
                "/usr/include/libmount",
                "/usr/include/atk-1.0",
                "/usr/lib/x86_64-linux-gnu/dbus-1.0/include",
                "/usr/include/at-spi-2.0",
                "/usr/include/libpng16",
                "/usr/include/pixman-1"
            ],
            
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c17",
            "cppStandard": "gnu++14",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```

```shell
gcc `pkg-config --cflags gtk+-3.0` -o main.exe main.c manager.c salesperson.c login.c `pkg-config --libs gtk+-3.0`
```





```c
// XOR 加密/解密算法
#define SECRET_KEY "P@ssw0rdP@ssw0rdP@ssw0rdP@ssw0rdP@ssw0rdP@ssw0rdP@ssw0rdP@ssw0rd"
void xorEncryptDecrypt(string input, size_t length) {
    string encryptionKey;
    strcpy(encryptionKey, SECRET_KEY);
    size_t key_length = strlen(encryptionKey);

    if (key_length == 0) {
        fprintf(stderr, "Encryption key is empty.\n");
        return;
    }

    for (size_t i = 0; i < length; ++i) {
        input[i] ^= encryptionKey[i % key_length];
    }
    input[length] = '\0'; // 确保输出是以null结尾的字符串
}
```

问题：如果字符加密异或后得到的结果刚好为'\0'或'\n'则会破环csv文件账密的存储格式，无法成功存储和加载。



解决方案：使用十六进制编码来保持输出的可打印性

```c
void xorEncryptDecrypt(string input, size_t length,string output) {
    string encryptionKey;
    strcpy(encryptionKey, SECRET_KEY);
    size_t key_length = strlen(encryptionKey);

    if (key_length == 0) {
        fprintf(stderr, "Encryption key is empty.\n");
        return;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char encrypted_char = input[i] ^ encryptionKey[i % key_length];
        sprintf(output + 2 * i, "%02x", encrypted_char);  // 将每个加密字节转换为两个十六进制字符
    }
    output[2 * length] = '\0'; // 确保输出字符串是以null结尾的
}
```



gtk3程序在windows11,wsl下运行窗口跳来跳去（每次打开出现位置不一样）

尝试1：通过 X Server 来实现在 Windows 上使用 WSL (Windows Subsystem for Linux) 运行 GTK 程序并显示图形用户界面

### 步骤 1: 安装 VcXsrv Windows X Server

1. **下载 VcXsrv**:
   - 访问 SourceForge 网站或搜索 "VcXsrv Windows X Server" 来找到下载链接。
   - 点击下载最新版本的安装文件。
2. **安装 VcXsrv**:
   - 打开下载的安装文件（如 `vcxsrv-64.x.x.x-installer.exe`）。
   - 遵循安装向导的步骤，接受协议，选择安装位置，默认设置通常就足够了。
   - 完成安装。

### 步骤 2: 配置 VcXsrv

1. **运行 XLaunch**（VcXsrv 的配置工具）:
   - 在 Windows 开始菜单中找到并启动 XLaunch。
2. **选择显示设置**:
   - 选择 "Multiple windows"（多窗口模式）。
   - 在“显示号”框中输入 `0`。
3. **选择如何启动客户端**:
   - 选择 "Start no client"（不启动任何客户端）。
4. **额外的设置**:
   - 勾选 "Clipboard"（剪贴板）和 "Primary Selection"（主选择），以支持剪贴板操作。
5. **禁用访问控制**:
   - 勾选 "Disable access control"（禁用访问控制），允许所有客户端连接。
6. **保存并完成配置**:
   - 点击“下一步”，然后选择“完成”。
   - 可以选择保存配置为桌面快捷方式，以便快速启动。

### 步骤 3: 配置 WSL 环境变量

1. 设置 DISPLAY 环境变量:

   - 打开 WSL 终端。

   - 在终端输入以下命令，将 DISPLAY 环境变量添加到你的 shell 配置文件（如 

     ```
     .bashrc
     ```

      或 

     ```
     .zshrc
     ```

     ）：

     ```
     bashCopy code
     echo "export DISPLAY=\$(grep nameserver /etc/resolv.conf | awk '{print \$2}'):0" >> ~/.bashrc
     ```

   - 执行 `source ~/.bashrc` 来使更改立即生效。

```shell
gcc `pkg-config --cflags gtk+-3.0` -o main main.c login.c menu.c libs/String.c libs/BasciIO.c libs/Regex.c widgets/customer_assign.c widgets/group_manage.c widgets/info_manage.c widgets/records_manage.c `pkg-config --libs gtk+-3.0`
```

c_cpp_properties.json

```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": 
            [
                
                "/usr/include/pango-1.0",
                "/usr/include/gtk-3.0",
                "/usr/include/uuid",
                "/usr/include/glib-2.0",
                "/usr/include/blkid",
                "/usr/include/cairo",
                "/usr/include/gdk-pixbuf-2.0",
                "/usr/include/at-spi2-atk/2.0",
                "/usr/lib/x86_64-linux-gnu/glib-2.0/include",
                "/usr/include/harfbuzz",
                "/usr/include/freetype2",
                "/usr/include/dbus-1.0",
                "/usr/include/gio-unix-2.0",
                "/usr/include/fribidi",
                "/usr/include/libmount",
                "/usr/include/atk-1.0",
                "/usr/lib/x86_64-linux-gnu/dbus-1.0/include",
                "/usr/include/at-spi-2.0",
                "/usr/include/libpng16",
                "/usr/include/pixman-1"
            ],
            
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c17",
            "cppStandard": "gnu++14",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}


```



launch.json

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "Debug GTK Application",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/main",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "/usr/bin/gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "Build GTK application",  // Make sure this matches the label in tasks.json
            "launchCompleteCommand": "exec-run"
        }
    ]
}

```

settings.json

```json
{
    "files.associations": {
        "array": "cpp",
        "atomic": "cpp",
        "bit": "cpp",
        "*.tcc": "cpp",
        "cctype": "cpp",
        "clocale": "cpp",
        "cmath": "cpp",
        "compare": "cpp",
        "concepts": "cpp",
        "cstdarg": "cpp",
        "cstddef": "cpp",
        "cstdint": "cpp",
        "cstdio": "cpp",
        "cstdlib": "cpp",
        "cwchar": "cpp",
        "cwctype": "cpp",
        "deque": "cpp",
        "string": "cpp",
        "unordered_map": "cpp",
        "vector": "cpp",
        "exception": "cpp",
        "algorithm": "cpp",
        "functional": "cpp",
        "iterator": "cpp",
        "memory": "cpp",
        "memory_resource": "cpp",
        "numeric": "cpp",
        "optional": "cpp",
        "random": "cpp",
        "string_view": "cpp",
        "system_error": "cpp",
        "tuple": "cpp",
        "type_traits": "cpp",
        "utility": "cpp",
        "initializer_list": "cpp",
        "iosfwd": "cpp",
        "iostream": "cpp",
        "istream": "cpp",
        "limits": "cpp",
        "new": "cpp",
        "numbers": "cpp",
        "ostream": "cpp",
        "stdexcept": "cpp",
        "streambuf": "cpp",
        "typeinfo": "cpp",
        "unordered_set": "cpp",
        "set": "cpp",
        "bitset": "cpp",
        "ranges": "cpp",
        "span": "cpp",
        "stacktrace": "cpp",
        "regex": "cpp",
        "valarray": "cpp",
        "stdlib.h": "c"
    }
}
```

tasks.json

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build GTK application",
            "type": "shell",
            "command": "${workspaceFolder}/build.sh",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": {
                "owner": "cpp",
                "fileLocation": ["absolute"],
                "pattern": {
                    "regexp": "^([^\\s].*)\\((\\d+),(\\d+)\\):\\s+(warning|error):\\s+(.*)$",
                    "file": 1,
                    "line": 2,
                    "column": 3,
                    "severity": 4,
                    "message": 5
                }
            }
        }
    ]
}

```

build.sh (src  .vscode 同级目录下)

```shell
#!/bin/bash

# 终止脚本在任何错误发生时
set -e

# 定义编译器和链接器选项
CFLAGS=$(pkg-config --cflags gtk+-3.0)
LIBS=$(pkg-config --libs gtk+-3.0)

# 定义输出文件名
OUTPUT="main"

# 定义源文件
SOURCES=$(find src -name '*.c')

# 输出开始编译的信息
echo "开始编译..."

# 编译命令
gcc $CFLAGS -o $OUTPUT $SOURCES $LIBS -g

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "编译成功，输出文件：$OUTPUT"
else
    echo "编译失败"
    exit 1
fi

```

ctrl + shift + b 构建

F5 debug (用vscode 打断点)



```
GtkWidget *dialog, *entry, *content_area;
    Employee newEmployee;

    // 初始化 GTK
    gtk_init(NULL, NULL);

    // 创建对话框
    dialog = gtk_dialog_new_with_buttons("添加业务员",
                                         NULL, // 在这里可以设置父窗口
                                         GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT,
                                         "_OK", GTK_RESPONSE_OK,
                                         "_Cancel", GTK_RESPONSE_CANCEL,
                                         NULL);
    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    entry = gtk_entry_new(); // 创建输入框
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry), "输入业务员姓名");
    gtk_container_add(GTK_CONTAINER(content_area), entry);

    // 显示所有组件
    gtk_widget_show_all(dialog);

    // 运行对话框并等待用户响应
    gint response = gtk_dialog_run(GTK_DIALOG(dialog));
    if (response == GTK_RESPONSE_OK) {
        const char *name = gtk_entry_get_text(GTK_ENTRY(entry));
        if (name && *name) {
            // 获取输入并复制到 newEmployee 结构
            strncpy(newEmployee.name, name, sizeof(newEmployee.name) - 1);
            newEmployee.name[sizeof(newEmployee.name) - 1] = '\0';

            // 保存到文件
            saveEmployeeToFile(newEmployee);

            // 显示新增的员工信息
            displayEmployee(newEmployee);

            // 打印确认信息
            printf("业务员信息已添加。\n");
        } else {
            printf("姓名输入不能为空。\n");
        }
    }

    // 销毁对话框
    gtk_widget_destroy(dialog);

    // 清理 GTK 环境，如果是单独应用运行，应调用 gtk_main_quit(); 或在主函数中调用 gtk_main();
```

