#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include "stdbool.h"
#include "block.h"

#define TOTAL_CHUNKS 100

#define CHUNK_WIDTH 16
#define CHUNK_LENGTH  16
#define CHUNK_DEPTH 100

typedef struct{
    Block*** data_blocks;
}Chunk;

typedef struct{
    Chunk** data_chunks;
}World;

Chunk* allocate_chunk();

void allocate_world(World* world);
void destroy_world(World* world);
#endif