#include "enter.h"

int main(int argc, char **args)
{
    char* file_name;
    get_file_name(&file_name, argc, args);
    printf("\n[info]read file from %s\n", file_name);
    int line = get_file_line(file_name);
    printf("[info] config file has %d line \n", line);
    CONFIG * config = NULL;
    parse_file(&config, line, file_name);

    return EXIT_SUCCESS;
}