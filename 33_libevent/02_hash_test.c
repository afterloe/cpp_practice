#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <openssl/md5.h>

int main()
{
    MD5_CTX ctx;
    MD5_Init(&ctx);
    char data[16] = "afterloe world";
    MD5_Update(&ctx, data, strlen(data));
    unsigned char cryptText[16] = {0};
    MD5_Final(cryptText, &ctx);

    printf("\n md5=[");
    for(int idx = 0; idx < sizeof cryptText; idx ++)
    {
        printf("%02x", cryptText[idx]);
    }
    printf("]\n");

    return EXIT_SUCCESS;
}