#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "include/graphics.h"

static const int SIZE = 25;
static const int WIDTH = 25;
static const int HEIGHT = 19;

#define STACK 256

typedef struct {
    int width;
    int height;
    char* cells;
} Maze;

// TODO: add checks to these
// TODO: standardise so they all use CellRef
char getCell(Maze* maze, int i, int j) {
    return maze->cells[j * maze->width + i];
}

void setCell(Maze* maze, int i, int j, int c) {
    maze->cells[j * maze->width + i] = c;
}

typedef struct {
    int x;
    int y;
} CellRef;

typedef struct {
    CellRef cells[STACK];
    int size;
} CellStack;

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
        return (CellRef){INT_MAX, INT_MAX};  // this is probably bad; TODO
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

typedef struct {
    CellRef cells[4];
    int size;
} NeighbourArray;

void clearArray(NeighbourArray* array) {
    array->size = 0;
}

void addArray(NeighbourArray* array, CellRef cell) {
    if (array->size >= 4) {
        message("array overflow\n");
        return;
    }
    array->cells[array->size] = cell;
    array->size += 1;
}

void drawCell(Maze* maze, int i, int j) {
    char cell = getCell(maze, i, j);
    if (cell == 1) {
        setColour(black);
    } else if (cell == 0) {
        setColour(white);
    } else if (cell == 2) { 
        setColour(green);
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

int isCellValid(Maze* maze, CellRef cell) {
    return (
        0 < cell.x && cell.x < maze->width - 1      // is the 0 necessary? is int signed?
     && 0 < cell.y && cell.y < maze->height - 1
    );
}

// TODO: the offsets are always the same. maybe just have it return a quadruplet
// of bools?
void populateArray(NeighbourArray* array, Maze* maze, CellRef cell) {
    clearArray(array);

    CellRef offsets[4] = {
        {2, 0}, {-2, 0},
        {0, 2}, {0, -2}
    };

    for (int i = 0; i < 4; i++) {
        CellRef nb = addCells(cell, offsets[i]);
        if (isCellValid(maze, nb)) {
            if (getCell(maze, nb.x, nb.y) != 0) {
                addArray(array, offsets[i]);
            }
        }
    }
}

CellRef chooseArray(NeighbourArray* array) {
    if (array->size == 1) {
        return array->cells[0];
    }

    int c = rand() % array->size;
    return array->cells[c];
}

void genMazeDFS(Maze* maze) {
    CellStack stack;
    initStack(&stack);
    NeighbourArray nbs;
    CellRef cell;

    cell.x = 1;
    cell.y = 1;
    setCell(maze, cell.x, cell.y, 0);   // mark as visited
                                        // TODO: do we need to??

    int cont = 1;
    while (cont) {
        populateArray(&nbs, maze, cell);    // get list of neighbours
        if (nbs.size == 0) {
            if (cell.x == 1 && cell.y == 1) cont = 0;
            cell = popStack(&stack);
        } else {
            pushStack(&stack, cell);  
            CellRef offset = chooseArray(&nbs);     // random unvisited neighbour
            CellRef step = {cell.x + offset.x/2, cell.y + offset.y/2};  // nicer way of doing this; TODO
            cell = addCells(cell, offset);
            setCell(maze, step.x, step.y, 0);
            setCell(maze, cell.x, cell.y, 0);
            // TODO: also fill the one it jumps over
        }
    }

    setCell(maze, 0, 1, 0);
    setCell(maze, maze->width-1, maze->height-2, 2);
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

    srand(3);
    setWindowSize(SIZE*WIDTH, SIZE*HEIGHT);

    Maze maze;
    initMaze(&maze, WIDTH, HEIGHT);
    
    clear();
    genMazeDFS(&maze);
    drawMaze(&maze);

    uninitMaze(&maze);

    return 0;
}

