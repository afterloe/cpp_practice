#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid = getpid();
    printf("befor fork:: %d\n", pid);
    pid = fork();
    printf("after fork:: %d\n", pid);

    return EXIT_SUCCESS;
}