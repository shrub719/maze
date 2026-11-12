#pragma once

typedef struct {
    CellRef cells[4];
    int size;
} NeighbourArray;

void genMazeDFS(Maze* maze);

