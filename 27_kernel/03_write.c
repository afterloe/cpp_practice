#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

int main()
{
    char chunk[1024] = {0};

    while(1)
    {
        int n = read(STDIN_FILENO, chunk, sizeof chunk);
        printf("read from keyboard: %d \n", n);

        write(STDOUT_FILENO, chunk, n);
    }

    return EXIT_SUCCESS;
}