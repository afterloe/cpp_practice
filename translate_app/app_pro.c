#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFF_SIZE 256

typedef struct _dict_item
{
    char *key;
    char *value;
} DICT_ITEM;

extern int get_file_line(char *);
extern int init_dict(DICT_ITEM **, char *);
extern void search_dict(DICT_ITEM *, int, char *);
extern void trim(char *);
extern FILE *open_file(const char *);

int main()
{
    DICT_ITEM *dict = NULL;
    int count = init_dict(&dict, "/home/afterloe/Resources/dicts/dict_utf8.txt");
    if (-1 == count)
    {
        printf("[error]: 字典初始化失败。\n");
        return count;
    }
    printf("[info]: 字典加载成功，共 %d 条\n", count);
    printf("%s %s\n", dict[200].key, dict[200].value);
    printf("[info]: 请输入要翻译的内容\n");
    char *input = NULL;
    char *buff = (char *)malloc(BUFF_SIZE);
    while (1)
    {
        input = fgets(buff, BUFF_SIZE, stdin);
        input[strlen(input) - 1] = 0x00;
        search_dict(dict, count, input);
    }

    return 0;
}

int init_dict(DICT_ITEM **p, char *dict_path)
{
    FILE *f = open_file(dict_path);
    char *buff = (char *)malloc(BUFF_SIZE);
    int line_count = get_file_line(dict_path);
    DICT_ITEM *tmp = (DICT_ITEM *)malloc(sizeof(DICT_ITEM) * line_count);
    char *content = NULL;
    while (1)
    {
        content = fgets(buff, BUFF_SIZE, f);
        if (NULL == content)
        {
            break;
        }
        trim(content);
        tmp->key = (char *)malloc(strlen(content));
        strcpy(tmp->key, content + 1);

        content = fgets(buff, BUFF_SIZE, f);
        if (NULL == content)
        {
            break;
        }
        trim(content);
        tmp->value = (char *)malloc(strlen(content + 5));
        strcpy(tmp->value, content + 6);

        tmp++;
        break;
    }

    fclose(f);
    *p = tmp;
    return line_count;
}

int get_file_line(char *file_path)
{
    char *buff = (char *)malloc(BUFF_SIZE);
    int line_num = 0;
    FILE *f = open_file(file_path);
    while (NULL != fgets(buff, BUFF_SIZE, f))
    {
        line_num += 2;
    }
    fclose(f);
    return line_num;
}

void search_dict(DICT_ITEM *dict, int line_count, char *src)
{
    for (int i = 0; i < line_count; i++)
    {
        if (strcmp(src, dict->key) == 0)
        {
            printf("[info]: %s\n", dict->value);
            break;
        }
        dict++;
    }
    printf("[info]: 未找到对应内容。\n");
}

void trim(char *content)
{
    for (int i = strlen(content); i > 0; i--)
    {
        char c = content[i];
        if (c == '\r' || c == '\n' || c == '\t' || c == ' ')
        {
            content[i] = 0;
        }
        else
        {
            break;
        }
    }
}

FILE *open_file(const char *file_path)
{
    FILE *f = fopen(file_path, "r");
    if (NULL == f)
    {
        perror("[error]");
        exit(-1);
    }
    return f;
}