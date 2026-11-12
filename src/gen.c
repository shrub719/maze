#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "maze.h"
#include "gen.h"
#include "include/graphics.h"

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
            if (getCell(maze, nb) != 0) {
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
    setCell(maze, cell, 0);   // mark as visited

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
            setCell(maze, step, 0);
            setCell(maze, cell, 0);
            // TODO: also fill the one it jumps over
        }
    }

    setCell(maze, (CellRef){0, 1}, 0);
    setCell(maze, (CellRef){maze->width-1, maze->height-2}, 2);
}

