#ifndef WORLD_H
#define WORLD_H

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
#include "stdbool.h"
#include "block.h"
#include "player_configuration.h"
#include "world_config.h"
#include "block.h"

#define PATH_WORLD_FILES "WorldFiles"

typedef struct{
    Block ***data_blocks;
    bool is_loaded;
    int x;
    int z;
    BoundingBox bounds;
}Chunk;

typedef struct{
    Chunk** data_chunks;
    bool initialized;
}World;

Chunk** allocate_chunk();
Block ***allocate_blocks();



int copy_file(const char *source_path, const char *dest_path);
int create_world_files(const char *world_name);
int load_world_files(const char *world_name);
int load_chunk(const char *world_name, int i, int j, Chunk *data);
void init_world(World *world);
int load_world(World *world, const char *world_name);
int save_chunk(const char *world_name, int i, int j, Chunk *data);
int save_world(World *world, const char *world_name);
void free_blocks(Block ***blocks);
void destroy_world(World *data_world);
void world_generator(World *data_world);
void settle_blocks(World *data_world);
void DrawChunkCornersRays(Chunk *chunk, Camera3D cam);

#endif