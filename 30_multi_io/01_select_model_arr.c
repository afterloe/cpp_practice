#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>

#define HANDLER 128

int main()
{
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd < 1)
    {
        perror("create socket failed ::");
        return EXIT_FAILURE;
    }
    // 开启端口复用
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);

    // 设置监听属性
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);

    bind(lfd, (struct sockaddr *)&server, sizeof server);
    listen(lfd, HANDLER);
    printf("server inited. wait client accept. \n");

    // 设置select内容
    fd_set listened, changed;
    int maxFID = lfd, current;
    FD_ZERO(&listened);
    FD_ZERO(&changed);
    FD_SET(lfd, &listened);
    while (1)
    {
        changed = listened;
        current = select(maxFID + 1, &changed, NULL, NULL, NULL);
        if (current < 0)
        {
            perror("select failed ::");
            break;
        }
        else if (0 == current)
        {
            continue;
        }
        else
        {
            if (FD_ISSET(lfd, &changed))
            {
                struct sockaddr_in client;
                socklen_t len = sizeof client;
                char ip[16] = {0};
                int cfd = accept(lfd, (struct sockaddr *)&client, &len);
                printf("client %s:", inet_ntop(AF_INET, &client.sin_addr.s_addr, ip, sizeof ip));
                printf("%d\n", ntohs(client.sin_port));
                FD_SET(cfd, &listened);
                if (cfd > maxFID)
                {
                    maxFID = cfd;
                }
                if (--current == 0)
                {
                    continue;
                }
            }

            for (int i = lfd + 1; i < maxFID; i++)
            {
                if (FD_ISSET(i, &changed))
                {
                    char buf[1500] = {0};
                    int ret = read(i, buf, 1500);
                    if (0 == ret)
                    {
                        printf("client leave. \n");
                        close(i);
                        FD_CLR(i, &changed);
                    }
                    else if (0 < ret)
                    {
                        write(STDOUT_FILENO, buf, ret);
                    }
                }
            }
        }
    }

    close(lfd);

    return EXIT_SUCCESS;
}