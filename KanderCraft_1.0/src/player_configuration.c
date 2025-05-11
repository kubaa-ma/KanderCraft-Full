#include "../include/player_configuration.h"
#include <stdio.h>
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

void side_info(Font standart, Camera camera){

        char side_Info[512];
        float frameTime = GetFrameTime();
        int fps_state = GetFPS();
        sprintf(side_Info, "KanderCraft unreleased version\nMade by Kander\nFPS - %d\nFrame time - %f\nXYZ - %d / %d / %d\nTarget XYZ - %d / %d/ %d", fps_state, frameTime,
            (int)camera.position.x ,(int)camera.position.y, (int)camera.position.z, 
            (int)camera.target.x, (int)camera.target.y, (int)camera.target.z);
        DrawTextPro(standart, side_Info, (Vector2){10, 10}, (Vector2){0,0}, 0, 18, 1.0f, WHITE);

}

void game_settings(bool *is_on, Font standart, Camera camera){
    if (IsKeyPressed(KEY_F11)) {
        ToggleBorderlessWindowed();
    }
    if (IsKeyPressed(KEY_F3)){
        *is_on = !*is_on;
    }
    if(*is_on){
        side_info(standart, camera);

    }
}