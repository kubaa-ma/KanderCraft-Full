#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"
#include "stdbool.h"


typedef struct{
    bool right_side;
    bool left_side;
    bool top_side;
    bool bottom;
    bool back;
    bool front;
}visibleFaces;

typedef struct {
    
    int x;
    int y;
    int z;
    visibleFaces sides;

    char type;
    BoundingBox cube;
    bool solid;
    bool Opaque;
    bool Visible;
}block;


#endif