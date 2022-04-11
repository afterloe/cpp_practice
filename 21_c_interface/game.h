#pragma once

#ifndef __GAME_H__
#define __GAME_H__

/**
 * @brief 定义函数指针 -  游戏世界初始化
 *
 * @param config : 配置信息
 */
typedef void (*WORD_INIT)(void *config);

/**
 * @brief 玩家初始化
 *
 * @param player : 玩家指针
 * @param name : 玩家姓名
 */
typedef void (*PLAYER_INIT)(void **player, char *name);

/**
 * @brief 战斗
 *
 * @param player : 玩家指针
 * @param game_difficult : 游戏难度
 * @return int : 0 - 战斗失败； 1 - 战斗成功
 */
typedef int (*FIGHT)(void *player, int game_difficult);

/**
 * @brief 玩家信息
 *
 * @param player : 玩家指针
 */
typedef void (*PLAYER_INFO)(void *player);

/**
 * @brief 离开游戏
 *
 * @param player : 玩家指针
 */
typedef void (*EXIT_WORLD)(void *player);

#endif