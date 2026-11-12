#include "include.h"
#include <time.h>
#include "maze.h"

// TODO: add checks to these
char getCell(Maze* maze, CellRef cell) {
    int i = cell.y * maze->width + cell.x;
    if (i >= maze->width * maze->height || i < 0) return -1;

    return maze->cells[i];
}

void setCell(Maze* maze, CellRef cell, int c) {
    int i = cell.y * maze->width + cell.x;
    if (i >= maze->width * maze->height || i < 0) return;

    maze->cells[i] = c;
}
CellRef addCells(CellRef c1, CellRef c2) {
    return (CellRef){
        c1.x + c2.x,
        c1.y + c2.y
    };
}

void drawCell(Maze* maze, CellRef cell) {
    char c = getCell(maze, cell);
    if (c == 1) {
        setColour(black);
    } else if (c == 0) {
        setColour(white);
    } else if (c == 2) { 
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
    maze->cells = malloc(count * sizeof(char));
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
            drawCell(maze, (CellRef){i, j});
        }
    }
}

