#include <stdlib.h>
#include <stdio.h>

#include "linked_stack.h"

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

    printf("linked stack Size :: %d \n", size(link_stack));
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
    printf("linked stack Size :: %d \n", size(link_stack));

    push(link_stack, &p1);
    printf("linked stack Size :: %d \n", size(link_stack));
    push(link_stack, &p2);
    printf("linked stack Size :: %d \n", size(link_stack));

    destroy(link_stack);

    return EXIT_SUCCESS;
}