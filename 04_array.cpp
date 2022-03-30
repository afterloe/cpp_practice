#include <iostream>
#include <stdio.h>
#include <time.h>

#define SIZE 10

void fillArray(int *, int);
int findMax(int *, int);
void two_dimensional_array_common();
void two_dimensional_array_usual();
void full_process()
{
    srand(time(NULL));
    int *p = (int *)malloc(10);
    // int size = 10;
    fillArray(p, SIZE);
    int max = findMax(p, SIZE);
    printf("max value is %d \n", findMax(p, SIZE));
    free(p);
}

int main(void)
{
    // full_process();
    // two_dimensional_array_common();
    two_dimensional_array_usual();
    system("pause");
    return 0;
}

void two_dimensional_array_usual() {
    // char ** students = (char**)malloc([4][32]);
}

void two_dimensional_array_common() {
    char student_name_list[4][32] = {"afterloe", "joe", "nio", "lilei"};
    for (int i = 0; i < 4; i++) {
        printf("%s\n", student_name_list[i]);
    }
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
