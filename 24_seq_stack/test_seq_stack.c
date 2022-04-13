#include <stdlib.h>
#include <stdio.h>

#include "seq_stack.h"

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