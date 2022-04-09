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
        int num = rand() % 100;
        insert_member(&current, num);
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
    if (NULL == (*header)->next)
    {
        NODE *new_node = (NODE *)malloc(sizeof(struct _link_node));
        new_node->num = value;
        new_node->next = NULL;
        (*header)->next = new_node;
    }
    else
    {
        return insert_member(&(*header)->next, value);
    }
}

void printf_link_list(struct _link_node *tail_ptr)
{
    printf("[");
    tail_ptr = tail_ptr->next;
    while (tail_ptr != NULL)
    {
        printf("%d ", tail_ptr->num);
        tail_ptr = tail_ptr->next;
    }
    printf("]\n");
}