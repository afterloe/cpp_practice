#include <iostream>
#include <stdio.h>
#include <time.h>

#define SIZE 10

void fillArray(int *, int);
int findMax(int *, int);

int main(void)
{
    srand(time(NULL));
    int *p = (int *)malloc(sizeof(int[10]));
    // int size = 10;
    fillArray(p, SIZE);
    int max = findMax(p, SIZE);
    printf("max value is %d \n", findMax(p, SIZE));
    free(p);
    system("pause");
    return 0;
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
