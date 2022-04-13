#include <stdlib.h>
#include <stdio.h>

#ifndef __LINKED_STACK
#define __LINKED_STACK

struct linked_stack_node
{
    struct linked_stack_node *next;
};

struct linked_stack
{
    struct linked_stack_node *head;
    int size;
};

typedef void *LinkedStack;

extern LinkedStack init();
extern void push(LinkedStack, void *);
extern void pop(LinkedStack);
extern void *top_linked_stack(LinkedStack);
extern int size(LinkedStack);
extern int is_empty(LinkedStack);
extern void empty(LinkedStack);
extern void destroy(LinkedStack);

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
    printf("%s -> %d\n", p->name, p->age);
}

int main()
{
    LinkedStack link_stack = init();

    Person p1 = {NULL, "aaa", 10};
    Person p2 = {NULL, "bbb", 20};
    Person p3 = {NULL, "ccc", 30};
    Person p4 = {NULL, "ddd", 40};
    Person p5 = {NULL, "eee", 50};

    push(link_stack, &p1);
    push(link_stack, &p2);
    push(link_stack, &p3);
    push(link_stack, &p4);
    push(link_stack, &p5);

    printf("Seq Stack Size :: %d \n", size(link_stack));
    while (!is_empty(link_stack))
    {
        void *data = top_linked_stack(link_stack);
        print_person(data);
        pop(link_stack);
    }

    push(link_stack, &p1);
    push(link_stack, &p2);
    push(link_stack, &p3);

    printf("清空栈\n");
    empty(link_stack);
    printf("Seq Stack Size :: %d \n", size(link_stack));

    push(link_stack, &p1);
    printf("Seq Stack Size :: %d \n", size(link_stack));
    push(link_stack, &p2);
    printf("Seq Stack Size :: %d \n", size(link_stack));

    destroy(link_stack);

    return EXIT_SUCCESS;
}

LinkedStack init()
{
    struct linked_stack *ptr = malloc(sizeof(struct linked_stack));
    ptr->head = NULL;
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
    struct linked_stack_node *current = stack->head;
    struct linked_stack_node *node = data;
    node->next = current;
    stack->head = data;
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
    struct linked_stack_node *current = stack->head;
    for (int idx = 0; idx < stack->size - 1; idx++)
    {
        current = current->next;
    }
    current->next = NULL;
    stack->size--;
}

void *top_linked_stack(LinkedStack ptr)
{
    if (NULL == ptr)
    {
        return NULL;
    }
    struct linked_stack *stack = ptr;
    struct linked_stack_node *current = stack->head;
    for (int idx = 0; idx < stack->size - 1; idx++)
    {
        current = current->next;
    }
    return current->next;
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
        return 0;
    }
    return 1;
}

void empty(LinkedStack ptr)
{
    if (NULL == ptr)
    {
        return;
    }

    struct linked_stack *stack = ptr;
    stack->head = NULL;
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