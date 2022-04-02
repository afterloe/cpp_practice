#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 128
#define DICT_SIZE 2

typedef struct _dict_item
{
    char *key;
    char *value;
} DICT_ITEM;

extern void init_dict(DICT_ITEM **);
extern int search_dict(DICT_ITEM *, char *, char *);

int main()
{
    DICT_ITEM *dict = NULL;
    init_dict(&dict);
    printf("[info]: 请输入要翻译的内容.\n");
    char *buf = (char *)malloc(BUF_SIZE);
    char *translate = (char *)malloc(BUF_SIZE);
    while (1)
    {
        fgets(buf, sizeof(buf), stdin);
        buf[strlen(buf) - 1] = _IOFBF;
        if (0 == search_dict(dict, buf, translate))
        {
            printf("[error]: 未找到对应翻译内容，请更新词典。\n");
        }
        else
        {
            printf("[info]: %s\n", translate);
        }
    }

    return 0;
}

void init_dict(DICT_ITEM **p)
{
    DICT_ITEM *tmp = (DICT_ITEM *)malloc(sizeof(DICT_ITEM) * DICT_SIZE);
    tmp[0].key = (char *)malloc(strlen("hello") + 1);
    strcpy(tmp[0].key, "hello");
    tmp[0].value = (char *)malloc(strlen("你好") + 1);
    strcpy(tmp[0].value, "你好");
    tmp[1].key = (char *)malloc(strlen("世界") + 1);
    strcpy(tmp[1].key, "世界");
    tmp[1].value = (char *)malloc(strlen("world") + 1);
    strcpy(tmp[1].value, "world");
    printf("[info]: 字典初始化完毕。\n");
    *p = tmp;
}

int search_dict(DICT_ITEM *dict, char *src, char *translate)
{
    for (int i = 0; i < DICT_SIZE; i++)
    {
        if (strcmp(src, dict->key) == 0)
        {
            strcpy(translate, dict->value);
            return 1;
        }
        dict++;
    }
    return 0;
}