#ifndef WORLD_H
#define WORLD_H

#include "raylib.h"
#include "stdbool.h"
#include "block.h"

#define WORLD_SIZE 100

#define CHUNK_X 16
#define CHUNK_Z 16
#define CHUNK_Y 100
#define CHUNK_SIZE CHUNK_Z*CHUNK_X*CHUNK_Y

typedef struct{
    block*** data_blocks;
}Chunk;

typedef struct{
    Chunk* data_chunks[WORLD_SIZE][WORLD_SIZE];
}World;

Chunk* Create_chunk();
void Create_world(World* world);
void destroy_world(World* world);
#endif