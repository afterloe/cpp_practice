#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern void test_01();
extern void test_02();

int main()
{
    // test_01();
    test_02();
    return EXIT_SUCCESS;
}

void test_01()
{
    char a = 'a';
    char b = 'b';
    printf("srd ::: a = [%c], b = [%c]\n", a, b);
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
    printf("des ::: a = [%c], b = [%c]\n", a, b);
}

void test_02()
{
    srand(time(NULL));
    int num = rand();
    if ((num & 0x01) == 0)
    {
        printf("%d 是偶数\n", num);
    }
    else
    {
        printf("%d 是奇数\n", num);
    }
}

void reversal(char **str)
{
    int str_len = strlen(*str);
    char tmp = 0;
    for (int i = 0; i < str_len; i++)
    {
        tmp = (*str)[i];
        (*str)[i] = (*str)[str_len - i];
        (*str)[str_len - i] = tmp;
    }
}