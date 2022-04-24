#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <wait.h>
#include <string.h>

#include <sys/epoll.h>

int main()
{
    // 0 读 1写
    int fd_pipe[2] = {0};
    int ret = pipe(fd_pipe);
    if (ret < 0)
    {
        perror("pip created failed ::");
        return EXIT_FAILURE;
    }
    int pid = fork();
    if (pid < 0)
    {
        perror("fork failed ::");
        return EXIT_FAILURE;
    }
    else if (pid == 0)
    {
        // 子进程
        close(fd_pipe[0]);
        char c = 'a';
        char chunk[16] = {0};
        for (;;)
        {
            memset(chunk, c++, sizeof chunk);
            write(fd_pipe[1], chunk, sizeof chunk);
            sleep(3);
        }
    }
    else if (pid > 0)
    {
        // 父进程
        close(fd_pipe[1]);

        int root = epoll_create(1);
        struct epoll_event current, list[1];
        current.data.fd = fd_pipe[0];
        current.events = EPOLLIN;
        epoll_ctl(root, EPOLL_CTL_ADD, fd_pipe[0], &current);
        for (;;)
        {
            int ret = epoll_wait(root, list, 1, -1);
            if (ret == 1)
            {
                char buf[128] = {0};
                int n = read(fd_pipe[0], buf, sizeof buf);
                if (n == 0)
                {
                    close(fd_pipe[0]);
                    epoll_ctl(root, EPOLL_CTL_DEL, fd_pipe[0], &current);
                    break;
                } else 
                {
                    write(STDOUT_FILENO, buf, n);
                }
            }
        }

        close(root);
        waitpid(pid, NULL, WNOHANG);
    }

    return EXIT_SUCCESS;
}