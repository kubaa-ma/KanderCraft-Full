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

void draw_blocks(World *data_world, Player_config *data_player, Model *block_model, Block_orient* sour) {
    for (int cx = 0; cx < TOTAL_CHUNKS; cx++) {
        for (int cz = 0; cz < TOTAL_CHUNKS; cz++) {
            for (int y = 0; y < CHUNK_DEPTH; y++) {
                for (int x = 0; x < CHUNK_WIDTH; x++) {
                    for (int z = 0; z < CHUNK_LENGTH; z++) {

                        Block block = data_world->data_chunks[cx][cz].data_blocks[y][x][z];

                        if (block.features & VISIBLE) {
                            Vector3 position_top = (Vector3){sour->sour_x[x] + 0.5f, sour->sour_y[y] + 1.0f, sour->sour_z[z] + 0.5f};
                            Vector3 position_front = (Vector3){sour->sour_x[x] + 0.5f, sour->sour_y[y] + 0.5f, sour->sour_z[z] + 15.0f};
                            Vector3 position_left = (Vector3){sour->sour_x[x] + 0.0f, sour->sour_y[y] + 0.5f, sour->sour_z[z] + 0.5f};
                            Vector3 position_bottom = (Vector3){sour->sour_x[x] + 0.5f, sour->sour_y[y] + 0.0f, sour->sour_z[z] + 0.5f};
                            Vector3 position_back = (Vector3){sour->sour_x[x] + 0.5f, sour->sour_y[y] + 0.5f, sour->sour_z[z] + 0.0f};
                            Vector3 position_right = (Vector3){sour->sour_x[x] + (float)(CHUNK_WIDTH - 1), sour->sour_y[y] + 0.5f, sour->sour_z[z] + 0.5f};


                            if (block.visible_faces & FACE_RIGHT) {
                                DrawModelEx(*block_model, position_right, ROT_RIGHT_SITE, ROT_ANGLE_RIGHT, BLOCK_SIZE, WHITE);
                            }
                            if (block.visible_faces & FACE_LEFT) {
                                DrawModelEx(*block_model, position_left, ROT_LEFT_SITE, ROT_ANGLE_LEFT, BLOCK_SIZE, WHITE);
                            }
                            if (block.visible_faces & FACE_TOP) {
                                DrawModelEx(*block_model, position_top, ROT_TOP_SITE, ROT_ANGLE_TOP, BLOCK_SIZE, WHITE);
                            }
                            if (block.visible_faces & FACE_BOTTOM) {
                                DrawModelEx(*block_model, position_bottom, ROT_BOTTOM_SITE, ROT_ANGLE_BOTTOM, BLOCK_SIZE, WHITE);
                            }
                            if (block.visible_faces & FACE_BACK) {
                                DrawModelEx(*block_model, position_back, ROT_BACK_SITE, ROT_ANGLE_BACK, BLOCK_SIZE, WHITE);
                            }
                            if (block.visible_faces & FACE_FRONT) {
                                DrawModelEx(*block_model, position_front, ROT_FRONT_SITE, ROT_ANGLE_FRONT, BLOCK_SIZE, WHITE);
                            }
                        }
                    }
                }
            }
        }
    }
}


