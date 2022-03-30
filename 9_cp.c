#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **args)
{
    char *path = NULL;
    if (1 == argc)
    {
        path = "a.txt";
    }
    else
    {
        path = args[1];
    }
    //b是二进制模式的意思，b只是在Windows有效，在Linux用r和rb的结果是一样的
    FILE *src = fopen(path, "rb");
    FILE *dst = fopen("copy.gif", "wb");
    if (NULL == src || NULL == dst)
    {
        perror("no such file, src, dst");
        return -1;
    }
    int count = 0;
    while (1)
    {
        char ch = fgetc(src);
        if (feof(src))
        {
            break;
        }
        fputc(ch, dst);
        count++;
    }
    printf("copy file success, %d byte \n", count);
    fclose(src);
    fclose(dst);
    system("pause");
    return 0;
}