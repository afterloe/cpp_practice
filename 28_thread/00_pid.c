#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h>

int main()
{
    int pid = -1;
    pid = getpid();
    if (-1 == pid)
    {
        perror("fetch pid filed: ");
    }
    printf("pid is %d \n", pid);

    int ppid = -1;
    ppid = getppid();
    if (-1 == ppid)
    {
        perror("fetch ppid failed: ");
    }
    printf("ppid is %d\n", ppid);

    int pgid = -1;
    pgid = getpgid(pid);
    if (-1 == pgid)
    {
        perror("fetch group id failed: ");
    }
    printf("pgid is %d\n", pgid);

    return EXIT_SUCCESS;
}