#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUM 100

char symbol[4] = {'+', '-', 'x', '/'};
char **generator_data(int);
void write_file(char *, char **, int);

int main()
{
    int num_of_test = 100;
    char dst[32] = "paper.txt";
    char **data = generator_data(num_of_test);
    write_file(dst, data, num_of_test);
    printf("[SUCCESS]. generator %d test paper in %s\n", num_of_test, dst);
    system("pause");
    return 0;
}

char **generator_data(int size)
{
    int x;
    int y;
    char **data = (char **)malloc(sizeof(char[size][MAX_NUM]));
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++)
    {
        char *content = (char *)malloc(MAX_NUM);
        x = rand() % MAX_NUM + 1;
        y = rand() % MAX_NUM + 1;
        sprintf(content, "%d%c%d=\n", x, symbol[rand() % 4], y);
        data[i] = content;
    }

    return data;
}

void write_file(char *dst, char **data, int size)
{
    FILE *f = fopen(dst, "w");
    if (NULL == f)
    {
        perror("open file failed");
        exit(-1);
    }
    while (0 != *data)
    {
        fputs(*data, f);
        data++;
    }
    fclose(f);
}