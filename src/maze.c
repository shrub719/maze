#include <stdlib.h>
#include <time.h>
#include "include/graphics.h"
#include "constants.h"
#include "maze.h"

// TODO: add checks to these
char getCell(Maze* maze, CellRef cell) {
    return maze->cells[cell.y * maze->width + cell.x];
}

void setCell(Maze* maze, CellRef cell, int c) {
    maze->cells[cell.y * maze->width + cell.x] = c;
}

void initStack(CellStack* stack) {
    stack->size = 0;
}

void pushStack(CellStack* stack, CellRef cell) {
    if (stack->size >= 256) {
        message("stack overflow\n");
        return;
    }
    stack->cells[stack->size] = cell;
    stack->size += 1;
}

CellRef popStack(CellStack* stack) {
    if (stack->size == 0) {
        message("stack empty\n");
        return (CellRef){-1, -1};  // this is probably bad; TODO
    }
    stack->size -= 1;
    return stack->cells[stack->size];
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

