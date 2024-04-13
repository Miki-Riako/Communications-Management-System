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

