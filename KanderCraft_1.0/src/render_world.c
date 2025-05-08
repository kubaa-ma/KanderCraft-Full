#include "raylib.h"
#include "../include/world.h"
#include "../include/render_world.h"
#include "../include/block.h"



void init_textures(Textures_K *data) {
    data->dirt = LoadTexture("assets/dirt.png");
}

void unload_textures(Textures_K *data) {
    UnloadTexture(data->dirt);
}

void init_model(Model *block_model, Textures_K *texture_data){
    Mesh plane_mesh = GenMeshPlane(10.0f, 10.0f, 1, 1);

    *block_model = LoadModelFromMesh(plane_mesh);
    
    
    block_model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_data->dirt;
    
    //UnloadMesh(plane_mesh);
}

void draw_blocks(World *data_world, Player_config *data_player, Model *block_model) {
    for (int cx = 0; cx < TOTAL_CHUNKS; cx++) {
        for (int cz = 0; cz < TOTAL_CHUNKS; cz++) {
            for (int y = 0; y < CHUNK_DEPTH; y++) {
                for (int x = 0; x < CHUNK_WIDTH; x++) {
                    for (int z = 0; z < CHUNK_LENGTH; z++) {

                        Block block = data_world->data_chunks[cx][cz].data_blocks[y][x][z];

                        if (block.features & VISIBLE) {
                            Vector3 position = {
                                (float)((cx * 2) * CHUNK_WIDTH * 2 + x) * BLOCK_SITE_SIZE,  // x
                                (float)(y) * BLOCK_SITE_SIZE,                      // y
                                (float)(cz * CHUNK_LENGTH + z) * BLOCK_SITE_SIZE   // z
                            };

                            if (block.visible_faces & FACE_RIGHT) {
                                DrawModelEx(*block_model, position, ROT_RIGHT_SITE, ROT_ANGLE_RIGHT, BLOCK_SIZE, WHITE);
                            }
                            if (block.visible_faces & FACE_LEFT) {
                                DrawModelEx(*block_model, position, ROT_LEFT_SITE, ROT_ANGLE_LEFT, BLOCK_SIZE, WHITE);
                            }
                            if (block.visible_faces & FACE_TOP) {
                                DrawModelEx(*block_model, position, ROT_TOP_SITE, ROT_ANGLE_TOP, BLOCK_SIZE, WHITE);
                            }
                            if (block.visible_faces & FACE_BOTTOM) {
                                DrawModelEx(*block_model, position, ROT_BOTTOM_SITE, ROT_ANGLE_BOTTOM, BLOCK_SIZE, WHITE);
                            }
                            if (block.visible_faces & FACE_BACK) {
                                DrawModelEx(*block_model, position, ROT_BACK_SITE, ROT_ANGLE_BACK, BLOCK_SIZE, WHITE);
                            }
                            if (block.visible_faces & FACE_FRONT) {
                                DrawModelEx(*block_model, position, ROT_FRONT_SITE, ROT_ANGLE_FRONT, BLOCK_SIZE, WHITE);
                            }
                        }
                    }
                }
            }
        }
    }
}


