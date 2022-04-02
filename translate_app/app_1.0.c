#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _dict_item
{
    char key[128];
    char value[128];
} DICT_ITEM;

extern void init_dict(DICT_ITEM **);
extern int searh(DICT_ITEM *, int, char *, char *);

int main()
{
    DICT_ITEM *dict = NULL;
    init_dict(&dict);

    int ret = 0;
    char input[128] = {0};
    char content[128] = {0};
    printf("提示： 请输入要翻译的内容。\n");
    while (1)
    {
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = 0;
        ret = searh(dict, 2, input, content);
        if (0 == ret)
        {
            printf("未找到[%s]对应内容，请更新词典。\n", input);
        }
        else
        {
            printf(":-> %s\n", content);
        }
    }

    return 0;
}

void init_dict(DICT_ITEM **tmp)
{

    // DICT_ITEM items[2] = {{"world", "世界"}, {"hello", "你好"}};
    // DICT_ITEM *p = items;
    DICT_ITEM *p = (DICT_ITEM*)malloc(sizeof(DICT_ITEM) * 2);
    strcpy(p[0].key, "hello");
    strcpy(p[0].value, "你好");
    strcpy(p[1].key, "世界");
    strcpy(p[1].value, "world");
    *tmp = p;
    printf("字典加载完成\n");
}

int searh(DICT_ITEM *item, int size, char *src, char *translate)
{
    for (int i = 0; i < size; i++)
    {
        // 比较 s1 和 s2 的ASCII码大小，0 相等
        if (strcmp(src, item[i].key) == 0)
        {
            strcpy(translate, item[i].value);
            return 1;
        }
    }
    return 0;
}