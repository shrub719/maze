#pragma once

typedef struct {
    CellRef cells[STACK];
    int size;
} CellStack;

typedef struct {
    CellRef cells[STACK];
    int size;
} CellArray;

typedef enum {
    PRIM, DFS
} GenAlg;

void genMazePrim(Maze* maze);
void genMazeDFS(Maze* maze);

