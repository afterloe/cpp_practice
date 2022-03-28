#include <stdlib.h>
#include <stdio.h>

int main()
{
    int a, b;
    a = 12;
    b = 13;
    auto func = [](int x, int y)
    { return x + y; };
    printf("sum is %d\n", func(a, b));
    system("pause");
    return 0;
}