#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int find_char(char *, char *);

int main()
{
    char *src = "abcdefghijklmnopqrstuvwxyz";
    int ret = find_char(src, "kl");
    if (-1 == ret)
    {
        printf("can't find any code from this str.");
        return EXIT_FAILURE;
    }
    printf("str is %d\n", ret);
    return EXIT_SUCCESS;
}

int find_char(char *src, char *sub)
{
    int index = -1;
    while ('\0' != *src)
    {
        if (*src != *sub)
        {
            src++;
            index++;
            continue;
        }
        char *tmp_src = src;
        char *tmp_sub = sub;
        while ('\0' != *tmp_sub)
        {
            if (*tmp_sub != *tmp_src)
            {
                src++;
                break;
            }
            tmp_src++;
            tmp_sub++;
            index++;
        }
        if (0 == *tmp_sub)
        {
            return index;
        }
    }
    return index;
}