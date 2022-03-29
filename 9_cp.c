#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *src = fopen("a.txt", "r");
    FILE *dst = fopen("copy.txt", "w");
    if (NULL == src || NULL == dst)
    {
        perror("no such file, src, dst");
        return -1;
    }
    int count = 0;
    while (!feof(src))
    {
        char ch = fgetc(src);
        if (EOF != ch)
        {
            fputc(ch, dst);
            count++;
        }
    }
    printf("copy file success, %d byte \n", count);
    fclose(src);
    fclose(dst);
    system("pause");
    return 0;
}