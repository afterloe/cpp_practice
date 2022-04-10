#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char name[32];
    int age;
} Person;

void print_array(void *ptr, int ele_size, int len, void (*func)(void *))
{
    char *p = ptr;
    printf("\n[");
    for (int idx = 0; idx < len / ele_size; idx++)
    {
        char *addr = p + idx * ele_size;
        func(addr);
    }
    printf("]\n");
}

void print_int(void *ptr)
{
    int *data = (int *)ptr;
    printf("%d ", *data);
}

void print_float(void *ptr)
{
    float *data = (float *)ptr;
    printf("%.3f ", *data);
}

void print_person(void *ptr)
{
    Person *p = (Person *)ptr;
    printf("%s -> %d", p->name, p->age);
}

void test01()
{
    int values[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print_array(values, sizeof(int), sizeof values, print_int);

    float fl_values[4] = {3.14f, 4.452f, 0.723f, 8.92f};
    print_array(fl_values, sizeof(float), sizeof fl_values, print_float);

    Person people[3] = {
        {"afterloe", 32},
        {"joe", 19},
        {"grace", 5}};
    print_array(people, sizeof(Person), sizeof people, print_person);
}

int main()
{
    test01();
    return EXIT_SUCCESS;
}