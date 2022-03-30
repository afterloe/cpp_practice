#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **args)
{
    char *path = (char *)malloc(sizeof(char[128]));
    if (1 == argc)
    {
        path = "a.txt";
    }
    else
    {
        path = args[1];
    }
    FILE *src = fopen(path, "r");
    FILE *dst = fopen("copy.gif", "w");
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