#include "raylib.h"
#include "../include/world.h"
#include "../include/render_world.h"
#include <stdlib.h>
#include "../include/player_configuration.h"
#include "../include/config.h"
#include "../include/block.h"

#define WORLD_NAME "World1"

int main() {

    Player_config data_player;

    if (load_config(&data_player)) {
        create_config(&data_player);
    }

    World data_world;
    data_world.data_chunks = allocate_chunk();
    init_world(&data_world);
    for (int i = 0; i < TOTAL_CHUNKS; i++) {
        for (int j = 0; j < TOTAL_CHUNKS; j++) {
            data_world.data_chunks[i][j].data_blocks = allocate_blocks();
                world_generator(&data_world, &data_player);
        }
    }

    if(load_world_files(WORLD_NAME) == 1){
        create_world_files(WORLD_NAME);
    } else{
        load_world(&data_world, WORLD_NAME);
    }

    bool is_on = false;
    Block_orient sour;
    Vector5 Collision_data;
    prepeare_block_ori(&sour);


    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "KanderCraft 1.0");
    ToggleBorderlessWindowed();
    Textures_K textures;
    init_textures(&textures);

    Model block_model;
    init_model(&block_model, &textures);

    Camera camera = { 0 };
    Vector2 screenCenter;
    Vector3 cameralast;
    create_camera(&camera, &screenCenter, &cameralast);
    init_player(&data_player, &camera);
    while (!WindowShouldClose()) {

        Centering_cursor();
        UpdateCamera(&camera, CAMERA_FREE);
        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(camera);

        draw_blocks(&data_world, &data_player, &block_model, &sour, camera);

        if(IsKeyUp(KEY_L)){
            Collision_data = detectCollision(camera, &data_world);
        }
        EndMode3D();
        Game_input(Collision_data, &data_world, camera);
        
        game_settings(&is_on, textures.standrat_font, &camera, Collision_data);
        if(IsKeyUp(KEY_L)){
            DrawTexture(textures.cursor, 0,0, WHITE);
        }
        EndDrawing();
        settle_blocks(&data_world);

    }

    save_world(&data_world, WORLD_NAME);

    take_player_info(&data_player, &camera);
    save_config(&data_player);

    for (int i = 0; i < TOTAL_CHUNKS; i++) {
        for (int j = 0; j < TOTAL_CHUNKS; j++) {
            free_blocks(data_world.data_chunks[i][j].data_blocks);
        }
    }

    UnloadModel(block_model);
    destroy_world(&data_world, &data_player);
    unload_textures(&textures);
    CloseWindow();

    return 0;
}
