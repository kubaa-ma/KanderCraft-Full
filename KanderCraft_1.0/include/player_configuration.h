#ifndef PLAYER_CONFIG_H
#define PLAYER_CONFIG_H

#include "raylib.h"

typedef struct{
    float pos_x;
    float pos_z;
    float pos_y;

    int render_distance;
}Player_config;

void take_player_info(Player_config *data, Camera *camera);

void init_player(Player_config *data, Camera *camera);

#endif