#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define SIZE 10

extern void fillArray(int *, int);
extern int findMax(int *, int);
extern void full_process(void);

extern void two_dimensional_array(void);
extern void sort_char(char *[], int);

int main(void)
{
    // full_process(); // 一维数组的查询与算法实现；
    two_dimensional_array(); // 二纬数组的查询与实现；
    return EXIT_SUCCESS;
}

void full_process()
{
    srand(time(NULL));
    int *p = (int *)malloc(10);
    fillArray(p, SIZE);
    int max = findMax(p, SIZE);
    printf("max value is %d \n", findMax(p, SIZE));
    free(p);
    p = NULL;
}

void sort_char(char *arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int max = i;
        for (int j = i + i; j < len; j++)
        {
            if (strcmp(arr[max], arr[j]) < 0)
            {
                max = j;
            }
        }
        if (i != max)
        {
            char *tmp = arr[i];
            arr[i] = arr[max];
            arr[max] = tmp;
        }
    }

    printf("after: \n");
    for (int i = 0; i < len; i++)
    {
        printf("%s\n", arr[i]);
    }
}

void two_dimensional_array()
{
    // char p[][16] = {"ccc", "bbbb", "ggggg", "dd", "eeeee", "aaaa"};
    char *p[] = {"a", "c", "b", "f", "d", "e"};
    int len = sizeof(p) / sizeof(char *);
    printf("befor: \n");
    for (int i = 0; i < len; i++)
    {
        printf("%s\n", p[i]);
    }
    sort_char(p, len);
}

void fillArray(int *p, int size)
{
    for (int i = 0; i < size; i++)
    {
        p[i] = rand();
        // *(p+i) = rand();
        printf("%d ", *(p + i));
    }
    printf("\n");
}

int findMax(int *p, int size)
{
    int max = *p;
    for (int i = 0; i < size; i++)
    {
        if (p[i] > max)
        {
            max = p[i];
        }
    }

    return max;
}
