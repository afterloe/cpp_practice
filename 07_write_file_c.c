#define _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <stdio.h>

int put_one_ch(char ch, FILE *);
int put_line(char *, FILE *);

int main()
{
    FILE *p = fopen("a.txt", "wb");
    if (NULL == p)
    {
        perror("open file failed.");
        return -1;
    }
    // printf("%d\n", put_one_ch('h', p));
    printf("write %d .\n", put_line("hello i'm afterloe.", p));
    system("pause");
    fclose(p);
    return 0;
}

int put_line(char *str, FILE *p)
{
    int count = 0;
    while (str[count] != 0)
    {
        fputc(str[count], p);
        count++;
    }
    return count;
}

int put_one_ch(const char ch, FILE *p)
{
    int d = fputc(ch, p);
    return d;
}