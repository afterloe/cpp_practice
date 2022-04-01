#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[32];
};

int main()
{
    struct Student students[3] = {{1101, "afterloe"}, {1102, "joe"}, {1102, "Grace"}};
    for (int i=0; i<3; i++) {
        printf("%d -> %s\n", students[i].id, students[i].name);
    }

    return -1;
}