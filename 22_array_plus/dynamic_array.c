#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"


#ifndef __dynamic_array_c
#define __dynamic_array_c
struct _dynamic_array
{
    void **addr;  // 具体指针
    int size;     // 数组大小
    int capacity; // 数组容量
};
#endif

ArrayList init(int capacity)
{
    struct _dynamic_array *ptr = (struct _dynamic_array *)malloc(sizeof(struct _dynamic_array));
    if (0 <= capacity)
    {
        capacity = 1;
    }
    ptr->addr = malloc(sizeof(void *) * capacity);
    ptr->size = 0;
    ptr->capacity = capacity;

    return ptr;
}

void insert(ArrayList ptr, void *data, int pos)
{
    if (NULL == ptr)
    {
        return;
    }
    struct _dynamic_array *arr = ptr;

    // 如果位置 不正确 则强制 尾插
    if (pos < 0 || pos > arr->size)
    {
        pos = arr->size;
    }

    // 判断容量是否足够, 不足则自动扩容
    if (arr->size >= arr->capacity)
    {
        int capacity = arr->capacity + 1; // 每次增加一个位置
        void **new_space = (void **)malloc(sizeof(void *) * capacity);
        memcpy(new_space, arr->addr, sizeof(void *) * arr->capacity);
        free(arr->addr);          // 释放空间
        arr->addr = new_space;    // 重新指向
        arr->capacity = capacity; // 更新容量信息
    }

    for (int idx = arr->size - 1; idx >= pos; idx--)
    {
        arr->addr[idx + 1] = arr->addr[idx]; // 移动内容
    }

    arr->addr[pos] = data;
    arr->size++;
}

void info(ArrayList ptr, void (*func)(void *))
{
    if (NULL == ptr)
    {
        return;
    }
    struct _dynamic_array *arr = ptr;
    printf("\n[");
    for (int idx = 0; idx < arr->size; idx++)
    {
        func(arr->addr[idx]);
    }
    printf("]\n");
    printf("array list ::: size -> %d; capacity -> %d", arr->size, arr->capacity);
    printf("\n");
}

void remove_by_pos(ArrayList ptr, int pos)
{
    if (NULL == ptr)
    {
        return;
    }
    struct _dynamic_array *arr = ptr;
    if (pos < 0 || pos >= arr->size)
    {
        return;
    }
    for (int idx = pos; idx < arr->size; idx++)
    {
        arr->addr[idx] = arr->addr[idx + 1];
    }
    arr->size--;
}

void remove_by_data(ArrayList ptr, void *data, int (*compare)(void *, void *))
{
    if (NULL == ptr || NULL == data)
    {
        return;
    }
    struct _dynamic_array *arr = ptr;
    for (int idx = 0; idx < arr->size; idx++)
    {
        if (compare(arr->addr[idx], data))
        {
            remove_by_pos(ptr, idx);
        }
    }
}

void emptry(ArrayList ptr)
{
    if (NULL == ptr)
    {
        return;
    }
    struct _dynamic_array *arr = ptr;
    free(arr->addr);
    arr->addr = NULL;
    arr->size = 0;
    arr->capacity = 0;
}

void destroy(ArrayList ptr)
{
    if (NULL == ptr)
    {
        return;
    }
    emptry(ptr);
    free(ptr);
    ptr = NULL;
}