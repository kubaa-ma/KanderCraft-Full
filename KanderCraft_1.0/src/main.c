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
#include "../include/folders.h"


int main() {

    Player_config data_player;
    GAMESTATE state = MENU;
    Button button_menu;
    Button button_wlist;
    

    World data_world;
    data_world.data_chunks = allocate_chunk();
    init_world(&data_world);
    for (int i = 0; i < TOTAL_CHUNKS; i++) {
        for (int j = 0; j < TOTAL_CHUNKS; j++) {
            data_world.data_chunks[i][j].data_blocks = allocate_blocks();
            world_generator(&data_world);
        }
    }

    int block_place = 0;
    bool is_on = false;
    bool use_test_camera = false;
    char world_list[458] = { 0 };
    char world_name[88];
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

    Camera test_camera = { 0 };
    create_camera(&test_camera, &screenCenter, &cameralast);
    int count = load_folder_names(world_list, sizeof(world_list)); 
    load_icon(world_list, &textures);


    while (!WindowShouldClose()) {

        if(state == MENU){

            BeginDrawing();
            ClearBackground(WHITE);
            int x = (screenWidth - textures.button.width) / 2;
            int z = (screenHeight - textures.button.height) / 2;
            draw_menu(textures);
            draw_buttons(&button_menu, textures.button, &state, x + 484, z + 400, 0, "NONE", "NONE", data_sounds.menu_click);
            DrawTextPro(textures.standrat_font, "Play", (Vector2){884, 648}, (Vector2){0, 0}, 0, 42, 1.0f, WHITE);
            game_settings(&is_on, textures.standrat_font, &camera, Collision_data, &use_test_camera);
            EndDrawing();
            
        }else if(state == WORLDS) {

            BeginDrawing();
            ClearBackground(WHITE);
            draw_menu(textures);
            draw_icons(textures);
            int clicked = 0;
            for(int i = 0; i < count; i++) {
                if (draw_buttons(&button_wlist, textures.button_t, &state, 484, 400 + (i * 82), i, world_name, world_list, data_sounds.menu_click)) {
                    clicked = 1;
                }
            }

            if(count < 4){
                int x = GetScreenWidth() - textures.button.width;
                int y = GetScreenHeight() - textures.button.height;

                draw_buttons(&button_menu, textures.button, &state, x -100, y - 48, 999, world_name, world_list, data_sounds.menu_click);
                DrawMultilineText("Create New World!", (Vector2){x - 60, y - 18}, 42, 1.0f, 46.0f, WHITE, textures.standrat_font);

            }

            DrawMultilineText(world_list, (Vector2){534, 400}, 42, 1.0f, 46.0f, WHITE, textures.standrat_font);

            if (clicked) {
                if(load_world(&data_world, world_name)) {create_world_files(world_name);}
                if (load_config(&data_player, world_name)) {create_config(&data_player, world_name);}
                init_player(&data_player, &camera);
                init_player(&data_player, &test_camera);

                unload_unnecessary(&textures);
            }
            game_settings(&is_on, textures.standrat_font, &camera, Collision_data, &use_test_camera);
            EndDrawing();
        
        }else if(state == NEW_WORLDK){
            char output_text[256];
            sprintf(output_text, "Name of the world: %s\n", world_name);
            BeginDrawing();
                draw_menu(textures);
                name_input(world_name);
                DrawMultilineText(output_text, (Vector2){534, 400}, 42, 1.0f, 46.0f, WHITE, textures.standrat_font);
                
                int clicked = 0;
                int x = GetScreenWidth() - textures.button.width;
                int y = GetScreenHeight() - textures.button.height;
                if(draw_buttons(&button_menu, textures.button, &state, x -100, y - 48, 1000, world_name, world_list, data_sounds.menu_click) == 1000){
                    clicked = 1000;
                }
                DrawMultilineText("Create!", (Vector2){x - 60, y - 18}, 42, 1.0f, 46.0f, WHITE, textures.standrat_font);
            EndDrawing();

            if(clicked == 1000){
                create_world_files(world_name);
                create_config(&data_player, world_name);
                init_player(&data_player, &camera);
                init_player(&data_player, &test_camera);

                unload_unnecessary(&textures);
                state = GAME;
                HideCursor();
            }


        } else if(state == GAME){

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


            DrawTexture(textures.slots_array, (GetScreenWidth() - textures.slots_array.width) / 2, GetScreenHeight() - textures.slots_array.height - 40, WHITE);
            DrawTexture(textures.slot_cursor, (GetScreenWidth() - textures.slots_array.width) / 2 + (block_place * 61) + block_place, GetScreenHeight() - textures.slots_array.height - 40, WHITE);
            draw_items(&textures);
            EndDrawing();

            Game_input(Collision_data, &data_world, camera, &data_sounds, block_place);
            settle_blocks(&data_world);

            int key = GetCharPressed();
            if (key >= '0' && key <= '9') {
                block_place = key - '0'; 
            }
        }
    }

    save_world(&data_world, world_name);

    take_player_info(&data_player, &camera);
    save_config(&data_player, world_name);

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
