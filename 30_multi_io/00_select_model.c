#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <sys/select.h>

int main()
{
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (0 == -1)
    {
        perror("socket open failed ::");
        return EXIT_FAILURE;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    // const char * addr_ptr = (const char *) &server.sin_addr.s_addr;
    // inet_pton(AF_INET, "127.0.0.1", addr_ptr);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);

    // 设置端口复用
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);

    bind(lfd, (struct sockaddr *)&server, sizeof server);

    listen(lfd, 128);
    printf("wait socket client accept.\n");

    // 设置SELECT API
    // 设置最大文件是 socket文件
    int maxfd = lfd;
    fd_set oldset, rset;

    // 设置SELECT队列为 0
    FD_ZERO(&oldset);
    FD_ZERO(&rset);

    // 将lfd添加到oldset内
    FD_SET(lfd, &oldset);
    while (1)
    {
        // 将oldset赋值给需要监听的集合rset
        rset = oldset;
        int n = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (n < 0)
        {
            perror("select listen failed :: ");
            break;
        }
        else if (n == 0)
        {
            // 监听没有变化
            continue;
        }
        else // 监听到有文件变化
        {
            // lfd变化 代表有新的连接
            if (FD_ISSET(lfd, &rset))
            {
                struct sockaddr_in client;
                socklen_t len = sizeof client;
                char ip[16] = {0};
                // 提取连接
                int cfd = accept(lfd, (struct sockaddr *)&client, &len);
                printf("client %s", inet_ntop(AF_INET, &client.sin_addr.s_addr, ip, sizeof ip));
                printf("port: %d accept!\n", ntohs(client.sin_port));
                // 添加cfd到oldset集合，下次监听
                FD_SET(cfd, &oldset);
                // 更新maxfd
                if (cfd > maxfd)
                {
                    maxfd = cfd;
                }
                // 如果只有lfd变化，continue
                if (--n == 0)
                {
                    continue;
                }
            }

            // 遍历 lfd 之后的文件描述符是否在rset集合内
            // 如果在，则cfd变化
            for (int i = lfd + 1; i <= maxfd; i++)
            {
                if (FD_ISSET(i, &rset))
                {
                    char chunk[1500] = {0};
                    int ret = read(i, chunk, sizeof chunk);
                    if (ret < 0)
                    {
                        perror("read cfd failed ::");
                        close(i);
                        FD_CLR(i, &oldset);
                        continue;
                    }
                    else if (ret == 0)
                    {
                        printf("client close. \n");
                        close(i);
                        FD_CLR(i, &oldset);
                    }
                    else
                    {
                        write(STDOUT_FILENO, chunk, ret);
                        write(i, chunk, ret);
                    }
                }
            }
        }
    }

    close(lfd);

    return EXIT_SUCCESS;
}