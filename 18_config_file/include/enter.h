#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 64

typedef struct
{
    char key[SIZE];
    char value[SIZE];
} CONFIG;

// 获取文件有效行数
extern int get_file_line(char *);
extern void get_file_name(char **, int, char **);
extern int is_invalid_line(char *);