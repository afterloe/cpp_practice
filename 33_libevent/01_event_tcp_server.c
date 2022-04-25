#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <event.h>

void cfdcb(int cfd, short event, void *args)
{
    char buf[1500] = {0};
    int n = recv(cfd, buf, sizeof buf, 0);
    if (n <= 0)
    {
        printf("client close\n");
        // 数组实现下树
        // event_del();
        // event_free();
    }
    else
    {
        write(STDOUT_FILENO, buf, n);
        write(cfd, buf, n);
    }
}

void lfdcb(int lfd, short event, void *args)
{
    struct event_base *root = (struct event_base *)args;
    // 不提取客户端信息
    int cfd = accept(lfd, NULL, NULL);
    struct evnet *ev = event_new(root, cfd, EV_READ | EV_PERSIST, cfdcb, NULL);
    event_add(ev, NULL);
}

int main()
{
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);
    bind(lfd, (struct sockaddr *)&server, sizeof server);
    listen(lfd, 128);

    struct event_base *root = event_base_new();
    struct event *ev = event_new(root, lfd, EV_READ | EV_PERSIST, lfdcb, root);
    event_add(ev, NULL);
    event_base_dispatch(root);

    close(lfd);
    event_base_free(root);

    return EXIT_SUCCESS;
}