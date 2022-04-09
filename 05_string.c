#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int find_char(char *, char *);
extern void reversal(char *);

int main()
{
    char src[] = "abcdefghijklmnopqrstuvwxyz";
    printf("src = [%s]\n", src);
    reversal(src);
    printf("reversal = [%s]\n", src);

    char sub[] = "kl";
    int ret = find_char(src, sub);
    if (-1 == ret)
    {
        printf("can't find any code from this str.");
        return EXIT_FAILURE;
    }
    printf("sub str is %d\n", ret);

    char count[32] = {0};
    int val = 4;
    sprintf(count, "%d", val);
    printf("buf=[%s]\n", count);
    return EXIT_SUCCESS;
}

void reversal(char *str)
{
    int start = 0;
    int end = strlen(str) - 1;
    while (start < end)
    {
        str[start] = str[start] ^ str[end];
        str[end] = str[start] ^ str[end];
        str[start] = str[start] ^ str[end];
        start++;
        end--;
    }

    // char *start = str;
    // char *end = str + strlen(str) - 1;
    // while (start < end)
    // {
    //     start = *start ^ *end;
    //     end = *start ^ *end;
    //     start = *start ^ *end;
    //     start++;
    //     end--;
    // }
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