#ifndef PLAYER_CONFIG_H
#define PLAYER_CONFIG_H

#include "raylib.h"

typedef struct{
    float pos_x;
    float pos_z;
    float pos_y;

    float tar_x;
    float tar_y;
    float tar_z;
    int render_distance;
}Player_config;


void create_camera(Camera *camera, Vector2 *screenCenter, Vector3 *cameralast);

void take_player_info(Player_config *data, Camera *camera);

void init_player(Player_config *data, Camera *camera);

void side_info(Font standart, Camera camera);

void game_settings(bool *is_on, Font standart, Camera *camera);
#endif