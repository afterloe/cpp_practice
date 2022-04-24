#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>

int main()
{
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd < 1)
    {
        perror("create socket failed ::");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}