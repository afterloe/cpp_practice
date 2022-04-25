#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int lfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (lfd < 0)
    {
        perror("sock create failed ::");
        return EXIT_FAILURE;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);
    char buf[1500] = {0};
    for (;;)
    {
        memset(buf, 0, sizeof buf);
        int n = read(STDIN_FILENO, buf, sizeof buf);
        if (n == 0)
        {
            printf("enter F4.\n");
            break;
        }
        sendto(lfd, buf, n, 0, (struct sockaddr *)&server, sizeof server);
        memset(buf, 0, sizeof buf);
        n = recvfrom(lfd, buf, sizeof buf, 0, NULL, 0);
        if (n <= 0)
        {
            printf("recv msg failed. \n");
            break;
        }
        write(STDOUT_FILENO, buf, n);
    }

    close(lfd);

    return EXIT_SUCCESS;
}