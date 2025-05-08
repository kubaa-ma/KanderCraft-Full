#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include "stdbool.h"
#include "block.h"
#include "player_configuration.h"

#define TOTAL_CHUNKS 10

#define CHUNK_WIDTH 16
#define CHUNK_LENGTH  16
#define CHUNK_DEPTH 10

typedef struct{
    Block ***data_blocks;
}Chunk;

typedef struct{
    Chunk** data_chunks;
}World;

Chunk** allocate_chunk();
Block ***allocate_blocks();

void free_blocks(Block ***blocks);
void destroy_world(World *data_world, const Player_config *data);
void world_generator(World *data_world, Player_config *data);
void settle_blocks(World *data_world, Player_config *data);

#endif