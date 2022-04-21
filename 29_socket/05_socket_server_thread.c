#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <errno.h>
#include <pthread.h>

#include <string.h>

typedef struct _args
{
    int cfd;
    struct sockaddr_in *current;
} ARGS;

extern void *run(void *);

int main()
{
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1)
    {
        perror("create socket fialed:: ");
        return EXIT_FAILURE;
    }

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(8000);
    const char *p = (const char *)&server.sin_addr.s_addr;
    inet_pton(AF_INET, p, "127.0.0.1");

    bind(lfd, (struct sockaddr *)&server, sizeof server);

    listen(lfd, 128);
    printf("wait socket accept\n");
    ARGS *runtime;
    while (1)
    {
        runtime = malloc(sizeof(ARGS));
        socklen_t len = sizeof(struct sockaddr_in);
        runtime->current = malloc(len);
        int cfd;
    again:
        cfd = accept(lfd, (struct sockaddr *)runtime->current, &len);
        if (cfd < 0)
        {
            if ((errno == ECONNABORTED) || (errno == EINTR))
                goto again;
            else
            {
                perror("accept error:: ");
                exit(-1);
            }
        }
        runtime->cfd = cfd;
        pthread_t pthid;
        pthread_create(&pthid, &attr, run, runtime);
    }

    close(lfd);

    return EXIT_SUCCESS;
}

void *run(void *arg)
{
    ARGS *context = arg;
    char ip[16] = {0};
    printf("accept client ip:: %s", inet_ntop(AF_INET, &(context->current->sin_addr.s_addr), ip, sizeof ip));
    printf(" port:: %d\n", ntohs(context->current->sin_port));
    char chunk[1024];
    while (1)
    {
        memset(chunk, 0, sizeof chunk);
        int n = read(context->cfd, chunk, sizeof chunk);
        if (n < 0)
        {
            perror("read failed ::");
            break;
        }
        else if (n == 0)
        {
            printf("client close. \n");
            break;
        }
        else
        {
            write(STDOUT_FILENO, chunk, n);
            write(context->cfd, chunk, n);
        }
    }

    close(context->cfd);
    free(context->current);
    context->current = NULL;
    free(context);
    context = NULL;

    return NULL;
}