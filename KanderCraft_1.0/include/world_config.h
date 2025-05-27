#pragma once

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

#define TOTAL_CHUNKS 2

#define BLOCK_SITE_SIZE 0.1f

#define CHUNK_WIDTH 17 //Only Odd numbers
#define CHUNK_LENGTH 17
#define CHUNK_DEPTH 70
#define MAX_SIZE CHUNK_DEPTH * TOTAL_CHUNKS //ONLY IF CHUNK_WIDTH = CHUNK_LENGTH

#define NEAR_PLANE 0.1f
#define FAR_PLANE 20.0f


#define ROT_RIGHT_SITE (Vector3){0.0f, 0.0f, 1.0f}
#define ROT_LEFT_SITE (Vector3){0.0f, 0.0f, 1.0f}
#define ROT_TOP_SITE (Vector3){0.0f, 0.0f, 0.0f}
#define ROT_BOTTOM_SITE (Vector3){0.0f, 0.0f, 90.0f}
#define ROT_FRONT_SITE (Vector3){90.0f, 0.0f, 0.0f}
#define ROT_BACK_SITE (Vector3){1.0f, 0.0f, 0.0f}

#define ROT_ANGLE_RIGHT -90.0f
#define ROT_ANGLE_LEFT 90.0f
#define ROT_ANGLE_TOP 0.0f
#define ROT_ANGLE_BOTTOM 180.0f
#define ROT_ANGLE_FRONT -90.0f
#define ROT_ANGLE_BACK -270.0f

typedef struct{
    int cx; 
    int cz; 
    int y;
    int x;
    int z;
}Vector5;