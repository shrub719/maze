#pragma once

typedef struct {
    int x;
    int y;
} IVec;
typedef struct {
    float x;
    float y;
    float z;
} FVec;

typedef IVec IQuad[4];
typedef FVec FQuad[4];

typedef struct {
    int quadCount;
    int x[STACK];
    int y[STACK];
} Scene;

void drawThreeDee(Robot* robot, Maze* maze);

