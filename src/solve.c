#include "include.h"
#include "maze.h"
#include "robot.h"
#include "solve.h"
#include "pov.h"

/*
void solveMazeHug(Robot* robot, Maze* maze) {
    int checked = 0;
    while (!atMarker(robot, maze, scene)) {
        if (checked) checked = 0;
        else left(robot, maze, scene);

        if (canMoveForward(robot, maze, scene)) {
            forward(robot, maze, scene);
        } else {
            right(robot, maze, scene);
            checked = 1;
        }
    }
}
*/

void solveMazeHug(Robot* robot, Maze* maze, Scene* scene) {
    while (!atMarker(robot, maze)) {
        if (canMoveLeft(robot, maze)) {
            left(robot, maze, scene);
            forward(robot, maze, scene);
        } else if (canMoveForward(robot, maze)) {
            forward(robot, maze, scene);
        } else {
            right(robot, maze, scene);
        }
    }
}

void solveMazeHugRight(Robot* robot, Maze* maze, Scene* scene) {
    while (!atMarker(robot, maze)) {
        if (canMoveRight(robot, maze)) {
            right(robot, maze, scene);
            forward(robot, maze, scene);
        } else if (canMoveForward(robot, maze)) {
            forward(robot, maze, scene);
        } else {
            left(robot, maze, scene);
        }
    }
}

void solveMazeRandom(Robot* robot, Maze* maze, Scene* scene) {
    while (!atMarker(robot, maze)) {
        int l = canMoveLeft(robot, maze);
        int f = canMoveForward(robot, maze);
        int r = canMoveRight(robot, maze);

        int c = rand() % 3;
        if (!l && !f && !r) {
            left(robot, maze, scene);
            left(robot, maze, scene);
        } else if (c == 0 && l) {
            left(robot, maze, scene);
        } else if (c == 2 && r) {
            right(robot, maze, scene);
        }

        if (canMoveForward(robot, maze)) forward(robot, maze, scene);
    }
}

