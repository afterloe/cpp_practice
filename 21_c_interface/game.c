#include "game_impl.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void WORD_INIT_IMPL(void *config)
{
    printf("\n加载游戏配置\n");
    int *i = (int *)config;
    for (int idx = 0; idx < 3; idx++)
    {
        printf("游戏配置： %d \n", *i);
        i++;
    }
}

void PLAYER_INIT_IMPL(void **player_ptr, char *name)
{
    Player *player = (Player *)malloc(sizeof(Player));
    player->exp = 0;
    player->level = 0;
    strcpy(player->name, name);
    *player_ptr = player;
}

int FIGHT_IMPL(void *player, int game_difficult)
{
    Player *ptr = player;
    int add_exp = 0;
    switch (game_difficult)
    {
    case 1:
        add_exp = is_win(90, game_difficult);
        break;
    case 2:
        add_exp = is_win(60, game_difficult);
        break;
    case 3:
        add_exp = is_win(30, game_difficult);
        break;
    default:
        break;
    }

    ptr->exp += add_exp;
    ptr->level = ptr->level + ptr->exp / 100;
    if (ptr->exp >= 100)
    {
        ptr->exp = ptr->exp - 100;
    }

    if (!add_exp)
    {
        return 0;
    }

    return 1;
}

void PLAYER_INFO_IMPL(void *player)
{
    Player *ptr = player;
    printf("%s lv.%d - %d \n", ptr->name, ptr->level, ptr->exp);
}

void EXIT_WORLD_IMPL(void *player)
{
    printf("保存游戏信息 ... \n");
}

int is_win(int percentage, int game_difficult)
{
    srand(time(NULL));
    int value = rand() % 100 + 1;
    if (value < percentage)
    {
        return game_difficult * 10;
    }
    return 0;
}