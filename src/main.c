#include <stdio.h>
#include <stdlib.h>
#include "include/graphics.h"

static const int SIZE = 25;
static const int WIDTH = 30;
static const int HEIGHT = 20;

typedef struct {
    int width;
    int height;
    char* cells;
} Maze;

char getCell(Maze* maze, int i, int j) {
    return maze->cells[j * maze->width + i];
}

void drawCell(Maze* maze, int i, int j) {
    char cell = getCell(maze, i, j);
    if (cell == 1) {
        setColour(black);
    } else if (cell == 0) {
        setColour(white);
    } else {
        message("invalid colour\n");
        setColour(magenta);
    }

    fillRect(i*SIZE, j*SIZE, (i + 1)*SIZE, (j+1)*SIZE);
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
            drawCell(maze, i, j);
        }
    }
}

int main() {
    // displayImageURL("https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Ftse3.mm.bing.net%2Fth%2Fid%2FOIP.scHvyIKsLexn0eOtLY4PQwAAAA%3Fr%3D0%26pid%3DApi&f=1&ipt=0877f0748ce0d2c32f1483db716648655d0f364d8d4a46f7d7235682cc741b40&ipo=images", 0, 0);

    setWindowSize(SIZE*WIDTH, SIZE*HEIGHT);

    Maze maze;
    initMaze(&maze, WIDTH, HEIGHT);
    
    clear();
    drawMaze(&maze);

    uninitMaze(&maze);

    return 0;
}

