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

#include "../include/world.h"
#include "../include/block.h"
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>//Only for windows
#include <errno.h>
#include <string.h>

int copy_file(const char *source_path, const char *dest_path) {
    FILE *src = fopen(source_path, "rb");
    if (!src) {
        perror("Error opening source file");
        return 1;
    }

    FILE *dst = fopen(dest_path, "wb");
    if (!dst) {
        perror("Error creating destination file");
        fclose(src);
        return 1;
    }

    char buffer[4096];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytes, dst);
    }

    fclose(src);
    fclose(dst);
    return 0;
}

int create_world_files(const char *world_name) {
    if (_mkdir(PATH_WORLD_FILES) != 0 && errno != EEXIST) {
        perror("Error creating main folder");
        return 0;
    }

    char path_world[256];
    snprintf(path_world, sizeof(path_world), "%s/%s", PATH_WORLD_FILES, world_name);
    if (_mkdir(path_world) != 0 && errno != EEXIST) {
        perror("Error creating world folder");
    }

    char path_chunks[256];
    snprintf(path_chunks, sizeof(path_chunks), "%s/Chunks", path_world);
    if (_mkdir(path_chunks) != 0 && errno != EEXIST) {
        perror("Error creating 'Chunks' folder");
    }

    char path_icon[256];
    snprintf(path_icon, sizeof(path_icon), "%s/Icon", path_world);
    if (_mkdir(path_icon) != 0 && errno != EEXIST) {
        perror("Error creating 'Icon' folder");
    }

    char dest_icon[256];
    snprintf(dest_icon, sizeof(dest_icon), "%s/Icon/Icon.png", path_world);
    if (copy_file("assets/dirt.png", dest_icon) != 0) {
        printf("Error copying file 'dirt.png' (incompleted)\n");
    }

    return 1;
}

int load_world_files(const char *world_name) {
    FILE *src;

    char world_path[256];
    snprintf(world_path, sizeof(world_path), "WorldFiles/%s/Icon/Icon.png", world_name);

    src = fopen(world_path, "rb");
    if (src == NULL) {
        printf("Creating new world");
        return 1;
    }
    

    fclose(src);
    return 0;
}

int save_chunk(const char *world_name, int i, int j, Chunk *data) {
    char ChunkPath[256];
    snprintf(ChunkPath, sizeof(ChunkPath), "WorldFiles/%s/Chunks/Chunk_%d_%d.dat", world_name, i, j);

    FILE *chunk = fopen(ChunkPath, "wb");
    if (chunk == NULL) {
        perror("Error opening chunk file for writing");
        return 1;
    }

    for (int z = 0; z < CHUNK_DEPTH; z++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int y = 0; y < CHUNK_LENGTH; y++) {
                size_t written = fwrite(&data->data_blocks[z][x][y], sizeof(Block), 1, chunk);
                if (written != 1) {
                    perror("Error writing block");
                    fclose(chunk);
                    return 2;
                }
            }
        }
    }

    fclose(chunk);
    return 0;
}
int save_world(World *world, const char *world_name){
    for(int i = 0; i < TOTAL_CHUNKS; i++){
        for(int j = 0; j < TOTAL_CHUNKS; j++){
            if (save_chunk(world_name, i, j, &world->data_chunks[i][j]) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

int load_chunk(const char *world_name, int i, int j, Chunk *data){
    char ChunkPath[256];
    snprintf(ChunkPath, sizeof(ChunkPath), "WorldFiles/%s/Chunks/Chunk_%d_%d.dat", world_name, i, j);

    FILE *chunk = fopen(ChunkPath, "rb");
    if (chunk == NULL) {
        perror("Error opening chunk file for writing");
        return 1;
    }

    for (int z = 0; z < CHUNK_DEPTH; z++) {
        for (int x = 0; x < CHUNK_WIDTH; x++) {
            for (int y = 0; y < CHUNK_LENGTH; y++) {
                size_t items_read = fread(&data->data_blocks[z][x][y], sizeof(Block), 1, chunk);
                if (items_read != 1) {
                    perror("Error reading block");
                    fclose(chunk);
                    return 2;
                }
            }
        }
    }
    fclose(chunk);
    return 0;

}

void init_world(World *world) {
    for (int x = 0; x < TOTAL_CHUNKS; x++) {
        for (int z = 0; z < TOTAL_CHUNKS; z++) {
            world->data_chunks[x][z].is_loaded = false;
        }
    }
    world->initialized = false;
}

int load_world(World *world, const char *world_name) {
    for (int x = 0; x < TOTAL_CHUNKS; x++) {
        for (int z = 0; z < TOTAL_CHUNKS; z++) {
            if (!world->data_chunks[x][z].is_loaded) {
                if (load_chunk(world_name, x, z, &world->data_chunks[x][z]) != 0) {
                    return 1;
                }
                world->data_chunks[x][z].is_loaded = true;
            }
        }
    }

    world->initialized = true;
    return 0;
}


Block ***allocate_blocks() {
    Block *raw_data = malloc(sizeof(Block) * CHUNK_DEPTH * CHUNK_WIDTH * CHUNK_LENGTH);
    if (!raw_data) {
        printf("Error allocating block data\n");
        return NULL;
    }

    Block ***blocks = malloc(sizeof(Block **) * CHUNK_DEPTH);
    if (!blocks) {
        printf("Error allocating block pointers (z)\n");
        free(raw_data);
        return NULL;
    }

    for (int z = 0; z < CHUNK_DEPTH; z++) {
        blocks[z] = malloc(sizeof(Block *) * CHUNK_WIDTH);
        if (!blocks[z]) {
            printf("Error allocating block pointers (x) at z=%d\n", z);
            for (int i = 0; i < z; i++) free(blocks[i]);
            free(blocks);
            free(raw_data);
            return NULL;
        }

        for (int x = 0; x < CHUNK_WIDTH; x++) {
            blocks[z][x] = raw_data + (z * CHUNK_WIDTH * CHUNK_LENGTH) + (x * CHUNK_LENGTH);
        }
    }

    return blocks;
}

void free_blocks(Block ***blocks) {
    if (!blocks) return;

    Block *raw_data = blocks[0][0];
    for (int z = 0; z < CHUNK_DEPTH; z++) {
        free(blocks[z]);
    }
    free(blocks);
    free(raw_data);
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

void destroy_world(World *data_world){
    for (int i = 0; i < TOTAL_CHUNKS; i++){
        for (int j = 0; j < TOTAL_CHUNKS; j++){
            free_blocks(data_world->data_chunks[i][j].data_blocks);
        }
        free(data_world->data_chunks[i]);
    }
    free(data_world->data_chunks);
}

void world_generator(World *data_world) {
    for (int i = 0; i < TOTAL_CHUNKS; i++) {
        for (int j = 0; j < TOTAL_CHUNKS; j++) {
            data_world->data_chunks[i][j].x = i;
            data_world->data_chunks[i][j].z = j;


            float worldX = (float)(i * CHUNK_WIDTH);
            float worldZ = (float)(j * CHUNK_LENGTH);
            data_world->data_chunks[i][j].bounds.min = (Vector3){ worldX, 0.0f, worldZ };
            data_world->data_chunks[i][j].bounds.max = (Vector3){ worldX + CHUNK_WIDTH, CHUNK_DEPTH, worldZ + CHUNK_LENGTH };

            Block ***blocks = data_world->data_chunks[i][j].data_blocks;
            for (int k = 0; k < CHUNK_DEPTH; k++) {
                for (int l = 0; l < CHUNK_WIDTH; l++) {
                    for (int m = 0; m < CHUNK_LENGTH; m++) {
        
                        blocks[k][l][m].type = BLOCK_DIRT;
    
                        if(k > 6 && k < CHUNK_DEPTH){
                            blocks[k][l][m].type = BLOCK_AIR;

                        }
                        if(k == 6 && k < CHUNK_DEPTH){
                            blocks[k][l][m].type = BLOCK_GRASS;

                        }
                        if (i == 0 && l == 0) {
                            blocks[k][l][m].type = BLOCK_AIR;
                        }
                        if (j == 0 && m == 0) {
                            blocks[k][l][m].type = BLOCK_AIR;
                        }
                        if (k == 0) {
                            blocks[k][l][m].type = BLOCK_AIR;
                        }

                    
                        if (i == TOTAL_CHUNKS - 1 && l == CHUNK_WIDTH - 1) {
                            blocks[k][l][m].type = BLOCK_AIR;
                        }
                        if (j == TOTAL_CHUNKS - 1 && m == CHUNK_LENGTH - 1) {
                            blocks[k][l][m].type = BLOCK_AIR;
                        }

                        if (blocks[k][l][m].type != BLOCK_AIR) {
                            blocks[k][l][m].features = SOLID | OPAQUE | VISIBLE;
    
                            Vector3 pos = {(float)(i * CHUNK_WIDTH + l), (float)k, (float)(j * CHUNK_LENGTH + m)};
                            
                            blocks[k][l][m].box.min = (Vector3){pos.x - 0.0f, pos.y - 0.0f, pos.z - 0.0f};
                            blocks[k][l][m].box.max = (Vector3){pos.x + 1.0f, pos.y + 1.0f, pos.z + 1.0f};
                        } else if(blocks[k][l][m].type == BLOCK_AIR){
                                blocks[k][l][m].features = 0;
                                blocks[k][l][m].visible_faces = 0;
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

                        // FACE_TOP
                        if (y + 1 >= CHUNK_DEPTH || !(world->data_chunks[cx][cz].data_blocks[y + 1][x][z].features & VISIBLE))
                            block->visible_faces |= FACE_TOP;

                        // FACE_BOTTOM
                        if (y - 1 < 0 || !(world->data_chunks[cx][cz].data_blocks[y - 1][x][z].features & VISIBLE))
                            block->visible_faces |= FACE_BOTTOM;

                        // FACE_RIGHT
                        if (x + 1 >= CHUNK_WIDTH) {
                            if (cx + 1 >= TOTAL_CHUNKS || !(world->data_chunks[cx + 1][cz].data_blocks[y][0][z].features & VISIBLE))
                                block->visible_faces |= FACE_RIGHT;
                        } else if (!(world->data_chunks[cx][cz].data_blocks[y][x + 1][z].features & VISIBLE)) {
                            block->visible_faces |= FACE_RIGHT;
                        }

                        // FACE_LEFT
                        if (x - 1 < 0) {
                            if (cx - 1 < 0 || !(world->data_chunks[cx - 1][cz].data_blocks[y][CHUNK_WIDTH - 1][z].features & VISIBLE))
                                block->visible_faces |= FACE_LEFT;
                        } else if (!(world->data_chunks[cx][cz].data_blocks[y][x - 1][z].features & VISIBLE)) {
                            block->visible_faces |= FACE_LEFT;
                        }

                        // FACE_BACK
                        if (z + 1 >= CHUNK_LENGTH) {
                            if (cz + 1 >= TOTAL_CHUNKS || !(world->data_chunks[cx][cz + 1].data_blocks[y][x][0].features & VISIBLE))
                                block->visible_faces |= FACE_BACK;
                        } else if (!(world->data_chunks[cx][cz].data_blocks[y][x][z + 1].features & VISIBLE)) {
                            block->visible_faces |= FACE_BACK;
                        }

                        // FACE_FRONT
                        if (z - 1 < 0) {
                            if (cz - 1 < 0 || !(world->data_chunks[cx][cz - 1].data_blocks[y][x][CHUNK_LENGTH - 1].features & VISIBLE))
                                block->visible_faces |= FACE_FRONT;
                        } else if (!(world->data_chunks[cx][cz].data_blocks[y][x][z - 1].features & VISIBLE)) {
                            block->visible_faces |= FACE_FRONT;
                        }

                    }
                }
            }
        }
    }
}

void DrawChunkCornersRays(Chunk *chunk, Camera3D cam) {
    Vector3 corners[8] = {
        chunk->bounds.min,
        {chunk->bounds.max.x, chunk->bounds.min.y, chunk->bounds.min.z},
        {chunk->bounds.min.x, chunk->bounds.max.y, chunk->bounds.min.z},
        {chunk->bounds.min.x, chunk->bounds.min.y, chunk->bounds.max.z},
        {chunk->bounds.min.x, chunk->bounds.max.y, chunk->bounds.max.z},
        {chunk->bounds.max.x, chunk->bounds.min.y, chunk->bounds.max.z},
        {chunk->bounds.max.x, chunk->bounds.max.y, chunk->bounds.min.z},
        chunk->bounds.max
    };

    for (int i = 0; i < 8; i++) {
        DrawLine3D(cam.position, corners[i], SKYBLUE);
    }
}

