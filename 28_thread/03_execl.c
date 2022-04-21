#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

int main()
{
    printf("befor excel");
    // ls /tmp -l
    int pid = execl("/bin/ls", "ls", "/tmp", "-l", NULL);
    printf("pid = %d\n", pid);

    return EXIT_SUCCESS;
}