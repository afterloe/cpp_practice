#include <stdlib.h>
#include <stdio.h>

#include <arpa/inet.h>

int main()
{
    // 数据转字节序
    char data[4] = {192, 168, 11, 23};
    int *ptr = (int *)&data;

    // 字节序转换
    int sum = htonl(*ptr);

    unsigned char *current = (unsigned char *)&sum;
    printf("[");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", *current);
        current++;
    }
    printf("]\n");

    unsigned short a = 0x0102; 
    unsigned short b = htons(a);

    printf("sum=%x\n", b);

    return EXIT_SUCCESS;
}