#pragma once

typedef enum {
    HUG, HUGRIGHT, RANDOM
} SolveAlg;

void solveMazeHug(Robot* robot, Maze* maze, Scene* scene);
void solveMazeHugRight(Robot* robot, Maze* maze, Scene* scene);
void solveMazeRandom(Robot* robot, Maze* maze, Scene* scene);

