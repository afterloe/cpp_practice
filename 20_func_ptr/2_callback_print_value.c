#include <stdlib.h>
#include <stdio.h>

extern void print_int(void *);
extern void print_float(void *);
extern void print_person(void *);

typedef struct
{
    char name[32];
    int age;
} Person;

void to_string(void *data, void (*func)(void *))
{
    func(data);
}

void print_int(void *num)
{
    int *data = (int *)num;
    printf("%d \n", *data);
}

void print_float(void *num)
{
    float *data = (float *)num;
    printf("%f \n", *data);
}

void print_person(void *ptr)
{
    Person *p = (Person *)ptr;
    printf("my name is %s, i'm %d years old.\n", p->name, p->age);
}

int main()
{
    int a = 200;
    to_string(&a, print_int);
    float b = 3.14f;
    to_string(&b, print_float);
    Person p1 = {"afterloe", 23};
    to_string(&p1, print_person);
    return EXIT_SUCCESS;
}