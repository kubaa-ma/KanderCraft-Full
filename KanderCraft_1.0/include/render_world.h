#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

#include "raylib.h"
#include "world.h"
#include <float.h> 

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define CUBE_SIDES 6

typedef struct {
    Texture2D dirt;
    Texture2D grass[CUBE_SIDES];
    Texture2D cursor;
    Font standrat_font;
} Textures_K;


typedef struct{
    int cx; 
    int cz; 
    int y;
    int x;
    int z;
}Vector5;

void init_textures(Textures_K *data);

void unload_textures(Textures_K *data);

void init_model(Model *block_model, Textures_K *texture_data);

void draw_blocks(World *data_world, Player_config *data_player, Model *block_model, Block_orient* sour);

Vector3 NormalizeVector(Vector3 v);

bool CheckRayCollisionWithBlock(Ray ray, World *data_world, int cx, int cz, int y, int x, int z);

Vector5 detectCollision(Camera camera, World *data_world);

Vector3 GetHitNormal(Ray ray, BoundingBox box);

void Game_input(Vector5 Collision_data, World *data_world, Camera camera);
void prepeare_block_ori(Block_orient *sour);
#endif
