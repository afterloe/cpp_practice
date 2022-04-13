#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"

typedef struct
{
    char name[32];
    int age;
} Person;

void print_person(void *data)
{
    Person *p = data;
    printf("name=%s,age=%d ", p->name, p->age);
}

int compare_person(void *one, void *two)
{
    Person *p1 = one;
    Person *p2 = two;
    return strcmp(p1->name, p2->name) == 0 && p1->age == p2->age;
}

void print_int(void *data)
{
    int *num = (int *)data;
    printf("%d ", *num);
}

int main()
{
    Person p1 = {"aaa", 10};
    Person p2 = {"bbb", 20};
    Person p3 = {"ccc", 30};
    Person p4 = {"ddd", 40};
    Person p5 = {"eee", 50};
    ArrayList arr = init(0);
    insert(arr, &p1, 0);
    insert(arr, &p2, 0);
    insert(arr, &p3, 21);
    insert(arr, &p4, -2);
    insert(arr, &p5, 0);
    info(arr, print_person);
    remove_by_pos(arr, 0);
    info(arr, print_person);
    Person del = {"ddd", 40};
    remove_by_data(arr, &del, compare_person);
    info(arr, print_person);
    emptry(arr);
    int a = 10;
    int b = 20;
    int c = 30;
    insert(arr, &a, -1);
    insert(arr, &b, -1);
    insert(arr, &c, -1);
    info(arr, print_int);
    destroy(arr);
    // insert(arr, &c, -1);
    return EXIT_SUCCESS;
}