#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "seq_stack.h"

#define MAX 1024

struct seq_stack
{
    void *data[MAX];
    int size;
};

Seq_Stack init()
{
    struct seq_stack *stack = malloc(sizeof(struct seq_stack));
    memset(stack->data, 0, sizeof(void *) * MAX);
    stack->size = 0;
    return stack;
}

void push(Seq_Stack ptr, void *data)
{
    if (NULL == ptr)
    {
        return;
    }

    struct seq_stack *stack = ptr;

    if (stack->size == MAX)
    {
        return;
    }

    stack->data[stack->size] = data;
    stack->size++;
}

void pop(Seq_Stack ptr)
{
    if (NULL == ptr)
    {
        return;
    }

    struct seq_stack *stack = ptr;

    if (stack->size == 0)
    {
        return;
    }

    stack->data[stack->size - 1] = NULL;
    stack->size--;
}

void *top_seq_stack(Seq_Stack ptr)
{
    if (NULL == ptr)
    {
        return NULL;
    }

    struct seq_stack *stack = ptr;

    if (stack->size == 0)
    {
        return NULL;
    }

    return stack->data[stack->size - 1];
}

int size(Seq_Stack ptr)
{
    if (NULL == ptr)
    {
        return -1;
    }

    struct seq_stack *stack = ptr;

    return stack->size;
}

int is_empty(Seq_Stack ptr)
{
    if (NULL == ptr)
    {
        return -1;
    }

    struct seq_stack *stack = ptr;
    if (0 == stack->size)
    {
        return 1;
    }
    return 0;
}

void empty(Seq_Stack ptr)
{
    if (NULL == ptr)
    {
        return;
    }

    struct seq_stack *stack = ptr;
    memset(stack->data, 0, sizeof(void *) * MAX);
    stack->size = 0;
}

void destroy(Seq_Stack ptr)
{
    if (NULL == ptr)
    {
        return;
    }

    empty(ptr);
    free(ptr);
    ptr = NULL;
}