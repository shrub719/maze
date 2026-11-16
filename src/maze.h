#pragma once

typedef enum {
    EMPTY = 0, WALL, MARKER
} Cell;

typedef struct {
    int width;
    int height;
    Cell* cells;
} Maze;

typedef struct {
    int x;
    int y;
} CellVec;

typedef struct {
    // sometimes in grid units; sometimes in pixel coords
    float x;
    float y;
} Vec;

Cell getCell(Maze* maze, CellVec cell);
void setCell(Maze* maze, CellVec cell, int c);
CellVec addCellVecs(CellVec c1, CellVec c2);
CellVec scaleCellVec(CellVec cell, float scalar);
void initMaze(Maze* maze, int width, int height);
void uninitMaze(Maze* maze);
void drawMaze(Maze* maze);

