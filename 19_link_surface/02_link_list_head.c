#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct _link_node
{
    int num;
    struct _link_node *next;
} NODE;

extern void init_linklist(struct _link_node **);
extern void insert_member(struct _link_node **, int);
extern void printf_link_list(struct _link_node *);

int main()
{
    NODE *current = NULL;
    init_linklist(&current);
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        insert_member(&current, rand() % 100);
    }
    printf_link_list(current);
    return EXIT_FAILURE;
}

void init_linklist(struct _link_node **tail_ptr)
{
    NODE *header = (NODE *)malloc(sizeof(struct _link_node));
    header->next = NULL;
    *tail_ptr = header;
}

void insert_member(struct _link_node **header, int value)
{
    NODE *new_node = (NODE *)malloc(sizeof(struct _link_node));
    new_node->next = NULL;
    new_node->num = value;
    (*header)->next = new_node;
    *header = new_node;
}

void printf_link_list(struct _link_node *tail_ptr)
{
    printf("[");
    while (tail_ptr->next != NULL)
    {
        printf("%d ", tail_ptr->num);
        tail_ptr = tail_ptr->next;
    }
    printf("]\n");
}