#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 128

char **load_data(const char *, const int);
char *cal(char *);
void write_paper(const char *, void *);

int main()
{
    char str[32] = "paper.txt";
    char **data = load_data(str, 100);
    write_paper(str, data);
    system("pause");
    return 0;
}

char **load_data(const char *file_name, int count)
{
    char **data = (char **)malloc(sizeof(char **[count][BUF_SIZE]));
    char *buf = (char *)malloc(BUF_SIZE);
    char *chunk = NULL;
    int i = 0;
    FILE *f = fopen(file_name, "r");
    if (NULL == f)
    {
        perror("no such this file.");
        exit(-1);
    }
    while (1)
    {
        chunk = fgets(buf, BUF_SIZE, f);
        if (NULL == chunk)
        {
            break;
        }
        data[i] = cal(chunk);
        i++;
    }
    fclose(f);
    return data;
}

char *cal(char *content)
{
    int x;
    int y;
    int num;
    char symbol;
    sscanf(content, "%d%c%d", &x, &symbol, &y);
    switch (symbol)
    {
    case '+':
        num = x + y;
        break;
    case '-':
        num = x - y;
        break;
    case 'x':
        num = x * y;
        break;
    case '/':
        num = x / y;
        break;
    }
    char *chunk = (char *)malloc(128);
    sprintf(chunk, "%d%c%d=%d\n", x, symbol, y, num);
    return chunk;
}

void write_paper(const char *file_name, void *data)
{
    FILE *f = fopen(file_name, "w+");
    if (NULL == f)
    {
        perror("authored.");
        exit(-1);
    }
    char **chunk = (char **)data;
    while (*chunk != 0)
    {
        fputs(*chunk, f);
        chunk++;
    }
    fclose(f);
    printf("paper has done.\n");
}