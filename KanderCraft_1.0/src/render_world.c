#include "raylib.h"
#include "../include/world.h"
#include "../include/render_world.h"
#include "../include/block.h"



void init_textures(Textures_K *data) {
    data->dirt = LoadTexture("assets/dirt.png");
    data->cursor = LoadTexture("assets/cursor.png");

}

void unload_textures(Textures_K *data) {
    UnloadTexture(data->dirt);
    UnloadTexture(data->cursor);
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
                            Vector3 position_top = (Vector3){sour->sour_x[x] + 0.5f, sour->sour_y[y] + 1.0f, sour->sour_z[z] + 0.5f};//
                            Vector3 position_front = (Vector3){sour->sour_x[x] + 0.5f, sour->sour_y[y] + 0.5f, sour->sour_z[z] + 0.0f};//
                            Vector3 position_left = (Vector3){sour->sour_x[x] + 0.0f, sour->sour_y[y] + 0.5f, sour->sour_z[z] + 0.5f};//
                            Vector3 position_bottom = (Vector3){sour->sour_x[x] + 0.5f, sour->sour_y[y] + 0.0f, sour->sour_z[z] + 0.5f};//
                            Vector3 position_back = (Vector3){sour->sour_x[x] + 0.5f, sour->sour_y[y] + 0.5f, sour->sour_z[z] + 1.0f};//
                            Vector3 position_right = (Vector3){sour->sour_x[x] + 1.0f, sour->sour_y[y] + 0.5f, sour->sour_z[z] + 0.5f};//


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
                            //DrawBoundingBox(block.box, WHITE);
                        }
                    }
                }
            }
        }
    }
}


Vector3 NormalizeVector(Vector3 v) {
    float lengthSq = v.x * v.x + v.y * v.y + v.z * v.z;
    if (lengthSq > 0.000001f) {
        float invLength = 1.0f / sqrtf(lengthSq);
        v.x *= invLength;
        v.y *= invLength;
        v.z *= invLength;
    }
    return v;
}

bool CheckRayCollisionWithBlock(Ray ray, World *data_world, int cx, int cz, int y, int x, int z) {
    BoundingBox box = data_world->data_chunks[cx][cz].data_blocks[y][x][z].box;
    RayCollision collision = GetRayCollisionBox(ray, box);
    return collision.hit;
}

Vector5 detectCollision(Camera camera, World *data_world) {
    Vector5 datas = { -1, -1, -1, -1, -1 };

    Vector3 camDir = {
        camera.target.x - camera.position.x,
        camera.target.y - camera.position.y,
        camera.target.z - camera.position.z
    };
    camDir = NormalizeVector(camDir);

    Ray ray = { camera.position, camDir };
    DrawRay(ray, BLUE);

    float minDistance = FLT_MAX;

    for (int cx = 0; cx < TOTAL_CHUNKS; cx++) {
        for (int cz = 0; cz < TOTAL_CHUNKS; cz++) {
            for (int y = 0; y < CHUNK_DEPTH; y++) {
                for (int x = 0; x < CHUNK_WIDTH; x++) {
                    for (int z = 0; z < CHUNK_LENGTH; z++) {

                        BoundingBox box = data_world->data_chunks[cx][cz].data_blocks[y][x][z].box;
                        RayCollision collision = GetRayCollisionBox(ray, box);

                        if (collision.hit && collision.distance < minDistance) {
                            minDistance = collision.distance;

                            datas.cx = cx;
                            datas.cz = cz;
                            datas.x = x;
                            datas.y = y;
                            datas.z = z;
                        }
                    }
                }
            }
        }
    }

    if (datas.cx != -1) {
        BoundingBox hitBox = data_world->data_chunks[datas.cx][datas.cz]
                             .data_blocks[datas.y][datas.x][datas.z].box;
        DrawBoundingBox(hitBox, WHITE);
    }

    return datas;
}

void Game_input(Vector5 Collision_data, World *data_world) {
    if(Collision_data.cx != -1 && Collision_data.cz != -1 && Collision_data.y != -1 && Collision_data.x != -1 && Collision_data.z != -1){
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[Collision_data.y][Collision_data.x][Collision_data.z].type != BLOCK_AIR) {
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[Collision_data.y][Collision_data.x][Collision_data.z].type = BLOCK_AIR;
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[Collision_data.y][Collision_data.x][Collision_data.z].features = 0b00000000;
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[Collision_data.y][Collision_data.x][Collision_data.z].box.min = (Vector3){999,999,999};
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[Collision_data.y][Collision_data.x][Collision_data.z].box.max = (Vector3){999,999,999};
        }
    }
}

void prepeare_block_ori(Block_orient *sour){
    for (int z = 0; z < TOTAL_CHUNKS * CHUNK_LENGTH - 1; z++) {
        for (int y = 0; y < TOTAL_CHUNKS * CHUNK_DEPTH - 1; y++) {
            for (int x = 0; x < TOTAL_CHUNKS * CHUNK_WIDTH - 1; x++) {
                sour->sour_x[x] = x;
                sour->sour_y[y] = y;
                sour->sour_z[z] = z;
            }
        }
    }
}