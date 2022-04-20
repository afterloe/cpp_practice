#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
    char name[64] = "/home/afterloe/Opts/usb_simulation/config.ini.example";
    printf("file:: %s \n", name);
    struct stat buf;
    int file_stat = stat(name, &buf);

    if (S_ISREG(buf.st_mode))
    {
        printf("文件类型:: 普通文件\n");
    }

    // 判断是否是文件夹
    // if (S_ISDIR(buf.st_mode))
    // {

    // }

    return EXIT_SUCCESS;
}