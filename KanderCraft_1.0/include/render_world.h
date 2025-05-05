#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

#include "raylib.h"
#include "world.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

typedef struct {
    Texture2D dirt;
} Textures_K;


void init_textures(Textures_K *data);

void unload_textures(Textures_K *data);



#endif
