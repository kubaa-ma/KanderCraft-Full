#ifndef BLOCK_H
#define BLOCK_H

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
#include <stdint.h>
#include "world_config.h"
#include <math.h>


#define BLOCK_SIZE (Vector3){BLOCK_SITE_SIZE, BLOCK_SITE_SIZE, BLOCK_SITE_SIZE}





#define FACE_RIGHT (1 << 0)
#define FACE_LEFT (1 << 1)
#define FACE_TOP (1 << 2)
#define FACE_BOTTOM (1 << 3)
#define FACE_BACK (1 << 4)
#define FACE_FRONT (1 << 5)

#define SOLID (1 << 0)
#define OPAQUE (1 << 1)
#define VISIBLE (1 << 2)

typedef uint8_t VisibleFaces;
typedef uint8_t B_features;

#define PLAYER_POSIBLE_PLACE_BLOCKS 2


typedef enum {
    BLOCK_AIR,
    BLOCK_DIRT,
    BLOCK_GRASS,
    BLOCK_STONE,
    BLOCK_DIAMOND,
    BLOCK_WOOD,
    BLOCK_WOOL_BLUE,
    BLOCK_WOOL_GREEN,
    BLOCK_WOOL_ORANGE,
    BLOCK_WOOL_PINK,
    BLOCK_WOOL_RED,
    BLOCK_WOOL_VIOLET
}Blocktype;

typedef struct {

    Blocktype type;
    BoundingBox box;
    VisibleFaces visible_faces;
    B_features features;
}Block;


typedef struct {
    float sour_x[TOTAL_CHUNKS * CHUNK_WIDTH];
    float sour_y[TOTAL_CHUNKS * CHUNK_DEPTH];
    float sour_z[TOTAL_CHUNKS * CHUNK_LENGTH];
}Block_orient;




#endif