#include <stdlib.h>
#include <stdio.h>

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

#endif

int main()
{
    LinkedList list = init();
    return EXIT_SUCCESS;
}

LinkedList init()
{
    struct linked_list *ptr = malloc(sizeof(struct linked_list));
    ptr->size = 0;
    ptr->header.next = NULL;

    return ptr;
}

void insert(LinkedList ptr, void * data, int pos)
{
    if (NULL == ptr)
    {
        return;
    }
    struct linked_list * list = ptr;
    if (pos < 0 || pos > list->size)
    {
        pos = list->size;
    }
    struct linked_node * current = list->header.next;
    for (int idx = 0; idx < pos; idx++)
    {
        current = current->next;
    }
}