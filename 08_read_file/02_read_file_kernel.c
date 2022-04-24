#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 1500

int main()
{
    char fileName[64] = "/home/afterloe/Projects/sync_tools/execute-20220419.log";
    printf("open file: %s\n", fileName);

    int fd = open(fileName, O_RDONLY);
    if (fd < 0)
    {
        perror("open file failed ::");
        return EXIT_FAILURE;
    }

    char buf[SIZE];
    memset(buf, 0, SIZE);
    int ret = -1;
    do
    {
        ret = read(fd, buf, SIZE);
        write(STDOUT_FILENO, buf, ret);
    } while (ret != 0);

    close(fd);

    return EXIT_SUCCESS;
}