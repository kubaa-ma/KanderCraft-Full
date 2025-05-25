#ifndef RENDER_WORLD_H
#define RENDER_WORLD_H

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
#include "world.h"
#include <float.h> 

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define CUBE_SIDES 6
#define TEXTURES_AMOUNT 128

typedef struct {
    Texture2D dirt;
    Texture2D grass[CUBE_SIDES];
    Texture2D cursor;
    Font standrat_font;
    Texture2D cobblestone;
} Textures_K;

typedef struct{
    Music music3;
    Sound destroy_loose_block;
    Sound place_loose_block;
    Sound place_stone_block;
}SoundsK;


void init_textures(Textures_K *data);

void init_sounds(SoundsK *data);

void unload_sounds(SoundsK *data);

void unload_textures(Textures_K *data);

void init_models(Model models[TEXTURES_AMOUNT], Textures_K *texture_data);

void draw_blocks(World *data_world, Player_config *data_player, Model *block_model, Block_orient* sour, Camera data_camera, bool use_debbug_camera);


Vector3 NormalizeVector(Vector3 v);

bool CheckRayCollisionWithBlock(Ray ray, World *data_world, int cx, int cz, int y, int x, int z);

Vector5 detectCollision(Camera camera, World *data_world,  bool use_test_camera);

Vector3 GetHitNormal(Ray ray, BoundingBox box);


void draw_IT(Model *models, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 blockScale, Color tint, Blocktype type);
bool Vector3EqualsK(Vector3 a, Vector3 b);
void Game_input(Vector5 Collision_data, World *data_world, Camera camera, SoundsK *sounds, int block_place);
void prepeare_block_ori(Block_orient *sour);
#endif
