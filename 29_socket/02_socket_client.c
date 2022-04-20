#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main()
{
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    char ip[32] = "192.168.2.157";
    const char *target = (const char *)&addr.sin_addr.s_addr;
    inet_pton(AF_INET, target, ip);

    connect(socket_fd, (struct sockaddr *)&addr, sizeof addr);

    char chunk[1024] = {0};
    while (1)
    {
        // 写数据
        // int n = read(STDIN_FILENO, chunk, sizeof chunk);
        // write(socket_fd, chunk, n);

        // 读数据
        int n = read(socket_fd, chunk, sizeof chunk);
        write(STDOUT_FILENO, chunk, n);
    }

    close(socket_fd);

    return EXIT_SUCCESS;
}