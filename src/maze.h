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
} CellRef;

Cell getCell(Maze* maze, CellRef cell);
void setCell(Maze* maze, CellRef cell, int c);
CellRef addCells(CellRef c1, CellRef c2);
void initMaze(Maze* maze, int width, int height);
void uninitMaze(Maze* maze);
void drawMaze(Maze* maze);

