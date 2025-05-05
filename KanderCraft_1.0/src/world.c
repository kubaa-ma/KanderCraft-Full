#include "../include/world.h"
#include "../include/block.h"
#include <stdio.h>
#include <stdlib.h>

Chunk* create_chunk() {
    Chunk* chunk = malloc(sizeof(Chunk));
    chunk->data_blocks = malloc(CHUNK_Y * sizeof(Block**));
    for (int y = 0; y < CHUNK_Y; y++) {
        chunk->data_blocks[y] = malloc(CHUNK_X * sizeof(Block*));
        for (int x = 0; x < CHUNK_X; x++) {
            chunk->data_blocks[y][x] = malloc(CHUNK_Z * sizeof(Block));
        }
    }
    return chunk;
}

void Create_world(World* world) {
    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int z = 0; z < WORLD_SIZE; z++) {
            world->data_chunks[x][z] = create_chunk();
        }
    }
}

void destroy_world(World* world) {
    for (int x = 0; x < WORLD_SIZE; x++) {
        for (int z = 0; z < WORLD_SIZE; z++) {
            Chunk* chunk = world->data_chunks[x][z];
            if (chunk != NULL) {
                for (int y = 0; y < CHUNK_Y; y++) {
                    for (int i = 0; i < CHUNK_X; i++) {
                        free(chunk->data_blocks[y][i]);
                    }
                    free(chunk->data_blocks[y]);
                }
                free(chunk->data_blocks);
                free(chunk);
                world->data_chunks[x][z] = NULL;
            }
        }
    }
    free(world);
}