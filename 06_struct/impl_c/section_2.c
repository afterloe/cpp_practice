#include <stdlib.h>
#include <stdio.h>

#include <string.h>

typedef struct
{
    char *name;
    int age;
} Person;

extern void allocate_memory(Person **);
extern void printf_person(const Person *);
extern void free_memory(Person **);

int main()
{
    Person *ptr = NULL;
    allocate_memory(&ptr);

    ptr->age = 10;
    strcpy(ptr->name, "afterloe");

    printf_person(ptr);
    free_memory(&ptr);
    return EXIT_SUCCESS;
}

void allocate_memory(Person **ptr)
{
    Person *tmp = (Person *)malloc(sizeof(Person));
    tmp->name = (char *)malloc(32);
    *ptr = tmp;
}

void printf_person(const Person *ptr)
{
    printf("person named %s, age is %d.\n", ptr->name, ptr->age);
}

void free_memory(Person **ptr)
{
    if (NULL == ptr || NULL == *ptr)
    {
        perror("hase free.");
        return;
    }

    free((*ptr)->name);
    (*ptr)->name = NULL;

    free(*ptr);
    *ptr = NULL;
}