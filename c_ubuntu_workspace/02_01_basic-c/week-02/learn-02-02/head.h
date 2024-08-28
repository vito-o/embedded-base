#ifndef __HEAD_H__  //若是宏没有定义
#define __HEAD_H__  //定义宏
// 当前代码只会执行一次
// 该文件被多次引用，其他文件引用的话，会被宏隔绝

// 头文件存放的内容
// 1.其他需要使用的头文件
// 2.函数或全局变量的声明
// 3.结构体的声明
// 4.宏的定义

#include <stdio.h>

extern int m;
extern int n;
extern int find_max();

#define STR "you will become a better man"

#endif
