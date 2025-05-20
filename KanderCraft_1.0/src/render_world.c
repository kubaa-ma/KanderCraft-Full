#include "raylib.h"
#include "../include/world.h"
#include "../include/render_world.h"
#include "../include/block.h"

void init_sounds(SoundsK *data){
    data->destroy_loose_block = LoadSound("assets/sounds/destroy_loose.wav");
    data->place_loose_block = LoadSound("assets/sounds/place_loose.wav");



    data->music3 = LoadMusicStream("assets/sounds/calm3.wav");
    // Music track used: calm3.wav
    // Original soundtrack from Minecraft by C418
    // This file is used for educational/non-commercial purposes only.
    // All rights to the original composition belong to its respective author and publisher.
}

void unload_sounds(SoundsK *data){
    UnloadSound(data->destroy_loose_block);
    UnloadSound(data->place_loose_block);
    UnloadMusicStream(data->music3);
}

void init_textures(Textures_K *data) {
    data->dirt = LoadTexture("assets/dirt.png");
    data->cursor = LoadTexture("assets/cursor.png");
    data->standrat_font = LoadFont("assets/minecraft_font.ttf");
    data->grass[0] = LoadTexture("assets/grass/grass_bottom.png");
    data->grass[1] = LoadTexture("assets/grass/grass_side_back.png");
    data->grass[2] = LoadTexture("assets/grass/grass_side_front.png");
    data->grass[3] = LoadTexture("assets/grass/grass_side_left.png");
    data->grass[4] = LoadTexture("assets/grass/grass_side_right.png");
    data->grass[5] = LoadTexture("assets/grass/grass_top.png");

}

void unload_textures(Textures_K *data) {
    UnloadTexture(data->dirt);
    UnloadTexture(data->cursor);
    UnloadFont(data->standrat_font);
    for(int i = 0; i < CUBE_SIDES; i ++){
        UnloadTexture(data->grass[i]);
    }
}

void init_models(Model models[TEXTURES_AMOUNT], Textures_K *texture_data) {
    int i;

    for (i = 0; i < CUBE_SIDES; i++) {
        Mesh face = GenMeshPlane(10.0f, 10.0f, 1, 1);
        models[i] = LoadModelFromMesh(face);

        models[i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_data->grass[i];
    }

    if (i < TEXTURES_AMOUNT) {
        Mesh dirt_face = GenMeshPlane(10.0f, 10.0f, 1, 1);
        models[i] = LoadModelFromMesh(dirt_face);

        models[i].materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_data->dirt;
        i++;
    }
}

void draw_blocks(World *data_world, Player_config *data_player, Model *block_model, Block_orient* sour, Camera data_camera) {

    int player_chunk_x = (int)floor(data_camera.position.x / CHUNK_WIDTH);
    int player_chunk_z = (int)floor(data_camera.position.z / CHUNK_LENGTH);

    int START_X = player_chunk_x - data_player->render_distance;
    int END_X   = player_chunk_x + data_player->render_distance;
    int START_Z = player_chunk_z - data_player->render_distance;
    int END_Z   = player_chunk_z + data_player->render_distance;

    if (START_X < 0) START_X = 0;
    if (START_Z < 0) START_Z = 0;
    if (END_X >= TOTAL_CHUNKS) END_X = TOTAL_CHUNKS - 1;
    if (END_Z >= TOTAL_CHUNKS) END_Z = TOTAL_CHUNKS - 1;

    for (int cx = START_X; cx <= END_X; cx++) {
        for (int cz = START_Z; cz <= END_Z; cz++) {
            for (int y = 0; y < CHUNK_DEPTH; y++) {
                for (int x = 0; x < CHUNK_WIDTH; x++) {
                    for (int z = 0; z < CHUNK_LENGTH; z++) {

                        int c_distance_x = 0;
                        int c_distance_z = 0;
                        c_distance_x = cx * CHUNK_WIDTH;
                        c_distance_z = cz * CHUNK_LENGTH;

                        Block block = data_world->data_chunks[cx][cz].data_blocks[y][x][z];

                        if (block.features & VISIBLE) {
                            Vector3 position_top = (Vector3){sour->sour_x[x] + 0.5f + c_distance_x, sour->sour_y[y] + 1.0f, sour->sour_z[z] + 0.5f + c_distance_z};//
                            Vector3 position_front = (Vector3){sour->sour_x[x] + 0.5f + c_distance_x, sour->sour_y[y] + 0.5f, sour->sour_z[z] + 0.0f + c_distance_z};//
                            Vector3 position_left = (Vector3){sour->sour_x[x] + 0.0f + c_distance_x, sour->sour_y[y] + 0.5f, sour->sour_z[z] + 0.5f + c_distance_z};//
                            Vector3 position_bottom = (Vector3){sour->sour_x[x] + 0.5f + c_distance_x, sour->sour_y[y] + 0.0f, sour->sour_z[z] + 0.5f + c_distance_z};//
                            Vector3 position_back = (Vector3){sour->sour_x[x] + 0.5f + c_distance_x, sour->sour_y[y] + 0.5f, sour->sour_z[z] + 1.0f + c_distance_z};//
                            Vector3 position_right = (Vector3){sour->sour_x[x] + 1.0f + c_distance_x, sour->sour_y[y] + 0.5f, sour->sour_z[z] + 0.5f + c_distance_z};//


                            if (block.visible_faces & FACE_RIGHT) {
                                draw_IT(block_model, position_right, ROT_RIGHT_SITE, ROT_ANGLE_RIGHT, BLOCK_SIZE, LIGHTGRAY, block.type);
                            }
                            if (block.visible_faces & FACE_LEFT) {
                                draw_IT(block_model, position_left, ROT_LEFT_SITE, ROT_ANGLE_LEFT, BLOCK_SIZE, LIGHTGRAY, block.type);
                            }
                            if (block.visible_faces & FACE_TOP) {
                                draw_IT(block_model, position_top, ROT_TOP_SITE, ROT_ANGLE_TOP, BLOCK_SIZE, WHITE, block.type);
                            }
                            if (block.visible_faces & FACE_BOTTOM) {
                                draw_IT(block_model, position_bottom, ROT_BOTTOM_SITE, ROT_ANGLE_BOTTOM, BLOCK_SIZE, DARKGRAY, block.type);
                            }
                            if (block.visible_faces & FACE_BACK) {
                                draw_IT(block_model, position_back, ROT_BACK_SITE, ROT_ANGLE_BACK, BLOCK_SIZE, WHITE, block.type);
                            }
                            if (block.visible_faces & FACE_FRONT) {
                                draw_IT(block_model, position_front, ROT_FRONT_SITE, ROT_ANGLE_FRONT, BLOCK_SIZE, WHITE, block.type);
                            }

                            // DrawBoundingBox(block.box, WHITE);
                        }
                    }
                }
            }
        }
    }
}
bool Vector3EqualsK(Vector3 a, Vector3 b) {

    const float EPSILON =  0.0001f;

    return (fabsf(a.x - b.x) < EPSILON &&
            fabsf(a.y - b.y) < EPSILON &&
            fabsf(a.z - b.z) < EPSILON);
}


bool FloatEqualsK(float a, float b) {
    const float EPSILON = 0.0001f;
    return fabsf(a - b) < EPSILON;
}

void draw_IT(Model *models, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 blockScale, Color tint, Blocktype type) {
    switch (type) {
        case BLOCK_GRASS:
            if (Vector3EqualsK(rotationAxis, ROT_RIGHT_SITE) && FloatEqualsK(rotationAngle, ROT_ANGLE_RIGHT)) {
                DrawModelEx(models[4], position, rotationAxis, rotationAngle, blockScale, tint);
            }
            else if (Vector3EqualsK(rotationAxis, ROT_LEFT_SITE) && FloatEqualsK(rotationAngle, ROT_ANGLE_LEFT)) {
                DrawModelEx(models[3], position, rotationAxis, ROT_ANGLE_LEFT, blockScale, tint);
            }
            else if (Vector3EqualsK(rotationAxis, ROT_TOP_SITE) && FloatEqualsK(rotationAngle, ROT_ANGLE_TOP)) {
                DrawModelEx(models[5], position, rotationAxis, rotationAngle, blockScale, tint);
            }
            else if (Vector3EqualsK(rotationAxis, ROT_BOTTOM_SITE) && FloatEqualsK(rotationAngle, ROT_ANGLE_BOTTOM)) {
                DrawModelEx(models[0], position, rotationAxis, rotationAngle, blockScale, tint);
            }
            else if (Vector3EqualsK(rotationAxis, ROT_FRONT_SITE) && FloatEqualsK(rotationAngle, ROT_ANGLE_FRONT)) {
                DrawModelEx(models[1], position, rotationAxis, rotationAngle, blockScale, tint);
            }
            else if (Vector3EqualsK(rotationAxis, ROT_BACK_SITE) && FloatEqualsK(rotationAngle, ROT_ANGLE_BACK)) {
                DrawModelEx(models[2], position, rotationAxis, rotationAngle, blockScale, tint);
            }
            break;

        case BLOCK_DIRT:
            DrawModelEx(models[6], position, rotationAxis, rotationAngle, blockScale, tint);
            break;

        default:
            break;
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

Vector3 GetHitNormal(Ray ray, BoundingBox box) {
    RayCollision collision = GetRayCollisionBox(ray, box);
    Vector3 normal = { 0, 0, 0 };

    if (!collision.hit) return normal;

    Vector3 point = collision.point;
    const float EPSILON = 0.001f;

    if (fabsf(point.x - box.min.x) < EPSILON) normal.x = -1;
    else if (fabsf(point.x - box.max.x) < EPSILON) normal.x = 1;
    else if (fabsf(point.y - box.min.y) < EPSILON) normal.y = -1;
    else if (fabsf(point.y - box.max.y) < EPSILON) normal.y = 1;
    else if (fabsf(point.z - box.min.z) < EPSILON) normal.z = -1;
    else if (fabsf(point.z - box.max.z) < EPSILON) normal.z = 1;

    return normal;
}


Vector5 detectCollision(Camera camera, World *data_world) {
    Vector5 datas = { -1, -1, -1, -1, -1 };

    Vector3 camDir = {camera.target.x - camera.position.x, camera.target.y - camera.position.y, camera.target.z - camera.position.z};
    camDir = NormalizeVector(camDir);

    Ray ray = { camera.position, camDir };
    //DrawRay(ray, BLUE);

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
        BoundingBox hitBox = data_world->data_chunks[datas.cx][datas.cz].data_blocks[datas.y][datas.x][datas.z].box;
        DrawBoundingBox(hitBox, WHITE);
    }

    return datas;
}

void Game_input(Vector5 Collision_data, World *data_world, Camera camera, SoundsK *sounds) {
    int c_distance_x = 0;
    int c_distance_z = 0;
    c_distance_z = Collision_data.cx * CHUNK_WIDTH;
    c_distance_x = Collision_data.cz * CHUNK_LENGTH;

    if(Collision_data.cx != -1 && Collision_data.cz != -1 &&
       Collision_data.y != -1 && Collision_data.x != -1 && Collision_data.z != -1) {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[Collision_data.y][Collision_data.x][Collision_data.z].type != BLOCK_AIR) {
            PlaySound(sounds->destroy_loose_block);
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[Collision_data.y][Collision_data.x][Collision_data.z].type = BLOCK_AIR;
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[Collision_data.y][Collision_data.x][Collision_data.z].features = 0b00000000;
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[Collision_data.y][Collision_data.x][Collision_data.z].box.min = (Vector3){999,999,999};
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[Collision_data.y][Collision_data.x][Collision_data.z].box.max = (Vector3){999,999,999};
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)  && Collision_data.y < CHUNK_DEPTH -1) {

            Vector3 camDir = NormalizeVector((Vector3){camera.target.x - camera.position.x, camera.target.y - camera.position.y, camera.target.z - camera.position.z});
            Ray ray = { camera.position, camDir };
            BoundingBox box = data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[Collision_data.y][Collision_data.x][Collision_data.z].box;
            Vector3 normal = GetHitNormal(ray, box);

            int newX = Collision_data.x + (int)normal.x;
            int newY = Collision_data.y + (int)normal.y;
            int newZ = Collision_data.z + (int)normal.z;
            PlaySound(sounds->place_loose_block);
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[newY][newX][newZ].type = BLOCK_DIRT;
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[newY][newX][newZ].features = 0b00000111;
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[newY][newX][newZ].box.min = (Vector3){newX + c_distance_z, newY, newZ + c_distance_x};
            data_world->data_chunks[Collision_data.cx][Collision_data.cz].data_blocks[newY][newX][newZ].box.max = (Vector3){newX + 1.0f + c_distance_z, newY + 1.0f, newZ + 1.0f + c_distance_x};
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