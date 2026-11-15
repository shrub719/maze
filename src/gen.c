#include "include.h"
#include "maze.h"
#include "gen.h"

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


void clearArray(CellArray* array) {
    array->size = 0;
}

void appendToArray(CellArray* array, CellRef cell) {
    if (array->size >= STACK) {
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
void populateNeighbourArray(CellArray* array, Maze* maze, CellRef cell) {
    CellRef offsets[4] = {
        {2, 0}, {-2, 0},
        {0, 2}, {0, -2}
    };

    for (int i = 0; i < 4; i++) {
        CellRef nb = addCells(cell, offsets[i]);
        if (isCellValid(maze, nb)) {
            if (getCell(maze, nb) != 0) {
                appendToArray(array, offsets[i]);
            }
        }
    }
}

int randomIndex(int size) {
    if (size == 1) return 0;
    return rand() % size;
}

CellRef chooseFromArray(CellArray* array) {
    return array->cells[randomIndex(array->size)];
}

CellRef chooseAndPopFromArray(CellArray* array) {
    if (array->size == 0) return (CellRef){-1, -1}; // TODO bad

    int i = randomIndex(array->size);
    CellRef c = array->cells[i];

    /* 
    // i was really proud of this but its O(n) for no reason
    for (int j = i + 1; j < array->size; j++) {
        array->cells[j - 1] = array->cells[j];
    }
    */

    array->cells[i] = array->cells[array->size - 1];
    array->size--;

    return c;
}

void genMazeDFS(Maze* maze) {
    CellStack stack;
    initStack(&stack);
    CellArray nbs;
    CellRef cell;

    cell.x = 1;
    cell.y = 1;
    setCell(maze, cell, 0);   // mark as visited

    int cont = 1;
    while (cont) {
        clearArray(&nbs);
        populateNeighbourArray(&nbs, maze, cell);    // get list of neighbours
        if (nbs.size == 0) {
            if (cell.x == 1 && cell.y == 1) {
                cont = 0;
                continue;
            }
            cell = popStack(&stack);
        } else {
            pushStack(&stack, cell);  
            CellRef offset = chooseFromArray(&nbs);     // random unvisited neighbour
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

void genMazePrim(Maze* maze) {
    CellArray walls;
    CellRef cell;
    CellArray cells;
    CellRef wall;
    cell.x = 1;
    cell.y = 1;
    setCell(maze, cell, 0);
    populateNeighbourArray(&walls, maze, cell);

    while (walls.size > 0) {
        // TODO 
    }
}

