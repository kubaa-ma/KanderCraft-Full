#include "raylib.h"
#include "../include/world.h"
#include "../include/render_world.h"



void init_textures(Textures_K *data) {
    data->dirt = LoadTexture("assets/dirt.png");
}

void unload_textures(Textures_K *data) {
    UnloadTexture(data->dirt);
}