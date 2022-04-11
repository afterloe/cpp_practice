#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct _link_node
{
    int num;
    struct _link_node *next;
} NODE;

extern struct _link_node *init_linklist();
extern void push(struct _link_node *, int);
extern void insert(struct _link_node *, int, int);
extern void printf_link_list(struct _link_node *);
extern void del(struct _link_node *, int);
extern void empty(struct _link_node *);
extern void destroy(struct _link_node *);
extern void reversal(struct _link_node *);
extern void sizeof_link_list(struct _link_node *);

int main()
{
    NODE *current = init_linklist();

    // 连续尾插
    srand(time(NULL));
    for (int i = 0; i < 10; i++)
    {
        int num = rand() % 100;
        push(current, num);
    }
    printf("链表初始化 \n");
    printf_link_list(current);
    sizeof_link_list(current);
    printf("反转链表 \n");
    reversal(current);
    printf_link_list(current);
    printf("清空链表 \n");
    empty(current);
    printf_link_list(current);

    push(current, 10);
    push(current, 20);
    push(current, 30);
    printf("指定插入前: \n");
    printf_link_list(current);
    insert(current, 20, 200);
    insert(current, 21, 1030);
    printf("指定插入后: \n");
    printf_link_list(current);

    printf("删除 200 ... ... \n");
    del(current, 200);
    printf("删除 200 后 \n");
    printf_link_list(current);
    destroy(current);
    current = NULL;
    // insert(current, 20, 10);
    // printf_link_list(current);
    return EXIT_FAILURE;
}

void destroy(struct _link_node *ptr)
{
    empty(ptr);
    free(ptr);
    ptr = NULL;
}

void empty(struct _link_node *ptr)
{
    NODE *prev = ptr;
    NODE *current = prev->next;

    while (current != NULL)
    {
        NODE *next = current->next;
        free(current);
        current = next;
    }

    current = NULL;
    ptr->next = NULL;
}

void del(struct _link_node *ptr, int value)
{
    NODE *prev = ptr;
    NODE *currect = ptr->next;
    while (currect != NULL)
    {
        if (value == currect->num)
        {
            break;
        }
        prev = currect;
        currect = currect->next;
    }

    if (currect == NULL)
    {
        return;
    }

    prev->next = currect->next;
    free(currect);
    currect = NULL;
}

struct _link_node *init_linklist()
{
    NODE *header = (NODE *)malloc(sizeof(struct _link_node));
    header->next = NULL;
    return header;
}

void insert(struct _link_node *header, int old_value, int new_value)
{
    NODE *prev = header;
    NODE *current = header->next;
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

void push(struct _link_node *header, int value)
{
    // 使用尾部指针 实现尾插；
    NODE *tail_ptr = header;
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

void sizeof_link_list(struct _link_node *header_ptr)
{
    int size = 0;
    NODE *current = header_ptr->next;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    printf("size is %d\n", size);
}

void reversal(struct _link_node *header_ptr)
{
    NODE *prev = NULL;
    NODE *current = header_ptr->next;
    NODE *next = NULL;
    while (current != NULL)
    {
        // 改变指针指向
        next = current->next;
        current->next = prev;

        // 移动指针
        prev = current;
        current = next;
    }
    header_ptr->next = prev;
}