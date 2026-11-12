#include "include.h"
#include "robot.h"
#include "maze.h"

static const int circleOffsets[] = {
    7, 2,
    11, 6,
    7, 11,
    2, 7
};

static const int directionalOffsets[] = {
    0, 1, 
    1, 0, 
    0, -1, 
    -1, 0
};

void initRobot(Robot* robot) {
    robot->pos.x = 0;
    robot->pos.y = 1;
    robot->dir = EAST;
}

void drawRobot(Robot* robot) {
    int x = SIZE*robot->pos.x;
    int y = SIZE*robot->pos.y;
    int i = 2*robot->dir;

    foreground();
    clear();
    setColour(darkgray);
    fillOval(x+1, y+1, 21, 21);
    setColour(red);
    fillOval(x+circleOffsets[i], y+circleOffsets[i+1], 12, 12);
}

CellRef getForwardCell(Robot* robot) {
    int i = 2*robot->dir;
    return addCells(
        robot->pos,
        (CellRef){directionalOffsets[i], directionalOffsets[i+1]}
    );
}

void right(Robot* robot) {
    robot->dir += 3;
}

void left(Robot* robot) {
    robot->dir += 1;
}

// does not check
void forward(Robot* robot, Maze* maze) {
    if (!canMoveForward(robot, maze)) {
        message("cannot move forward\n");
        return;
    }

    robot->pos = getForwardCell(robot);
}

int atMarker(Robot* robot, Maze* maze) {
    return (getCell(maze, robot->pos) == 3);
}

int canMoveForward(Robot* robot, Maze* maze) {
    return (getCell(maze, getForwardCell(robot)) == 0);
}

