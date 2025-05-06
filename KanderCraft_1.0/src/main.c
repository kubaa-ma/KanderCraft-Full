#include "raylib.h"
#include "../include/world.h"
#include "../include/render_world.h"
#include <stdlib.h>
#include "../include/player_configuration.h"
#include "../include/config.h"


int main() {

    Player_config data;

    if(load_config(&data)){
        create_config(&data);
    }

    World* user_world = malloc(sizeof(World));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "KanderCraft 1.0");

    Textures_K textures;
    init_textures(&textures);


    Camera camera = { 0 };
    init_player(&data, &camera);
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f }; 
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; 
    camera.fovy = 54.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    Vector2 screenCenter = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    Vector3 cameralast = camera.position;


    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);



        BeginMode3D(camera);

        ClearBackground(WHITE);

        EndMode3D();


        EndDrawing();
    }
    take_player_info(&data, &camera);
    save_config(&data);
    unload_textures(&textures);
    CloseWindow();

    return 0;
}