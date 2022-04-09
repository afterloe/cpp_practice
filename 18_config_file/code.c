#include "code.h"

void code_file(char *src_file_path, char *dist_file_path)
{
    /*
     加密逻辑
     char -> short
     0000 0000 0010 0011   <<  4
     0000 0010 0011 0000   |
     1000 0010 0011 0000   +  0000 ~ 1111
     1000 0010 0011 1101
     */
    FILE *src = fopen(src_file_path, "r");
    FILE *dst = fopen(dist_file_path, "w");
    srand(time(NULL));

    if (src == NULL || dst == NULL)
    {
        printf("[ERROR]: 文件为空");
        return;
    }

    char ch;
    while (EOF != (ch = fgetc(src)))
    {
        short _ = (short)ch;
        // 左移四位
        _ = _ << 4;
        // 统一符号位
        _ = _ | 0x8000;
        // 增加 随机数
        _ = _ + rand() % 16;
        // 写入字符到文件
        fprintf(dst, "%hd", _);
    }

    fclose(src);
    fclose(dst);
    src = NULL;
    dst = NULL;
}

void decode_file(char *src_file_path, char *dist_file_path)
{
    // 1000 0010 0011 1101 << 1
    // 0000 0100 0111 1010 >> 5
    // 0000 0000 0010 0011 short -> char
    FILE *src = fopen(src_file_path, "r");
    FILE *dst = fopen(dist_file_path, "w");
    if (src == NULL || dst == NULL)
    {
        printf("[ERROR]: 文件为空");
        return;
    }

    short _;
    while (!feof(src))
    {
        fscanf(src, "%hd", &_);
        _ <<= 1;
        _ >>= 5;
        fputc((char)_, dst);
    }

    fclose(src);
    fclose(dst);
    src = NULL;
    dst = NULL;
}