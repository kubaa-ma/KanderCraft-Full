#ifndef PLAYER_CONFIG_H
#define PLAYER_CONFIG_H

/***************************************************************
 *  Project:       KanderCraft
 *  Author:        Jakub Jansa
 *  License:       BSD 2-Clause License
 *
 *  Copyright (c) 2025, Jakub Jansa
 *  All rights reserved.
 *
 *  This file is part of a free software project and is licensed
 *  under the BSD 2-Clause License. See LICENSE file for details.
 ***************************************************************/

#include "raylib.h"
#include "world_config.h"

typedef struct{
    float pos_x;
    float pos_z;
    float pos_y;

    float tar_x;
    float tar_y;
    float tar_z;
    int render_distance;
    float fovy;
}Player_config;

typedef struct{
    Rectangle rect;
    bool covered;
    bool clicked;
} Button;

typedef enum {MENU, SETTINGS, GAME, WORLDS}GAMESTATE;

void create_camera(Camera *camera, Vector2 *screenCenter, Vector3 *cameralast);

void take_player_info(Player_config *data, Camera *camera);

void init_player(Player_config *data, Camera *camera);

void side_info(Font standart, Camera camera, Vector5 Collisiondata);

void game_settings(bool *is_on, Font standart, Camera *camera, Vector5 Collisiondata, bool *use_test_camera);



#endif