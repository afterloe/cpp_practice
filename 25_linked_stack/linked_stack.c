#include <stdlib.h>
#include <stdio.h>

#include "linked_stack.h"

struct linked_stack_node
{
    struct linked_stack_node *next;
};

struct linked_stack
{
    struct linked_stack_node head;
    int size;
};

LinkedStack init()
{
    struct linked_stack *ptr = malloc(sizeof(struct linked_stack));
    ptr->head.next = NULL;
    ptr->size = 0;

    return ptr;
}

void push(LinkedStack ptr, void *data)
{
    if (NULL == ptr || NULL == data)
    {
        return;
    }

    struct linked_stack *stack = ptr;
    struct linked_stack_node *node = data;

    node->next = stack->head.next;
    stack->head.next = node;
    stack->size++;
}

void pop(LinkedStack ptr)
{
    if (NULL == ptr)
    {
        return;
    }

    struct linked_stack *stack = ptr;
    if (stack->size == 0)
    {
        return;
    }
    struct linked_stack_node *first = stack->head.next;
    stack->head.next = first->next;
    stack->size--;
}

void *top_linked_stack(LinkedStack ptr)
{
    if (NULL == ptr)
    {
        return NULL;
    }
    struct linked_stack *stack = ptr;
    return stack->head.next;
}

int size(LinkedStack ptr)
{
    if (NULL == ptr)
    {
        return -1;
    }
    struct linked_stack *stack = ptr;
    return stack->size;
}

int is_empty(LinkedStack ptr)
{
    if (NULL == ptr)
    {
        return -1;
    }
    struct linked_stack *stack = ptr;
    if (0 == stack->size)
    {
        return 1;
    }
    return 0;
}

void empty(LinkedStack ptr)
{
    if (NULL == ptr)
    {
        return;
    }

    struct linked_stack *stack = ptr;
    stack->head.next = NULL;
    stack->size = 0;
}

void destroy(LinkedStack ptr)
{
    if (NULL == ptr)
    {
        return;
    }

    empty(ptr);
    free(ptr);
    ptr = NULL;
}