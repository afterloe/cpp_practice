#include <stdlib.h>
#include <stdio.h>

#include <arpa/inet.h>

int main()
{
    // 点分制 ip 地址 转 32位 网络大端数据
    char ip[] = "192.168.11.34";
    unsigned int num = 0;

    inet_pton(AF_INET, ip, &num);

    unsigned char *p = (unsigned char *)&num;

    // [192 168 11 34 ]
    printf("[");
    for (int i = 0; i < 4; i++)
    {
        printf("%d ", *p);
        p++;
    }
    printf("]\n");

    // 32位的网络大端数据 转 点分制 ip地址
    char ipr[64] = {0};
    const char *cp = inet_ntop(AF_INET, &num, ipr, sizeof ipr);
    printf("[");
    while (*cp != 0)
    {
        printf("%c ", *cp);
        cp++;
    }
    printf("]\n");

    return EXIT_SUCCESS;
}