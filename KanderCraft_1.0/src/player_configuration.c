#include "../include/player_configuration.h"

void create_camera(Camera *camera, Vector2 *screenCenter, Vector3 *cameralast){
    camera->target = (Vector3){ 0.0f, 0.0f, 0.0f }; 
    camera->up = (Vector3){ 0.0f, 1.0f, 0.0f }; 
    camera->fovy = 54.0f;
    camera->projection = CAMERA_PERSPECTIVE;
    *screenCenter = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    *cameralast = camera->position;
}

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