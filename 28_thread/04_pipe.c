#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    // 管道 0 - read, 1 - write
    int fd_pipe[2] = {0};
    if (pipe(fd_pipe) < 0)
    {
        perror("create pip failed: ");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (0 == pid)
    {
        // 子进程
        char buf[] = "i'm son!";
        write(fd_pipe[1], buf, strlen(buf));

        _exit(0);
    }
    else if (0 < pid)
    {
        // 父进程
        wait(NULL); // 等待子进程结束
        char str[50] = {0};
        read(fd_pipe[0], str, sizeof str);

        printf("receive str=[%s]\n", str);
    }

    return EXIT_SUCCESS;
}