#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE 128

void by_char(FILE *);
void by_buf(FILE *);

int main(int argc, char **argv)
{
    if (1 == argc)
    {
        perror("please input args to cat.");
        return -1;
    }
    argv++;
    FILE *f = fopen(*argv, "r");
    if (NULL == f)
    {
        perror("no such this file.");
        return -1;
    }
    // by_char(f);
    by_buf(f);

    system("pause");
    return 0;
}

void by_buf(FILE *f)
{
    char *buf = (char *)malloc(sizeof(char[BUFF_SIZE]));
    char *content = NULL;
    while (1)
    {
        content = fgets(buf, BUFF_SIZE, f);
        if (NULL == content)
        {
            break;
        }
        fputs(content, stdout);
    }
    printf("\n");
}

void by_char(FILE *f)
{
    while (1)
    {
        char ch = fgetc(f);
        if (EOF == ch)
        {
            break;
        }
        fputc(ch, stdout);
    }

    printf("\n");
}