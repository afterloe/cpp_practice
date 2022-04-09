#include "enter.h"
#include "code.h"

int main(int argc, char **args)
{
    char* file_name;
    get_file_name(&file_name, argc, args);
    printf("\n[info]read file from %s\n", file_name);
    int line = get_file_line(file_name);
    printf("[info] config file has %d line \n", line);
    CONFIG * config = NULL;
    parse_file(&config, line, file_name);

    printf("%s\n", get_value("ip", config, line));
    printf("%s\n", get_value("info_show", config, line));

    code_file(file_name, "./code_file.txt");
    decode_file("./code_file.txt", "./decode_file.txt");

    free_space(config, file_name);
    
    return EXIT_SUCCESS;
}