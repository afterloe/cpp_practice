#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int flag = open("../01_hello.cpp", O_RDONLY);
    printf("open flag: %d\n", flag);
    if (-1 == flag)
    {
        perror("failed ::");
        return EXIT_FAILURE;
    }
    close(flag);
    return EXIT_SUCCESS;
}