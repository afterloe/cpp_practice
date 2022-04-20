#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

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
    return EXIT_SUCCESS;
}