/***************************************************************
 *  Project:       KanderCraft
 *  Author:        Jakub Jansa
 *  License:       BSD 2-Clause License
 *
 *  Copyright (c) 2025, Jakub Jansa
 *  All rights reserved.
 *
 *  This file is part of a free software project and is licensed
 *  under the BSD 2-Clause License. See LICENSE file for details.
 ***************************************************************/

#include "raylib.h"
#include "../include/world.h"
#include "../include/render_world.h"
#include <stdlib.h>
#include "../include/player_configuration.h"
#include "../include/config.h"
#include "../include/block.h"

#define WORLD_NAME "Test_world"

int main() {

    Player_config data_player;

    if (load_config(&data_player)) create_config(&data_player);
    

    World data_world;
    data_world.data_chunks = allocate_chunk();
    init_world(&data_world);
    for (int i = 0; i < TOTAL_CHUNKS; i++) {
        for (int j = 0; j < TOTAL_CHUNKS; j++) {
            data_world.data_chunks[i][j].data_blocks = allocate_blocks();
            world_generator(&data_world);
        }
    }
    

    if(load_world_files(WORLD_NAME) == 1) create_world_files(WORLD_NAME);
    
    load_world(&data_world, WORLD_NAME);

    int block_place = 0;
    bool is_on = false;
    bool use_test_camera = false;
    Block_orient sour;
    Vector5 Collision_data;
    prepeare_block_ori(&sour);

    InitAudioDevice();
    SoundsK data_sounds;
    init_sounds(&data_sounds);

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "KanderCraft 1.0");
    ToggleBorderlessWindowed();
    Textures_K textures;
    init_textures(&textures);

    Model block_model[TEXTURES_AMOUNT];
    init_models(block_model, &textures);
    int screenWidth = (GetScreenWidth() / 2) - 12;
    int screenHeight = (GetScreenHeight() / 2) - 12;

    Camera camera = { 0 };
    Vector2 screenCenter;
    Vector3 cameralast;
    create_camera(&camera, &screenCenter, &cameralast);
    init_player(&data_player, &camera);

    Camera test_camera = { 0 };
    create_camera(&test_camera, &screenCenter, &cameralast);
    init_player(&data_player, &test_camera);

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_U)) {use_test_camera = !use_test_camera;}
        
        Centering_cursor();
        UpdateCamera(use_test_camera? &test_camera : &camera, CAMERA_FREE);
        UpdateMusicStream(data_sounds.music3);

        if (!IsMusicStreamPlaying(data_sounds.music3)) {
            PlayMusicStream(data_sounds.music3);
        }
        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode3D(use_test_camera? test_camera : camera);
        draw_blocks(&data_world, &data_player, block_model, &sour, camera, use_test_camera);
        if(IsKeyUp(KEY_L))Collision_data = detectCollision(camera, &data_world, use_test_camera);
        DrawFrustum(camera, NEAR_PLANE, FAR_PLANE, camera.fovy, (float)GetScreenWidth()/GetScreenHeight(), &data_world, &is_on);
        EndMode3D();

        game_settings(&is_on, textures.standrat_font, &camera, Collision_data, &use_test_camera);
        if(IsKeyUp(KEY_L)) DrawTexture(textures.cursor, screenWidth, screenHeight, WHITE);
        EndDrawing();

        Game_input(Collision_data, &data_world, camera, &data_sounds, block_place);
        settle_blocks(&data_world);
        if(GetMouseWheelMove()){
            if(block_place == 0){
                block_place = 1;
            } else if (block_place == 1){
                block_place = 0;
            }
        }

    }

    save_world(&data_world, WORLD_NAME);

    take_player_info(&data_player, &camera);
    save_config(&data_player);

    for (int i = 0; i < TOTAL_CHUNKS; i++) {
        for (int j = 0; j < TOTAL_CHUNKS; j++) {
            free_blocks(data_world.data_chunks[i][j].data_blocks);
        }
    }

    for(int i = 0; i < TEXTURES_AMOUNT; i++){
        UnloadModel(block_model[i]);
    }

    unload_sounds(&data_sounds);
    CloseAudioDevice();

    destroy_world(&data_world);
    unload_textures(&textures);
    CloseWindow();

    return 0;
}
