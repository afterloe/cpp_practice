#include "enter.h"

int get_file_line(char *file_name)
{
    if (NULL == file_name)
    {
        perror("获取信息失败.");
        return -1;
    }

    FILE *f = fopen(file_name, "r");

    char buf[1024] = {0};
    int line = 0;
    while (NULL != fgets(buf, 1024, f))
    {
        line++;
    }

    fclose(f);
    f = NULL;

    return line;
}

void get_file_name(char **dst, int argc, char **args)
{
    char *file_name = (char *)malloc(SIZE);
    if (1 == argc)
    {
        strcpy(file_name, "./config.txt");
    }
    else
    {
        args++;
        file_name = *args;
    }

    *dst = file_name;
}