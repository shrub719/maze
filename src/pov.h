#pragma once

typedef struct {
    int x0; int y0;
    int x1; int y1;
    int x2; int y2;
    int x3; int y3;
} Quad;

typedef struct {
    int quadCount;
    int x[STACK];
    int y[STACK];
} Scene;

void drawThreeDee(Robot* robot, Maze* maze);

