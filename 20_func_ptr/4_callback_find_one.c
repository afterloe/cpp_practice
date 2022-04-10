#include <stdlib.h>
#include <stdio.h>

#include <string.h>

int find_that(void *arr, void *that, int ele_size, int len, int (*compare)(void *, void *))
{
    char *ptr = arr;
    for (int idx = 0; idx < len / ele_size; idx++)
    {
        char *current = ptr + idx * ele_size;
        if (compare(current, that))
        {
            return idx;
        }
    }

    return -1;
}

typedef struct
{
    char name[32];
    int age;
} Person;

int compare_person(void *a, void *b)
{
    Person *p1 = (Person *)a;
    Person *p2 = (Person *)b;

    if (strcmp(p1->name, p2->name) == 0 && p1->age == p2->age)
    {
        return 1;
    }
    return 0;
}

int compare_int(void *a, void *b)
{
    int *x, *y;
    x = (int *)a, y = (int *)b;
    if (*x == *y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void test01()
{
    int int_arr[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int idx;
    int target = 3;
    idx = find_that(int_arr, &target, sizeof(int), sizeof int_arr, compare_int);
    if (-1 != idx)
    {
        printf("find %d in int_arr[%d] \n", target, idx);
    }
    else
    {
        printf("can't find %d in int_arr\n", target);
    }
}

void test02()
{
    Person people[3] = {
        {"afterloe", 32},
        {"joe", 19},
        {"grace", 5}};
    Person target =  {"joe", 19};
    Person target_1 = {"afterloe", 22};
    int idx;
    idx = find_that(people, &target, sizeof(Person), sizeof people, compare_person);
    printf("%d \n", idx);
    idx = find_that(people, &target_1, sizeof(Person), sizeof people, compare_person);
    printf("%d \n", idx);
}

int main()
{
    test01();
    test02();
    return EXIT_SUCCESS;
}