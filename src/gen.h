#pragma once

typedef struct {
    CellRef cells[4];
    int size;
} NeighbourArray;

typedef struct {
    CellRef cells[STACK];
    int size;
} CellStack;

typedef enum {
    RDFS
} GenAlg;

void genMazeDFS(Maze* maze);

