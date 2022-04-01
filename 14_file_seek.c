#include <stdlib.h>
#include <stdio.h>

int main()
{
    FILE *f = fopen("a.txt", "w");
    fputs("helloafterloe", f);

    fseek(f, -8, SEEK_END); // 以文件末尾，向左移动8个字符， 覆盖输出.
    fputc(' ', f);

    fclose(f);
    return 0;
}