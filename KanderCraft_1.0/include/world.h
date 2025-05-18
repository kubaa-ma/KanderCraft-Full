#ifndef WORLD_H
#define WORLD_H



#include "raylib.h"
#include "stdbool.h"
#include "block.h"
#include "player_configuration.h"
#include "world_config.h"
#include "block.h"

#define PATH_WORLD_FILES "WorldFiles"

typedef struct{
    Block ***data_blocks;
}Chunk;

typedef struct{
    Chunk** data_chunks;
}World;

Chunk** allocate_chunk();
Block ***allocate_blocks();

int copy_file(const char *source_path, const char *dest_path);
int create_world_files(const char *world_name);
int load_world_files(const char *world_name);
void free_blocks(Block ***blocks);
void destroy_world(World *data_world, const Player_config *data);
void world_generator(World *data_world, Player_config *data);
void settle_blocks(World *data_world);


#endif