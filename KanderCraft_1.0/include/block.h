#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"
#include "stdbool.h"
#include <stdint.h>

#define FACE_RIGHT (1 << 0)
#define FACE_LEFT (1 << 1)
#define FACE_TOP (1 << 2)
#define FACE_BOTTOM (1 << 3)
#define FACE_BACK (1 << 4)
#define FACE_FRONT (1 << 5)

typedef uint8_t VisibleFaces;

typedef enum {
    BLOCK_AIR,
    BLOCK_DIRT
}Blocktype;

typedef struct {
    
    int x;
    int y;
    int z;

    Blocktype type;
    BoundingBox cube;
    bool solid;
    bool opaque;
    bool visible;
    VisibleFaces data;
}Block;


#endif