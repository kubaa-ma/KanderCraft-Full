#include "../include/player_configuration.h"

void take_player_info(Player_config *data, Camera *camera){
    data->pos_x = camera->position.x;
    data->pos_y = camera->position.y;
    data->pos_z = camera->position.z;
}

void init_player(Player_config *data, Camera *camera){
    camera->position.x = data->pos_x;
    camera->position.y = data->pos_y;
    camera->position.z = data->pos_z;
}