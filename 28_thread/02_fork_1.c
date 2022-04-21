#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    pid_t pid;
    pid = fork();

    if (pid < 0)
    {
        printf("fork failed.");
        perror("");
    }

    if (0 == pid)
    {
        // 子进程
        for (int i = 0; i < 5; i++)
        {
            printf("son: do %d .\n", i);
            sleep(3);
        }

        exit(5);
    }
    else if (pid > 0)
    {
        // 父进程
        for (int i = 0; i < 5; i++)
        {
            printf("father: do %d .\n", i);
        }
        int status;
        pid_t flag = wait(&status);
        if (WIFEXITED(status))
        {
            printf("子进程正常退出. \n");
            // 获取 子进程 exit 的code
            printf("exit code=%d \n", WEXITSTATUS(status));
        }
    }

    return EXIT_SUCCESS;
}