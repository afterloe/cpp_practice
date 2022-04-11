#pragma once

#ifndef __GAME_IMPL_1
#define __GAME_IMPL_1

typedef struct __palyer
{
    char name[64];
    int level;
    int exp;
} Player;

extern void WORD_INIT_IMPL(void *);

extern void PLAYER_INIT_IMPL(void **, char *);

extern int FIGHT_IMPL(void *, int);

extern void PLAYER_INFO_IMPL(void *);

extern void EXIT_WORLD_IMPL(void *);

extern int is_win(int, int);

#endif