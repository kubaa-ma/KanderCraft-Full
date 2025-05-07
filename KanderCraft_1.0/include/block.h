#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"
#include "stdbool.h"
#include <stdint.h>

#define BLOCK_SITE_SIZE 1.0f
#define BLOCK_SIZE (Vector3){BLOCK_SITE_SIZE, BLOCK_SITE_SIZE, BLOCK_SITE_SIZE}

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
#define ROT_ANGLE_FRONT 90.0f
#define ROT_ANGLE_BACK 270.0f

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

typedef enum {
    BLOCK_AIR,
    BLOCK_DIRT
}Blocktype;

typedef struct {

    Blocktype type;
    BoundingBox box;
    VisibleFaces visible_faces;
    B_features features;
}Block;


#endif