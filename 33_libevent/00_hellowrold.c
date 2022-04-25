#include <stdlib.h>
#include <stdio.h>

#include <event.h>

int main()
{
    // gcc file.c -levent
    const char **methods = event_get_supported_methods();
    printf("libevent support method : \n");
    for (;;)
    {
        if (NULL == *methods)
        {
            break;
        }
        printf("%s ", *methods);
        methods++;
    }
    printf("\n");

    return EXIT_SUCCESS;
}