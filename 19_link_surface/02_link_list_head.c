#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct _link_node
{
    int num;
    struct _link_node *next;
} NODE;

extern void init_linklist(struct _link_node **);
extern void push(struct _link_node **, int);
extern void insert(struct _link_node **, int, int);
extern void printf_link_list(struct _link_node *);

int main()
{
    NODE *current = NULL;
    init_linklist(&current);
    srand(time(NULL));
    // 连续尾插
    // for (int i = 0; i < 10; i++)
    // {
    //     int num = rand() % 100;
    //     push(&current, num);
    // }
    push(&current, 10);
    push(&current, 20);
    push(&current, 30);
    printf("指定插入前: \n");
    printf_link_list(current);
    insert(&current, 20, 200);
    insert(&current, 21, 1030);
    printf("指定插入后: \n");
    printf_link_list(current);

    return EXIT_FAILURE;
}

void init_linklist(struct _link_node **tail_ptr)
{
    NODE *header = (NODE *)malloc(sizeof(struct _link_node));
    header->next = NULL;
    *tail_ptr = header;
}

void insert(struct _link_node **header, int old_value, int new_value)
{
    NODE *prev = *header;
    NODE *current = (*header)->next;
    while (current != NULL)
    {
        if (old_value == current->num)
        {
            break;
        }
        prev = current;
        current = current->next;
    }

    NODE *new_node = (NODE *)malloc(sizeof(struct _link_node));
    new_node->num = new_value;
    new_node->next = NULL;

    new_node->next = current;
    prev->next = new_node;
}

void push(struct _link_node **header, int value)
{
    // 使用尾部指针 实现尾插；
    NODE *tail_ptr = *header;
    while (NULL != tail_ptr->next)
    {
        tail_ptr = tail_ptr->next;
    }
    NODE *new_node = (NODE *)malloc(sizeof(struct _link_node));
    new_node->num = value;
    new_node->next = NULL;
    tail_ptr->next = new_node;

    // 使用递归的方式 实现尾插；
    // if (NULL == (*header)->next)
    // {
    //     NODE *new_node = (NODE *)malloc(sizeof(struct _link_node));
    //     new_node->num = value;
    //     new_node->next = NULL;
    //     (*header)->next = new_node;
    // }
    // else
    // {
    //     return insert_member(&(*header)->next, value);
    // }
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