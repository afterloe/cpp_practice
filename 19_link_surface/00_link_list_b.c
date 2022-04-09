#include <stdlib.h>
#include <stdio.h>

typedef struct _linked_node
{
    int num;
    struct _linked_node *next;
} NODE;

extern void static_linked_list();
extern void linked_list();

int main()
{
    static_linked_list();
    linked_list();
    return EXIT_SUCCESS;
}

void static_linked_list()
{
    NODE n1 = {1, NULL};
    NODE n2 = {2, NULL};
    NODE n3 = {3, NULL};
    NODE n4 = {4, NULL};
    NODE n5 = {5, NULL};

    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;

    NODE *current = &n1;
    while (current != NULL)
    {
        printf("%d ", current->num);
        current = current->next;
    }
    printf("\n\n");
}

void linked_list()
{
    NODE * n1 = (NODE *) malloc (sizeof(struct _linked_node));
    NODE * n2 = (NODE *) malloc (sizeof(struct _linked_node));
    NODE * n3 = (NODE *) malloc (sizeof(struct _linked_node));
    NODE * n4 = (NODE *) malloc (sizeof(struct _linked_node));
    NODE * n5 = (NODE *) malloc (sizeof(struct _linked_node));

    n1->num = 100;
    n1->next = n2;
    n2->num = 200;
    n2->next = n3;
    n3->num = 300;
    n3->next = n4;
    n4->num = 400;
    n4->next = n5;
    n5->num = 500;

    NODE * current = n1;
    while (NULL != current)
    {
        printf("%d ", current->num);
        current = current->next;
    }
    printf("\n\n");
}