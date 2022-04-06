#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _person
{
    char name[64];
    int age;

} Person;

typedef struct
{
    char name[32];
    int age;
} Person2;

int main()
{
    Person p1 = {"afterloe", 10};
    printf("%s -> %d \n", p1.name, p1.age);

    Person2 p2 = {"joe", 10};
    printf("%s -> %d \n", p2.name, p2.age);

    p2.age = 25;
    strcpy(p2.name, "joe_1"); // p2.name = "joe_1";
    printf("%s -> %d \n", p2.name, p2.age);

    Person *ptr = &p1;
    ptr->age = 30;
    strcpy(ptr->name, "afterloe_1");
    printf("%s -> %d \n", p1.name, p1.age);

    return EXIT_SUCCESS;
}