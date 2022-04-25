#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <unistd.h>

#include <stddef.h>
#include <sys/socket.h>
#include <sys/un.h>

int main()
{
    char file[16] = "foo.socket";
    int lfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (lfd < 0)
    {
        perror("create udp server failed ::");
        return EXIT_FAILURE;
    }
    unlink(file);
    struct sockaddr_un server;
    server.sun_family = AF_UNIX;
    strcpy(server.sun_path, file);
    int len = offsetof(struct sockaddr_un, sun_family) + strlen(file);
    bind(lfd, (struct sockaddr *)&server, sizeof server);
    printf("wait client to accept \n");
    listen(lfd, 128);

    for (;;)
    {
        struct sockaddr_un client;
        socklen_t len = sizeof client;
        int cfd = accept(lfd, (struct sockaddr *)&client, &len);
        if (cfd < 0)
        {
            perror("accept uds client failed ::");
            break;
        }

        char buf[1500] = {0};
        memset(buf, 0, sizeof buf);
        int n = recv(cfd, buf, sizeof buf, 0);
        if (n == 0)
        {
            printf("client close.\n");
            break;
        }
        write(STDOUT_FILENO, buf, n);
        send(cfd, buf, n, 0);
    }

    close(lfd);

    return EXIT_SUCCESS;
}