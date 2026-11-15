#include "include.h"
#include "maze.h"
#include "robot.h"
#include "solve.h"

/*
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
*/

void solveMazeHug(Robot* robot, Maze* maze) {
    while (!atMarker(robot, maze)) {
        if (canMoveLeft(robot, maze)) {
            left(robot, maze);
            forward(robot, maze);
        } else if (canMoveForward(robot, maze)) {
            forward(robot, maze);
        } else {
            right(robot, maze);
        }
    }
}

void solveMazeHugRight(Robot* robot, Maze* maze) {
    while (!atMarker(robot, maze)) {
        if (canMoveRight(robot, maze)) {
            right(robot, maze);
            forward(robot, maze);
        } else if (canMoveForward(robot, maze)) {
            forward(robot, maze);
        } else {
            left(robot, maze);
        }
    }
}

void solveMazeDFS(Robot* robot, Maze* maze) {

}

