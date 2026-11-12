#pragma once

typedef struct {
    CellRef cells[4];
    int size;
} NeighbourArray;

typedef struct {
    CellRef cells[STACK];
    int size;
} CellStack;

void genMazeDFS(Maze* maze);

