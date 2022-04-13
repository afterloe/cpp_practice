#include <stdlib.h>
#include <stdio.h>

#include "link_node.h"

struct linked_node
{
    struct linked_node *next;
};

struct linked_list
{
    struct linked_node header;
    int size;
};

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

void destroy(LinkedList ptr)
{
    if (NULL == ptr)
    {
        return;
    }
    empty(ptr);
    free(ptr);
    ptr = NULL;
}