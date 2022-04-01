#include <stdio.h>
#include <stdlib.h>

struct Student
{
    int id;
    char name[32];
};

int main()
{
    struct Student students[3] = {{1101, "afterloe"}, {1102, "joe"}, {1102, "Grace"}};
    for (int i = 0; i < 3; i++)
    {
        printf("%d -> %s\n", students[i].id, students[i].name);
    }

    FILE *f = fopen("a.txt", "w");

    if (NULL == f)
    {
        perror("");
        return -1;
    }

    fwrite(students, sizeof(students), 3, f);
    printf("success.\n");
    fclose(f);

    return 0;
}