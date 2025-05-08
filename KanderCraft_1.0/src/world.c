#include "../include/world.h"
#include "../include/block.h"
#include <stdio.h>
#include <stdlib.h>

Block ***allocate_blocks() {
    Block ***blocks = malloc(CHUNK_DEPTH * sizeof(Block **));
    if (!blocks) {
        printf("Error allocating block depth\n");
        return NULL;
    }

    for (int z = 0; z < CHUNK_DEPTH; z++) {
        blocks[z] = malloc(CHUNK_WIDTH * sizeof(Block *));
        if (!blocks[z]) {
            printf("Error allocating block width at depth %d\n", z);
            for (int i = 0; i < z; i++) {
                for (int j = 0; j < CHUNK_WIDTH; j++) {
                    free(blocks[i][j]);
                }
                free(blocks[i]);
            }
            free(blocks);
            return NULL;
        }

        for (int x = 0; x < CHUNK_WIDTH; x++) {
            blocks[z][x] = malloc(CHUNK_LENGTH * sizeof(Block));
            if (!blocks[z][x]) {
                printf("Error allocating block length at depth %d, width %d\n", z, x);

                for (int i = 0; i <= z; i++) {
                    for (int j = 0; j < (i == z ? x : CHUNK_WIDTH); j++) {
                        free(blocks[i][j]);
                    }
                    free(blocks[i]);
                }
                free(blocks);
                return NULL;
            }
        }
    }

    return blocks;
}

void free_blocks(Block ***blocks) {
    for (int z = 0; z < CHUNK_DEPTH; z++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            free(blocks[z][x]);
        }
        free(blocks[z]);
    }
    free(blocks);
}

Chunk** allocate_chunk() {
    int size = TOTAL_CHUNKS;

    Chunk** data_chunks = malloc(size * sizeof(Chunk*));
    if (!data_chunks) {
        printf("Error allocating chunk rows\n");
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        data_chunks[i] = malloc(size * sizeof(Chunk));
        if (!data_chunks[i]) {
            printf("Error allocating chunk columns at row %d\n", i);
            for (int j = 0; j < i; j++) free(data_chunks[j]);
            free(data_chunks);
            return NULL;
        }

        for (int j = 0; j < size; j++) {
            data_chunks[i][j].data_blocks = allocate_blocks();
            if (!data_chunks[i][j].data_blocks) {
                printf("Error allocating blocks for chunk [%d][%d]\n", i, j);
                for (int a = 0; a <= i; a++) {
                    for (int b = 0; b < (a == i ? j : size); b++) {
                        free_blocks(data_chunks[a][b].data_blocks);
                    }
                    free(data_chunks[a]);
                }
                free(data_chunks);
                return NULL;
            }
        }
    }

    return data_chunks;
}

void destroy_world(World *data_world, const Player_config *data){
    for (int i = 0; i < TOTAL_CHUNKS; i++){
        for (int j = 0; j < TOTAL_CHUNKS; j++){
            free_blocks(data_world->data_chunks[i][j].data_blocks);
        }
        free(data_world->data_chunks[i]);
    }
    free(data_world->data_chunks);
}

void world_generator(World *data_world, Player_config *data) {
    for (int i = 0; i < TOTAL_CHUNKS; i++) {
        for (int j = 0; j < TOTAL_CHUNKS; j++) {
            for (int k = 0; k < CHUNK_DEPTH; k++) {
                for (int l = 0; l < CHUNK_WIDTH; l++) {
                    for (int m = 0; m < CHUNK_LENGTH; m++) {
    
                        Block ***blocks = data_world->data_chunks[i][j].data_blocks;
    
                        blocks[k][l][m].type = BLOCK_DIRT;
    
                        if (
                            l == 0 || l == CHUNK_WIDTH - 1 ||
                            m == 0 || m == CHUNK_LENGTH - 1 ||
                            k == 0 || k == CHUNK_DEPTH - 1 
                        ) {
                            blocks[k][l][m].type = BLOCK_AIR;
                        }

                        if (blocks[k][l][m].type != BLOCK_AIR) {
                            blocks[k][l][m].features = SOLID | OPAQUE | VISIBLE;
    
                            Vector3 pos = {
                                (float)(j * CHUNK_WIDTH + l),
                                (float)k,
                                (float)(i * CHUNK_LENGTH + m)
                            };
    
                            blocks[k][l][m].box.min = (Vector3){pos.x - 0.0f, pos.y - 0.0f, pos.z - 0.0f};
                            blocks[k][l][m].box.max = (Vector3){pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f};
                        }
                    }
                }
            }
        }
    }    
}

void settle_blocks(World *world) {
    for (int cx = 0; cx < TOTAL_CHUNKS; cx++) {
        for (int cz = 0; cz < TOTAL_CHUNKS; cz++) {
            for (int y = 0; y < CHUNK_DEPTH; y++) {
                for (int x = 0; x < CHUNK_WIDTH; x++) {
                    for (int z = 0; z < CHUNK_LENGTH; z++) {

                        Block *block = &world->data_chunks[cx][cz].data_blocks[y][x][z];

                        if (!(block->features & VISIBLE)) {
                            block->visible_faces = 0;
                            continue;
                        }

                        block->visible_faces = 0;

                        if (y + 1 >= CHUNK_DEPTH || !(world->data_chunks[cx][cz].data_blocks[y + 1][x][z].features & VISIBLE))
                            block->visible_faces |= FACE_TOP;

                        if (y - 1 < 0 || !(world->data_chunks[cx][cz].data_blocks[y - 1][x][z].features & VISIBLE))
                            block->visible_faces |= FACE_BOTTOM;

                        if (x + 1 >= CHUNK_WIDTH || !(world->data_chunks[cx][cz].data_blocks[y][x + 1][z].features & VISIBLE))
                            block->visible_faces |= FACE_RIGHT;

                        if (x - 1 < 0 || !(world->data_chunks[cx][cz].data_blocks[y][x - 1][z].features & VISIBLE))
                            block->visible_faces |= FACE_LEFT;

                        if (z + 1 >= CHUNK_LENGTH || !(world->data_chunks[cx][cz].data_blocks[y][x][z + 1].features & VISIBLE))
                            block->visible_faces |= FACE_BACK;

                        if (z - 1 < 0 || !(world->data_chunks[cx][cz].data_blocks[y][x][z - 1].features & VISIBLE))
                            block->visible_faces |= FACE_FRONT;
                    }
                }
            }
        }
    }
}


