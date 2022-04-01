#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

int main()
{
    struct stat *status = (struct stat *)malloc(sizeof(struct stat));
    if (-1 == stat("a.txt", status))
    {
        perror("[ERROR]");
        return 0;
    }

    printf("files is %ld bytes.\n", status->st_size);

    rename("a.txt", "b.txt");
    printf("rename file success.\n");

    remove("b.txt");
    printf("file has been del.\n");

    return 0;
}