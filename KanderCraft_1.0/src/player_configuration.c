#include "../include/player_configuration.h"
#include <stdio.h>

void create_camera(Camera *camera, Vector2 *screenCenter, Vector3 *cameralast){
    camera->up = (Vector3){ 0.0f, 1.0f, 0.0f }; 
    camera->projection = CAMERA_PERSPECTIVE;
    *screenCenter = (Vector2){ GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    *cameralast = camera->position;
}

void take_player_info(Player_config *data, Camera *camera){
    data->pos_x = camera->position.x;
    data->pos_y = camera->position.y;
    data->pos_z = camera->position.z;
    data->tar_x = camera->target.x;
    data->tar_y = camera->target.y;
    data->tar_z = camera->target.z;
    data->fovy = camera->fovy;
}

void init_player(Player_config *data, Camera *camera){
    camera->position.x = data->pos_x;
    camera->position.y = data->pos_y;
    camera->position.z = data->pos_z;
    camera->target.x = data->tar_x;
    camera->target.y = data->tar_y;
    camera->target.z = data->tar_z;
    camera->fovy = data->fovy;
}

void side_info(Font standart, Camera camera, Vector5 CollisionData, bool *use_test_camera){

        char side_Info[512];
        float frameTime = GetFrameTime();
        int fps_state = GetFPS();\

        if(*use_test_camera){
            DrawTextPro(standart, "!DEBUG CAMERA! (switch [U])", (Vector2){800, 10}, (Vector2){0,0}, 0, 42, 1.0f, WHITE);
        }

        sprintf(side_Info, "KanderCraft unreleased version\nMade by Kander\nFPS: %d\nFrame time - %f\nXYZ: %d / %d / %d\nTarget XYZ: %d / %d/ %d\nCamera Fovy (Key: j,n): %f (54.0 normal)\nCollision At chunk XZ: %d | %d Blok XYZ: %d | %d | %d\nAt chunk XZ: %d / %d\nDebugging camera switch by pressing [U]", fps_state, frameTime,
            (int)camera.position.x ,(int)camera.position.y, (int)camera.position.z, 
            (int)camera.target.x, (int)camera.target.y, (int)camera.target.z, camera.fovy, CollisionData.cx, CollisionData.cz, CollisionData.x, CollisionData.y, CollisionData.z, (int)camera.position.x / CHUNK_WIDTH, (int)camera.position.z /CHUNK_LENGTH);
        DrawTextPro(standart, side_Info, (Vector2){10, 10}, (Vector2){0,0}, 0, 24, 1.0f, WHITE);

}

void game_settings(bool *is_on, Font standart, Camera *camera, Vector5 CollisionData, bool *use_test_camera){
    if (IsKeyPressed(KEY_F11)) {
        ToggleBorderlessWindowed();
    }
    if (IsKeyPressed(KEY_F3)){
        *is_on = !*is_on;
    }
    if(*is_on){
        side_info(standart, *camera, CollisionData, use_test_camera);
    }
    if(IsKeyDown(KEY_J) && camera->fovy > 1){
        camera->fovy -=0.5;
    } else if(IsKeyDown(KEY_N) && camera->fovy < 130){
        camera->fovy +=0.5;
    }
}