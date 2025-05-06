#include "raylib.h"
#include "../include/world.h"
#include "../include/render_world.h"
#include <stdlib.h>



int main() {

    World* user_world = malloc(sizeof(World));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "KanderCraft 1.0");

    Textures_K textures;
    init_textures(&textures);


    Camera camera = { 0 };
    camera.position = (Vector3){ 5.0f, 14.75f, 5.0f };
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

    unload_textures(&textures);
    CloseWindow();

    return 0;
}