#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// 测试用 nc -u 127.1 8888
int main()
{
    // UDP 使用 dgram 参数
    int lfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in domain;
    domain.sin_family = AF_INET;
    domain.sin_port = htons(8888);
    // inet_pton(AF_INET, "127.0.0.1", &domain.sin_addr.s_addr);
    // 该函数任意地址等同于上面，但是只支持ipv4
    domain.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ret = bind(lfd, (struct sockaddr *)&domain, sizeof domain);
    if (ret < 0)
    {
        perror("bind failed ::");
        return EXIT_FAILURE;
    }
    char buf[1500] = {0};
    struct sockaddr_in cli;
    socklen_t len = sizeof cli;
    // 读数据
    for (;;)
    {
        memset(buf, 0, sizeof buf);
        int n = recvfrom(lfd, buf, sizeof buf, 0, (struct sockaddr *)&cli, &len);
        if (n < 0)
        {
            perror("recv msg failed ::");
            break;
        }
        else
        {
            write(STDOUT_FILENO, buf, n);
            sendto(lfd, buf, n, 0, (struct sockaddr *)&cli, len);
        }
    }

    close(lfd);

    return EXIT_SUCCESS;
}