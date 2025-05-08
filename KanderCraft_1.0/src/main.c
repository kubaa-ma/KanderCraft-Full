#include "raylib.h"
#include "../include/world.h"
#include "../include/render_world.h"
#include <stdlib.h>
#include "../include/player_configuration.h"
#include "../include/config.h"

int main() {


    Player_config data_player;

    if (load_config(&data_player)) {
        create_config(&data_player);
    }

    World data_world;
    data_world.data_chunks = allocate_chunk();

    for (int i = 0; i < TOTAL_CHUNKS; i++) {
        for (int j = 0; j < TOTAL_CHUNKS; j++) {
            data_world.data_chunks[i][j].data_blocks = allocate_blocks();
        }
    }

    world_generator(&data_world, &data_player);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "KanderCraft 1.0");

    Textures_K textures;
    init_textures(&textures);

    Model block_model;
    init_model(&block_model, &textures);

    Camera camera = { 0 };
    Vector2 screenCenter;
    Vector3 cameralast;
    init_player(&data_player, &camera);
    create_camera(&camera, &screenCenter, &cameralast);

    while (!WindowShouldClose()) {
        
        settle_blocks(&data_world, &data_player);
        UpdateCamera(&camera, CAMERA_FREE);
        BeginDrawing();
        ClearBackground(BLUE);
        BeginMode3D(camera);
        draw_blocks(&data_world, &data_player, &block_model);
        DrawGrid(1000, 10);
        EndMode3D();
        EndDrawing();
    }

    take_player_info(&data_player, &camera);
    save_config(&data_player);

    for (int i = 0; i < data_player.render_distance; i++) {
        for (int j = 0; j < data_player.render_distance; j++) {
            free_blocks(data_world.data_chunks[i][j].data_blocks);
        }
    }

    UnloadModel(block_model);
    destroy_world(&data_world, &data_player);
    unload_textures(&textures);
    CloseWindow();

    return 0;
}
