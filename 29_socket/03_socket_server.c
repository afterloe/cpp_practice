#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    int socket_lfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8000);

    const char *addr_ptr = (const char *)&addr.sin_addr.s_addr;
    char addr_str[64] = "127.0.0.1";
    inet_pton(AF_INET, addr_ptr, addr_str);

    bind(socket_lfd, (struct sockaddr *)&addr, sizeof addr);

    listen(socket_lfd, 128);
    printf("socket server init.\n");

    printf("wait accept ! \n");
    struct sockaddr_in client;
    socklen_t len = sizeof client;
    int cfd = accept(socket_lfd, (struct sockaddr *)&client, &len);
    char client_ip[16];
    printf("accept ip:: %s", inet_ntop(AF_INET, &client.sin_addr.s_addr, client_ip, sizeof client_ip));
    printf(" port:: %d \n", ntohs(client.sin_port));

    char chunk[1024];
    while (1)
    {
        memset(chunk, 0, sizeof chunk);
        int n = read(cfd, chunk, sizeof chunk);
        if (0 == n)
        {
            printf("socket closed.\n");
            break;
        }
        write(STDOUT_FILENO, chunk, n);

        write(cfd, chunk, n);
    }

    close(cfd);
    close(socket_lfd);

    return EXIT_SUCCESS;
}