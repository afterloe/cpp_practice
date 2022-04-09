#include "enter.h"

int main(int argc, char **args)
{
    char* file_name;
    get_file_name(&file_name, argc, args);
    printf("\n[info]read file from %s\n\n", file_name);

    return EXIT_SUCCESS;
}