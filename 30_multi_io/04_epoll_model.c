#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

#include <fcntl.h>
#include <errno.h>

#define MAX 1024

int main()
{
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd < 0)
    {
        perror("create socket file failed ::");
        return EXIT_FAILURE;
    }
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    // inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);
    server.sin_addr.s_addr = INADDR_ANY;
    bind(lfd, (struct sockaddr *)&server, sizeof server);
    listen(lfd, 128);

    printf("wait client. \n");
    int root = epoll_create(MAX);
    struct epoll_event list[MAX], first;
    first.data.fd = lfd;
    first.events = EPOLLIN;
    epoll_ctl(root, EPOLL_CTL_ADD, lfd, &first);

    int idx = 0;
    struct epoll_event *current = NULL;

    for (;;)
    {
        int ret = epoll_wait(root, list, MAX, -1);
        if (ret == -1)
        {
            perror("failed to wait socket. \n");
            break;
        }
        else if (ret == 0)
        {
            continue;
        }
        else
        {
            current = list;
            for (idx = 0; idx < ret; idx++)
            {
                if (current->data.fd == lfd && current->events & EPOLLIN)
                {
                    struct sockaddr_in client;
                    socklen_t len = sizeof client;
                    int cfd = accept(lfd, (struct sockaddr *)&client, &len);
                    if (cfd < 0)
                    {
                        perror("accept failed ::");
                        continue;
                    }
                    // 设置cfd 为非阻塞, 避免边缘触发时， read一直阻塞读取。
                    int model = fcntl(cfd, F_GETFL);
                    model |= O_NONBLOCK;
                    fcntl(cfd, F_SETFL, model);

                    char ip[16] = {0};
                    printf("client %s", inet_ntop(AF_INET, &client.sin_addr.s_addr, ip, sizeof ip));
                    printf(": %d\n", ntohs(client.sin_port));
                    struct epoll_event node;
                    node.data.fd = cfd;
                    // 设置 epoll 为 边缘触发 模式， 即 只触发一次。
                    // 默认 水平触发， 即 只要有数据就一直循环
                    node.events = EPOLLIN | EPOLLET;
                    epoll_ctl(root, EPOLL_CTL_ADD, cfd, &node);
                }
                else if (current->events & EPOLLIN)
                {
                    char buf[4] = {0};
                    for (;;)
                    {
                        // MSG_PEEK 表示读数据 不会删除缓冲区中的内容
                        int n = recv(current->data.fd, buf, sizeof buf, MSG_CMSG_CLOEXEC);
                        // int n = read(current->data.fd, buf, sizeof buf);
                        if (n < 0)
                        {
                            if (errno == EAGAIN)
                            {
                                // 缓冲区读取干净， 跳出本次循环。
                                break;
                            }
                            printf("client find error. \n");
                            epoll_ctl(root, EPOLL_CTL_DEL, current->data.fd, current);
                            close(current->data.fd);
                            break;
                        }
                        else if (n == 0)
                        {
                            printf("client closed. \n");
                            epoll_ctl(root, EPOLL_CTL_DEL, current->data.fd, current);
                            close(current->data.fd);
                            break;
                        }
                        else
                        {
                            write(STDOUT_FILENO, buf, n);
                            // send api, 0 表示一般速度， 1 表示紧急，一般设置0
                            send(current->data.fd, buf, n, 0);
                            // write(current->data.fd, buf, n);
                        }
                    }
                }

                current++;
            }
        }
    }

    close(lfd);
    return EXIT_SUCCESS;
}