#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef __link_node
#define __link_node

struct linked_node
{
    struct linked_node *next;
};

struct linked_list
{
    struct linked_node header;
    int size;
};

typedef void *LinkedList;

extern LinkedList init();
extern void insert(LinkedList, void *, int);
extern void info(LinkedList, void (*)(void *));
extern void remove_by_pos(LinkedList, int);
extern void remove_by_value(LinkedList, void *, int (*)(void *, void *));
extern void empty(LinkedList);

#endif

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

    return EXIT_SUCCESS;
}

LinkedList init()
{
    struct linked_list *ptr = malloc(sizeof(struct linked_list));
    ptr->size = 0;
    ptr->header.next = NULL;

    return ptr;
}

void insert(LinkedList ptr, void *data, int pos)
{
    if (NULL == ptr)
    {
        return;
    }
    struct linked_list *list = ptr;
    if (pos < 0 || pos > list->size)
    {
        pos = list->size;
    }
    struct linked_node *node = data;
    struct linked_node *current = &list->header;
    for (int idx = 0; idx < pos; idx++)
    {
        current = current->next;
    }

    node->next = current->next;
    current->next = node;

    list->size++;
}

void info(LinkedList ptr, void (*print_fun)(void *))
{
    if (NULL == ptr)
    {
        return;
    }
    struct linked_list *list = ptr;
    struct linked_node *current = &list->header;
    printf("\nsize :: %d [", list->size);
    for (int idx = 0; idx < list->size; idx++)
    {
        current = current->next;
        print_fun(current);
    }
    printf("]\n");
}

void remove_by_pos(LinkedList ptr, int pos)
{
    if (NULL == ptr)
    {
        return;
    }
    struct linked_list *list = ptr;
    if (pos < 0 || pos > list->size)
    {
        return;
    }

    struct linked_node *prv = &list->header;
    struct linked_node *current = prv->next;
    for (int idx = 0; idx < pos; idx++)
    {
        prv = current;
        current = current->next;
    }
    prv->next = current->next;
    current = NULL;
    list->size--;
}

void remove_by_value(LinkedList ptr, void *data, int (*compare)(void *, void *))
{
    if (NULL == ptr)
    {
        return;
    }

    struct linked_list *list = ptr;
    if (NULL == data)
    {
        return;
    }
    struct linked_node *current = &list->header;
    for (int idx = 0; idx < list->size; idx++)
    {
        current = current->next;
        if (compare(current, data))
        {
            remove_by_pos(ptr, idx);
            return;
        }
    }
}

void empty(LinkedList ptr)
{
    if (NULL == ptr)
    {
        return;
    }

    struct linked_list *list = ptr;
    list->size = 0;
    struct linked_node *current = &list->header;
    current->next = NULL;
}