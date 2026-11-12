#include "include.h"
#include "maze.h"
#include "robot.h"
#include "solve.h"

void solveMazeHug(Robot* robot, Maze* maze) {
    int checked = 0;
    while (!atMarker(robot, maze)) {
        if (checked) checked = 0;
        else left(robot, maze);

        if (canMoveForward(robot, maze)) {
            forward(robot, maze);
        } else {
            right(robot, maze);
            checked = 1;
        }
    }
}

