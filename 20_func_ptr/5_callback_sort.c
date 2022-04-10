#include <stdlib.h>
#include <stdio.h>

#include <time.h>

void sort(void *arr, int ele_size, int size, int (*compare)(void *, void *))
{
    char *ptr = arr;
    for (int idx = 0; idx < size / ele_size; idx++)
    {
        char *current = ptr + ele_size * idx;
        for (int i = idx + 1; i < size / ele_size; i++)
        {
            char *next = ptr + i * idx;
            if (compare(current, next))
            {
                char *tmp = current;
                current = next;
                next = tmp;
            }
        }
    }
}

int compare_int(void *a, void *b)
{
    int *x = (int *)a;
    int *y = (int *)b;
    if (x > y)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void test01()
{
    srand(time(NULL));
    int arr[10] = {0};
    printf("\n [");
    for (int i = 0; i < sizeof arr / sizeof(int); i++)
    {
        arr[i] = rand() / 100 + 1;
        printf("%d ", arr[i]);
    }
    printf("] \n");

    sort(arr, sizeof(int), sizeof arr, compare_int);
    printf("排序后");
    printf("\n [");
    for (int i = 0; i < sizeof arr / sizeof(int); i++)
    {
        printf("%d ", arr[i]);
    }
    printf("] \n");
}

int main()
{
    test01();
    return EXIT_SUCCESS;
}