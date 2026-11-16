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
    int* x;
    int* y;
} Scene;

void drawThreeDee(Robot* robot, Maze* maze, Scene* scene);
void clearScene(Scene* scene);
void initScene(Scene* scene, Maze* maze);
void uninitScene(Scene* scene);

