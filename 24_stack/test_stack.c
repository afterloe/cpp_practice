#include <stdlib.h>
#include <stdio.h>

#include <string.h>

#ifndef __STACK
#define __STACK

#define MAX 1024

struct seq_stack
{
    void *data[MAX];
    int size;
};

typedef void *Seq_Stack;

extern Seq_Stack init();
extern void push(Seq_Stack, void *);
extern void pop(Seq_Stack);
extern void *top_seq_stack(Seq_Stack);
extern int size(Seq_Stack);
extern int is_empty(Seq_Stack);
extern void empty(Seq_Stack);
extern void destroy(Seq_Stack);

#endif

typedef struct
{
    char name[32];
    int age;
} Person;

void print_person(void *data)
{
    Person *p = data;
    printf("%s - %d \n", p->name, p->age);
}

int main()
{
    Person p1 = {"aaa", 10};
    Person p2 = {"bbb", 20};
    Person p3 = {"ccc", 30};
    Person p4 = {"ddd", 40};
    Person p5 = {"eee", 50};

    Seq_Stack stack = init();
    push(stack, &p1);
    printf("Seq Stack Size :: %d \n", size(stack));
    push(stack, &p2);
    printf("Seq Stack Size :: %d \n", size(stack));
    push(stack, &p3);
    printf("Seq Stack Size :: %d \n", size(stack));
    push(stack, &p4);
    printf("Seq Stack Size :: %d \n", size(stack));
    push(stack, &p5);
    printf("Seq Stack Size :: %d \n", size(stack));

    while (!is_empty(stack))
    {
        Person *p = top_seq_stack(stack);
        pop(stack);
        print_person(p);
    }

    push(stack, &p1);
    printf("Seq Stack Size :: %d \n", size(stack));
    push(stack, &p2);
    printf("Seq Stack Size :: %d \n", size(stack));

    printf("清空栈\n");
    empty(stack);
    printf("Seq Stack Size :: %d \n", size(stack));

    push(stack, &p1);
    printf("Seq Stack Size :: %d \n", size(stack));
    push(stack, &p2);
    printf("Seq Stack Size :: %d \n", size(stack));

    destroy(stack);

    return EXIT_SUCCESS;
}

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