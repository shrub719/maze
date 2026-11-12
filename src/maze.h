#pragma once

typedef struct {
    int width;
    int height;
    char* cells;
} Maze;

typedef struct {
    int x;
    int y;
} CellRef;

typedef struct {
    CellRef cells[STACK];
    int size;
} CellStack;

char getCell(Maze* maze, CellRef cell);
void setCell(Maze* maze, CellRef cell, int c);
void initStack(CellStack* stack);
void pushStack(CellStack* stack, CellRef cell);
CellRef popStack(CellStack* stack);
CellRef addCells(CellRef c1, CellRef c2);
void initMaze(Maze* maze, int width, int height);
void uninitMaze(Maze* maze);
void drawMaze(Maze* maze);

