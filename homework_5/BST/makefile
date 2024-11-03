# Makefile for Binary Search Tree project

# 编译目标
TARGET = bst_test

# 源文件
SRCS = main.cpp BinarySearchTree.h

# 生成可执行文件
all: 
	g++ main.cpp -o $(TARGET) -std=c++20 -O2

# 运行程序
run: all
	./$(TARGET)

# 生成报告
report:
	xelatex report.tex
	xelatex report.tex # 可能需要两次编译以处理引用

# 清理生成的文件
clean:
	rm -f $(TARGET) report.pdf *.log *.aux

.PHONY: all run report clean
