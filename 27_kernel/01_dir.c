#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int main()
{
    char pwd[64];
    getcwd(pwd, sizeof pwd);
    printf("old PWD: %s\n", pwd);

    char new_path[64] = "/tmp";
    int flag = chdir(new_path);
    if (-1 == flag)
    {
        perror("chdir failed: ");
    }

    getcwd(pwd, sizeof pwd);
    printf("new PWD: %s\n", pwd);

    DIR *dir = opendir(pwd);
    if (NULL == dir)
    {
        perror("open dir failed: ");
    }
    printf("open %s success. \n", pwd);

    struct dirent *entry = NULL;

    while (NULL != (entry = readdir(dir)))
    {
        printf("%s \n", entry->d_name);
    }

    flag = closedir(dir);
    if (0 != flag)
    {
        perror("close dir failed: ");
    }
    printf("关闭目录成功 . \n");

    return EXIT_SUCCESS;
}