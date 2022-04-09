#include <stdlib.h>
#include <stdio.h>

#define BUF_LENGTH 128

void read_ch(FILE *);
void read_all(FILE *);
void read_all_full(FILE *);

int main()
{
    FILE *f = fopen("a.txt", "r");
    if (NULL == f)
    {
        perror("no such this file.");
        return -1;
    }
    // read_ch(f);
    // read_all(f);
    read_all_full(f);
    system("pause");
    fclose(f);
    return 0;
}

void read_all_full(FILE *f)
{
    while (!feof(f))
    {
        printf("%c", fgetc(f));
    }
    printf("\n");
}

void read_all(FILE *f)
{
    char ch;
    while ((ch = fgetc(f)) != EOF)
    {
        printf("%c", ch);
    }
    printf("\n");
}

void read_ch(FILE *f)
{
    char ch = fgetc(f);
    printf("%c\n", ch);
}