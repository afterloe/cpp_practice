#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 64
#define BIG_SIZE 1024

typedef struct
{
    char key[SIZE];
    char value[SIZE];
} CONFIG;

// 获取文件有效行数
extern int get_file_line(char *);

// 获取读取配置文件的名称
extern void get_file_name(char **, int, char **);

// 判断是否是有效配置项
extern int is_invalid_line(char *);

// 配置项初始化
extern void parse_file(CONFIG **, int, char *);

// 通过配置项获取配置值
extern char * get_value(char *, CONFIG *, int);

// 释放内存
extern void free_space(CONFIG *, char *);