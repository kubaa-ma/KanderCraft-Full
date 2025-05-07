#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

#include "raylib.h"
#include "world.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define CUBE_SIDES 6

typedef struct {
    Texture2D dirt;
    Texture2D grass[CUBE_SIDES];
} Textures_K;


void init_textures(Textures_K *data);

void unload_textures(Textures_K *data);

void init_model(Model *block_model, Textures_K *texture_data);

void draw_blocks(World *data_world, Player_config *data_player, Model *block_model);
#endif
