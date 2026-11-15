#pragma once

typedef enum {
    HUG, HUGRIGHT, DFS
} SolveAlg;

void solveMazeHug(Robot* robot, Maze* maze);
void solveMazeHugRight(Robot* robot, Maze* maze);
void solveMazeDFS(Robot* robot, Maze* maze);

