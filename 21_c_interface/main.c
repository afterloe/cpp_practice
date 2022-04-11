#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "game_impl.h"

extern void init_game(WORD_INIT);
extern void play_game(PLAYER_INIT, FIGHT, PLAYER_INFO);
extern void destroy_game(void *, EXIT_WORLD);

int main()
{
    init_game(WORD_INIT_IMPL);
    play_game(PLAYER_INIT_IMPL, FIGHT_IMPL, PLAYER_INFO_IMPL);
    destroy_game(NULL, EXIT_WORLD_IMPL);

    return EXIT_SUCCESS;
}

void init_game(WORD_INIT func)
{
    int config[3] = {123, 456, 789};
    func(config);
}

void play_game(PLAYER_INIT init_func, FIGHT fight_func, PLAYER_INFO info_func)
{
    void *player = NULL;
    char buf[256];
    system("clear");
    printf("请输入玩家姓名: ");
    scanf("%s", buf);
    init_func(&player, buf);

    int game_difficult = -1;
    while (1)
    {
        getchar();
        system("clear");

        printf("\n请输入游戏难度\n");
        printf("\n 1) 简单"
               " 2) 中等"
               " 3) 困难 \n");

        scanf("%d", &game_difficult);
        getchar();

        int ret = fight_func(player, game_difficult);
        if (ret)
        {
            printf("\n 战斗胜利 ! \n");
        }
        else
        {
            printf("\n 战斗失败，再接再厉 !! \n");
        }

        info_func(player);
    }
}

void destroy_game(void *player, EXIT_WORLD func)
{
    printf("\n准备退出游戏\n");
    func(player);
}
