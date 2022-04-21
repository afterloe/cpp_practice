#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <wait.h>
#include <unistd.h>

int main()
{
    // 创建socket
    int sock_lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sock_lfd)
    {
        perror("socket create failed::");
        return EXIT_FAILURE;
    }

    // 绑定
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8000);

    // 绑定到 0.0.0.0
    // server.sin_addr.s_addr = INADDR_ANY;

    // 绑定到指定ip
    const char *addr_ptr = (const char *)&server.sin_addr.s_addr;
    char ip[16] = "127.0.0.1";
    inet_pton(AF_INET, addr_ptr, ip);
    bind(sock_lfd, (struct sockaddr *)&server, sizeof server);

    // 监听
    listen(sock_lfd, 128); // 连接数和被连接数的总和，一般设为128或 64
    printf("wait socket client accept. \n");
    // 连接
    struct sockaddr_in *current;
    while (1)
    {
        current = malloc(sizeof(struct sockaddr_in));
        socklen_t len = sizeof current;
        int sock_cfd = accept(sock_lfd, (struct sockaddr *)&current, &len);
        // fork
        pid_t pid = fork();
        if (pid < 0)
        {
            // 错误
            perror("fork process failed ::");
            _Exit(0);
        }
        if (pid == 0)
        {
            // 子进程
            close(sock_lfd);
            char ip[16] = {0};
            printf("client accept from %s", inet_ntop(AF_INET, &(current->sin_addr.s_addr), ip, sizeof ip));
            printf(":%d \n", ntohs(current->sin_port));
            char chunk[1024] = {0};
            while (1)
            {
                memset(chunk, 0, sizeof chunk);
                int n = read(sock_cfd, chunk, sizeof chunk);
                if (0 == n) 
                {
                    printf("client[pid=%d] exit.", getpid());
                    exit(0);
                }
                write(STDOUT_FILENO, chunk, n);
                write(sock_cfd, chunk, n);
            }
        }
        if (pid > 0)
        {
            // 主进程
            close(sock_cfd);
        }
    }
 
    // clsoe
    close(sock_lfd);

    // wait
    // 回收资源
    return EXIT_SUCCESS;
}