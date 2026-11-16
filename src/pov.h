#pragma once
#include "maze.h"

typedef Vec Quad[4];

typedef struct {
    // normalised
    float x;
    float height;
} Edge;
typedef Edge Wall[2];

typedef struct {
    int quadCount;
    int x[STACK*4];
    int y[STACK*4];
} Scene;

void drawThreeDee(Robot* robot, Maze* maze);

