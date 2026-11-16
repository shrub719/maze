#pragma once

typedef struct {
    CellVec cells[STACK];
    int size;
} CellStack;

typedef struct {
    CellVec cells[STACK];
    int size;
} CellArray;

typedef enum {
    PRIM, DFS
} GenAlg;

void genMazePrim(Maze* maze);
void genMazeDFS(Maze* maze);

