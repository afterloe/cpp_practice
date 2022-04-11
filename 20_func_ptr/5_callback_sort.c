#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include <string.h>

void print_array(void *ptr, int ele_size, int len, void (*func)(void *))
{
    char *p = ptr;
    printf("\n[");
    for (int idx = 0; idx < len / ele_size; idx++)
    {
        char *addr = p + idx * ele_size;
        func(addr);
    }
    printf("]\n");
}

void sort(void *arr, int ele_size, int size, int (*compare)(void *, void *))
{

    for (int idx = 0; idx < size / ele_size; idx++)
    {
        int max_idx = idx;
        for (int i = idx + 1; i < size / ele_size; i++)
        {
            void *current = arr + ele_size * max_idx;
            void *next = arr + ele_size * i;
            if (compare(current, next))
            {
                max_idx = i;
            }
        }
        if (idx != max_idx)
        {
            void *next = arr + ele_size * idx;
            void *max_or_min = arr + ele_size * max_idx;
            void *tmp = malloc(ele_size);

            memcpy(tmp, next, ele_size);
            memcpy(next, max_or_min, ele_size);
            memcpy(max_or_min, tmp, ele_size);
        }
    }
}

int compare_int(void *a, void *b)
{
    int *x = (int *)a;
    int *y = (int *)b;
    if (*x > *y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void print_int(void *ptr)
{
    int *data = (int *)ptr;
    printf("%d ", *data);
}

void test01()
{
    srand(time(NULL));
    int arr[10] = {0};
    for (int i = 0; i < sizeof arr / sizeof(int); i++)
    {
        arr[i] = rand() % 100 + 1;
    }
    printf("排序前: \n");
    print_array(arr, sizeof(int), sizeof arr, print_int);
    sort(arr, sizeof(int), sizeof arr, compare_int);
    printf("排序后: \n");
    print_array(arr, sizeof(int), sizeof arr, print_int);
}

int main()
{
    test01();
    return EXIT_SUCCESS;
}