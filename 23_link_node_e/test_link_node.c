#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "link_node.h"

typedef struct
{
    void *node;
    char name[32];
    int age;
} Person;

void print_person(void *data)
{
    Person *p = data;
    printf("%s - %d | ", p->name, p->age);
}

int compare_person(void *b, void *a)
{
    Person *p1 = a;
    Person *p2 = b;
    return strcmp(p1->name, p2->name) == 0 && p1->age == p2->age;
}

int main()
{
    LinkedList list = init();
    Person p1 = {NULL, "aaa", 10};
    Person p2 = {NULL, "bbb", 20};
    Person p3 = {NULL, "ccc", 30};
    Person p4 = {NULL, "ddd", 40};

    insert(list, &p1, -1);
    insert(list, &p2, -1);
    insert(list, &p3, 0);
    insert(list, &p4, -1);

    info(list, print_person);

    printf("删除 第三个元素 \n ");
    remove_by_pos(list, 1);
    info(list, print_person);
    printf("删除 ddd 元素 \n");
    Person target = {NULL, "ddd", 40};
    remove_by_value(list, &target, compare_person);
    info(list, print_person);
    printf("清空链表 \n");
    empty(list);
    info(list, print_person);
    printf("再插入 \n");
    insert(list, &p3, 0);
    insert(list, &p4, -1);
    info(list, print_person);
    destroy(list);
    info(list, print_person);
    insert(list, &p4, -1);
    return EXIT_SUCCESS;
}