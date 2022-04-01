#include <stdio.h>
#include <stdlib.h>

typedef struct Student
{
    int id;
    char name[32];
} Student;

extern void obj2file(const char *);
extern void file2obj(const char *);

int main()
{
    // obj2file("a.txt");
    file2obj("a.txt");
    return 0;
}

void file2obj(const char *file_name)
{
    Student serialze[3];
    FILE *f = fopen(file_name, "r");
    if (NULL == f)
    {
        perror("");
        return;
    }
    int count = fread(serialze, sizeof(Student), 3, f);
    printf("read %d object from file\n", count);
    for (int i=0; i< 3; i++){
        printf("%d -> %s\n", serialze[i].id, serialze[i].name);
    }
    return;
}

void obj2file(const char *file_name)
{
    Student students[3] = {{1101, "afterloe"}, {1102, "joe"}, {1102, "Grace"}};
    FILE *f = fopen(file_name, "w");

    if (NULL == f)
    {
        perror("");
        return;
    }

    fwrite(students, sizeof(students), 3, f);
    printf("success.\n");
    fclose(f);
}