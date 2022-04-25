#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <stddef.h>

int main()
{
    char file[16] = "foo.socket";
    int lfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (lfd < 0)
    {
        perror("create socket failed ::");
        return EXIT_SUCCESS;
    }

    struct sockaddr_un un;
    un.sun_family = AF_UNIX;
    sprintf(un.sun_path, "%s%05d", "/tmp/", getpid());
    int len = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

    unlink(un.sun_path);
    int flag = bind(lfd, (struct sockaddr *)&un, len);
    if (flag < 0)
    {
        perror("bind failed ::");
        return EXIT_FAILURE;
    }

    memset(&un, 0, sizeof un);
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, file);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(file);
    flag = connect(lfd, (struct sockaddr *)&un, len);
    if (flag < 0)
    {
        perror("conn failed ::");
        return EXIT_FAILURE;
    }
    char buf[1500];
    for (;;)
    {
        memset(buf, 0, sizeof buf);
        int n = read(STDIN_FILENO, buf, sizeof buf);
        if (n <= 0)
        {
            break;
        }
        send(lfd, buf, n, 0);
        memset(buf, 0, sizeof buf);
        n = recv(lfd, buf, sizeof buf, 0);
        if (n == 0)
        {
            break;
        }
        write(STDOUT_FILENO, buf, n);
    }

    close(lfd);

    return EXIT_SUCCESS;
}