#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

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
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);
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
                if (current->data.fd == lfd)
                {
                    struct sockaddr_in client;
                    socklen_t len = sizeof client;
                    int cfd = accept(lfd, (struct sockaddr *)&client, &len);
                    if (cfd < 0)
                    {
                        perror("accept failed ::");
                        continue;
                    }
                    char ip[16] = {0};
                    printf("socket %s", inet_ntop(cfd, &client.sin_addr.s_addr, ip, sizeof ip));
                    printf(": %d\n", ntohs(client.sin_port));
                    struct epoll_event node;
                    node.data.fd = cfd;
                    node.events = EPOLLIN;
                    epoll_ctl(root, EPOLL_CTL_ADD, cfd, &node);
                }
                else
                {
                    char buf[1500] = {0};
                    int n = read(current->data.fd, buf, sizeof buf);
                    if (n <= 0)
                    {
                        printf("client closed or find error. \n");
                        epoll_ctl(root, EPOLL_CTL_DEL, current->data.fd, current);
                        close(current->data.fd);
                        continue;
                    }
                    else
                    {
                        write(STDOUT_FILENO, buf, n);
                        write(current->data.fd, buf, n);
                    }
                }

                current++;
            }
        }
    }

    close(lfd);
    return EXIT_SUCCESS;
}