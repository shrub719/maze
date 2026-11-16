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

static const CellRef offsets[4] = {
    {1, 0}, {-1, 0},
    {0, 1}, {0, -1}
};

void populateNeighbourArray(CellArray* array, Maze* maze, CellRef cell) {
    for (int i = 0; i < 4; i++) {
        CellRef nb = addCells(cell, scaleCell(offsets[i], 2.0));
        if (isCellValid(maze, nb)) {
            if (getCell(maze, nb) != 0) {
                appendToArray(array, offsets[i]);
            }
        }
    }
}

void populateWallArray(CellArray* array, Maze* maze, CellRef cell) {
    printf("populating wall of (%d, %d)\n", cell.x, cell.y);
    for (int i = 0; i < 4; i++) {
        CellRef w = addCells(cell, offsets[i]);
        printf("checking (%d, %d): ", w.x, w.y);
        if (isCellValid(maze, scaleCell(w, 2.0))) {
            printf("valid ");
            if (getCell(maze, w) == 1) {
                printf("wall ");
                appendToArray(array, w);
            }
        }
        printf("\n");
    }
}

// TODO: should not look in all 4 directions!! 
void populateDividingArray(CellArray* array, int* visitedCount, Maze* maze, CellRef cell) {
    printf("populating dividing cells of (%d, %d)\n", cell.x, cell.y);
    for (int i = 0; i < 4; i++) {
        CellRef d = addCells(cell, offsets[i]);
        printf("checking (%d, %d): ", d.x, d.y);
        if (d.x == 0 && d.y == 1) *visitedCount += 1;   // special case for entry wall
                                                        //
        if (isCellValid(maze, scaleCell(d, 2.0))) {
            printf("valid ");
            if (getCell(maze, d) == 0) *visitedCount += 1;
            else appendToArray(array, d);

            if (getCell(maze, d) == 0) printf("visited ");
            else printf("appended ");
        }
        printf("\n");
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
            CellRef step = addCells(cell, offset);
            cell = addCells(cell, scaleCell(offset, 2.0));
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
    cell.x = 0;
    cell.y = 1;
    setCell(maze, cell, 0);
    populateWallArray(&walls, maze, cell);

    while (walls.size > 0) {
        printf("%d walls left\n", walls.size);
        wall = chooseAndPopFromArray(&walls);
        clearArray(&cells);
        int visitedCount = 0;
        populateDividingArray(&cells, &visitedCount, maze, wall);
        printf("visited %d\n", visitedCount);
        
        if (visitedCount == 1) {
            setCell(maze, wall, 0);
            for (int i = 0; i < cells.size; i++) {
                cell = cells.cells[i];
                setCell(maze, cell, 0);
                populateWallArray(&walls, maze, cell);
            }
        }
    }
}

