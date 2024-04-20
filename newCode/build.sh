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
