#!/bin/bash

# comp 函数：编译 main.c 并运行
comp() {
    if [ -f "main.c" ]; then
        echo "找到 main.c，正在编译..."
        g++ main.c -o main.exe

        if [ $? -eq 0 ]; then
            echo "编译成功！正在运行程序..."
            ./main.exe
        else
            echo "编译失败。"
        fi
    else
        echo "未找到 main.c 文件。"
    fi
}

# cl 函数：清理目录下的特定文件
cl() {
    echo "正在清理..."
    rm -f *.out *.exe *.csv
    echo "清理完毕。"
}

cd src || (echo "无法进入 src 目录" && exit 1)
