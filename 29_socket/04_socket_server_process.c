#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

#include <unistd.h>

extern void free_process(int);

int main()
{
    // 创建信号监听
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

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
        int sock_cfd = accept(sock_lfd, (struct sockaddr *)current, &len);
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
            unsigned short p = ntohs(current->sin_port);
            printf("client accept from %s", inet_ntop(AF_INET, &(current->sin_addr.s_addr), ip, sizeof ip));
            printf(":%d \n", p);
            char chunk[1024] = {0};
            while (1)
            {
                memset(chunk, 0, sizeof chunk);
                int n = read(sock_cfd, chunk, sizeof chunk);
                if (0 == n)
                {
                    free(current);
                    current = NULL;
                    close(sock_cfd);
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
            // 回收资源
            // step 1 - 注册信号回调函数
            struct sigaction act;
            act.sa_flags = 0;
            act.sa_handler = free_process;
            sigemptyset(&act.sa_mask);
            sigaction(SIGCHLD, &act, NULL);
            sigprocmask(SIG_UNBLOCK, &set, NULL);

        }
    }

    // clsoe
    close(sock_lfd);

    return EXIT_SUCCESS;
}

void free_process(int sig)
{
    pid_t pid;
    while (1)
    {
        pid = waitpid(-1, NULL, WNOHANG);
        if (pid <= 0)
        {
            // <0 子进程全部退出
            // =0 没有进程退出
            break;
        }
        else
        {
            printf("child pid[%d] exit. \n", pid);
        }
    }
}