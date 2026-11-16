#include "include.h"
#include <time.h>
#include "maze.h"

Cell getCell(Maze* maze, CellVec cell) {
    int i = cell.y * maze->width + cell.x;
    if (i >= maze->width * maze->height || i < 0) return -1;

    return maze->cells[i];
}

void setCell(Maze* maze, CellVec cell, int c) {
    int i = cell.y * maze->width + cell.x;
    if (i >= maze->width * maze->height || i < 0) return;

    maze->cells[i] = c;
}

CellVec addCellVecs(CellVec c1, CellVec c2) {
    return (CellVec){
        c1.x + c2.x,
        c1.y + c2.y
    };
}

CellVec scaleCellVec(CellVec cell, float scalar) {
    return (CellVec){
        (int)(cell.x * scalar),
        (int)(cell.y * scalar)
    };
}

void drawCell(Maze* maze, CellVec cell) {
    Cell c = getCell(maze, cell);
    if (c == WALL) {
        setColour(black);
    } else if (c == EMPTY) {
        setColour(white);
    } else if (c == MARKER) { 
        setColour(green);
    } else {
        message("invalid colour\n");
        setColour(magenta);
    }

    fillRect(cell.x*SIZE, cell.y*SIZE, (cell.x + 1)*SIZE, (cell.y+1)*SIZE);
}

void initMaze(Maze* maze, int width, int height) {
    maze->width = width;
    maze->height = height;
    int count = width * height;
    maze->cells = malloc(count * sizeof(Cell));
    for (int i = 0; i < count; i++) {
        maze->cells[i] = 1;
    }
}

void uninitMaze(Maze* maze) {
    free(maze->cells);
}

void drawMaze(Maze* maze) {
    background();
    for (int i = 0; i < maze->width; i++)  {
        for (int j = 0; j < maze->height; j++) {
            drawCell(maze, (CellVec){i, j});
        }
    }
}

