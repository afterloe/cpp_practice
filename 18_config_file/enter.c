#include "enter.h"

int get_file_line(char *file_name)
{
    if (NULL == file_name)
    {
        perror("获取信息失败.");
        return -1;
    }

    FILE *f = fopen(file_name, "r");

    char buf[BIG_SIZE] = {0};
    int line = 0;
    while (NULL != fgets(buf, BIG_SIZE, f))
    {
        if (is_invalid_line(buf))
        {
            line++;
        }
    }

    fclose(f);
    f = NULL;

    return line;
}

void get_file_name(char **dst, int argc, char **args)
{
    char *file_name = (char *)malloc(SIZE);
    if (1 == argc)
    {
        strcpy(file_name, "./config.txt");
    }
    else
    {
        args++;
        file_name = *args;
    }

    *dst = file_name;
}

int is_invalid_line(char * str)
{
    if (str[0] == '\n' || strchr(str, ':') == NULL)
    {
        return 0;
    }

    return 1;
}

void parse_file(CONFIG **config, int size, char * file_name)
{
    FILE * file = fopen(file_name, "r");
    if (NULL == file)
    {
        return ;
    }
    CONFIG * tmp = (CONFIG *) malloc(sizeof(CONFIG) * size);
    char *buf = (char *) malloc(BIG_SIZE);

    int idx = 0;
    while (fgets(buf, BIG_SIZE, file) != NULL)
    {
        if (!is_invalid_line(buf)) {
            continue;
        }
        memset(tmp[idx].key, 0, SIZE);
        memset(tmp[idx].value, 0, SIZE);
        char * pos = strchr(buf, ':');
        strncpy(tmp[idx].key, buf, pos - buf);
        strncpy(tmp[idx].value, pos + 1, strlen(pos + 1) - 1);
        idx++;
    }

    *config = tmp;

    fclose(file);
    file = NULL;
}

char * get_value(char *key, CONFIG * config, int size)
{
    for (int idx = 0; idx < size; idx ++) {
        if (strcmp(config->key, key) == 0)
        {
            return config->value;
        }
        config++;
    }
    
    return NULL;
}