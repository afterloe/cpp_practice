#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

int main()
{
    int fd[2];

    int ret = pipe(fd);
    if (-1 == ret)
    {
        perror("create pipe failed:: ");
    }

    // _PC_PIPE_BUF，查看管道缓冲区大小
    // _PC_NAME_MAX，文件名字字节数的上限
    long num = fpathconf(fd[0], _PC_PIPE_BUF);
    long max = fpathconf(fd[0], _PC_NAME_MAX);

    printf("fd num is %ld, size is %ld \n", num, max);

    return EXIT_SUCCESS;
}