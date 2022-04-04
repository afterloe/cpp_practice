#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int get_file_line(FILE *);
extern void read_from_file(FILE *, char **, int);
extern void show_content(char **, int);
extern void space_recovery(char **, int);

int main()
{
    FILE *f = fopen("./.gitignore", "r");
    if (NULL == f)
    {
        perror("");
        return EXIT_FAILURE;
    }

    int line = get_file_line(f);
    fseek(f, 0, SEEK_SET);
    printf("file line is %d\n", line);
    char **data = (char **)malloc(sizeof(char *) * line);
    read_from_file(f, data, line);
    show_content(data, line);

    space_recovery(data, line);
    fclose(f);
    f = NULL;
    return EXIT_SUCCESS;
}

void space_recovery(char **ptr, int count)
{
    for (int i = 0; i < count; i ++)
    {
        free(ptr[i]);
        ptr[i] = NULL;
    }
    free(ptr);
    ptr = NULL;
}

void show_content(char **ptr, int count)
{
    for (int i = 0; i < count; i++)
    {
        printf("[%d]: %s\n", i, *ptr);
        ptr++;
    }
}

void read_from_file(FILE *f, char **ptr, int line_num)
{
    char buf[1024] = {0};
    int index = 0;
    int str_len = -1;
    while (NULL != fgets(buf, 1024, f))
    {
        str_len = strlen(buf);
        char *line = (char *)malloc(str_len + 1);
        strcpy(line, buf);
        line[str_len - 1] = 0;
        ptr[index++] = line;
        memset(buf, 0, 1024);
    }
}

int get_file_line(FILE *f)
{
    char buf[1024] = {0};
    int line_num = 0;
    while (NULL != fgets(buf, 1024, f))
    {
        line_num++;
    }

    return line_num;
}