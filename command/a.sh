#!/bin/bash

# comp 函数：在当前目录编译 main.c 并将输出放入 build 目录
comp() {
    if [ -f "../src/main.c" ]; then
        echo "找到 main.c，正在编译..."
        gcc ../src/main.c -o cms.out

        if [ $? -eq 0 ]; then
            echo "编译成功！正在运行程序..."
            ./cms.out
        else
            echo "编译失败。"
        fi
    else
        echo "未找到 main.c 文件。"
    fi
}

# dbg 函数：编译为调试版本并放入 build/Debug 目录
dbg() {
    mkdir -p Debug
    if [ -f "../src/main.c" ]; then
        echo "找到 main.c，正在编译调试版本..."
        gcc -g ../src/main.c -o Debug/outDebug

        if [ $? -eq 0 ]; then
            echo "编译调试版本成功！"
        else
            echo "编译调试版本失败。"
        fi
    else
        echo "未找到 main.c 文件。"
    fi
}

# rls 函数：编译为发布版本并放入 bin 目录
rls() {
    if [ -f "../src/main.c" ]; then
        echo "找到 main.c，正在编译发布版本..."
        gcc ../src/main.c -o ../bin/cms.exe

        if [ $? -eq 0 ]; then
            echo "编译发布版本成功！"
        else
            echo "编译发布版本失败。"
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

cd ../build || (echo "无法进入 build 目录" && exit 1)