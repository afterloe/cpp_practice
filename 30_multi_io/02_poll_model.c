#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include <poll.h>

#define MAX_SIZE 1024
#define STR_CHUNK_SIZE 1500

int main()
{
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd < 0)
    {
        perror("failed to open socket ::");
        return EXIT_FAILURE;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr.s_addr);
    int opt = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);

    bind(lfd, (struct sockaddr *)&server, sizeof server);
    listen(lfd, 128);

    printf("wait client accept. \n");

    struct pollfd *list = malloc(sizeof(struct pollfd) * MAX_SIZE), *current = NULL;
    char *chunk = malloc(STR_CHUNK_SIZE);
    int idx = -1, maxIDX = -1, ret = -1;
    for (idx = 0; idx < MAX_SIZE; idx++)
    {
        list[idx].fd = -1;
    }

    list[0].fd = lfd;
    list[0].events = POLLIN;
    maxIDX = 0;

    for (;;)
    {
        ret = poll(list, maxIDX + 1, -1);
        if (list[0].revents & POLLIN)
        {
            struct sockaddr_in client;
            socklen_t len = sizeof client;
            int cfd = accept(lfd, (struct sockaddr *)&client, &len);
            char ip[16] = {0};
            printf("client %s", inet_ntop(AF_INET, &client.sin_addr.s_addr, ip, sizeof ip));
            printf(": %d accept.\n", ntohs(client.sin_port));

            for (idx = 0; idx < MAX_SIZE; idx++)
            {
                if (list[idx].fd < 0)
                {
                    list[idx].fd = cfd;
                    break;
                }
            }

            if (idx == MAX_SIZE)
            {
                printf("too many clients");
            }

            list[idx].events = POLLIN;
            if (idx > maxIDX)
            {
                maxIDX = idx;
            }
            if (--ret == 0)
            {
                continue;
            }
        }
        current = list;
        for (idx = 0; idx <= maxIDX; idx++)
        {
            if (current->revents & POLLIN)
            {
                memset(chunk, 0, STR_CHUNK_SIZE);
                int n = read(current->fd, chunk, STR_CHUNK_SIZE);
                if (n == 0)
                {
                    printf("client close link. \n");
                    close(current->fd);
                    current->fd = -1;
                }
                else
                {
                    write(STDOUT_FILENO, chunk, n);
                    write(current->fd, chunk, n);
                }
            }
            current++;
        }
    }

    free(chunk);
    chunk = NULL;
    free(list);
    list = NULL;

    close(lfd);

    return EXIT_SUCCESS;
}