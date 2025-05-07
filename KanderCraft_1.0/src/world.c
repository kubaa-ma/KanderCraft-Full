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

Chunk** allocate_chunk(const Player_config *data) {
    int size = data->render_distance;

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
    for (int i = 0; i < data->render_distance; i++){
        for (int j = 0; j < data->render_distance; j++){
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

                        Block *block = &data_world->data_chunks[i][j].data_blocks[k][l][m];
                        block->type = BLOCK_DIRT;

                        if (k == 0 || k == CHUNK_DEPTH - 1) {
                            block->type = BLOCK_AIR;
                        }

                        if (block->type != BLOCK_AIR) {
                            block->features = SOLID | OPAQUE | VISIBLE;

                            Vector3 pos = {
                                (float)(j * CHUNK_WIDTH + l),
                                (float)k,
                                (float)(i * CHUNK_LENGTH + m)
                            };

                            block->box.min = (Vector3){pos.x - 0.5f, pos.y - 0.5f, pos.z - 0.5f};
                            block->box.max = (Vector3){pos.x + 0.5f, pos.y + 0.5f, pos.z + 0.5f};
                        }
                    }
                }
            }
        }
    }
}

void settle_blocks(World *data_world, Player_config *data) {
    for (int i = 0; i < TOTAL_CHUNKS; i++) {
        for (int j = 0; j < TOTAL_CHUNKS; j++) {
            for (int k = 0; k < CHUNK_DEPTH; k++) {
                for (int l = 0; l < CHUNK_WIDTH; l++) {
                    for (int m = 0; m < CHUNK_LENGTH; m++) {

                        Block *block = &data_world->data_chunks[i][j].data_blocks[k][l][m];
                        block->visible_faces = 0;

                        if (k + 1 < CHUNK_DEPTH &&
                            !(data_world->data_chunks[i][j].data_blocks[k + 1][l][m].features & VISIBLE))
                            block->visible_faces |= FACE_TOP;

                        if (k - 1 >= 0 &&
                            !(data_world->data_chunks[i][j].data_blocks[k - 1][l][m].features & VISIBLE))
                            block->visible_faces |= FACE_BOTTOM;

                        if (l + 1 < CHUNK_WIDTH &&
                            !(data_world->data_chunks[i][j].data_blocks[k][l + 1][m].features & VISIBLE))
                            block->visible_faces |= FACE_RIGHT;

                        if (l - 1 >= 0 &&
                            !(data_world->data_chunks[i][j].data_blocks[k][l - 1][m].features & VISIBLE))
                            block->visible_faces |= FACE_LEFT;

                        if (m + 1 < CHUNK_LENGTH &&
                            !(data_world->data_chunks[i][j].data_blocks[k][l][m + 1].features & VISIBLE))
                            block->visible_faces |= FACE_BACK;

                        if (m - 1 >= 0 &&
                            !(data_world->data_chunks[i][j].data_blocks[k][l][m - 1].features & VISIBLE))
                            block->visible_faces |= FACE_FRONT;
                    }
                }
            }
        }
    }
}