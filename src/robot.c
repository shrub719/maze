#include "include.h"
#include "robot.h"
#include "maze.h"
#include "pov.h"

static const int circleOffsets[] = {
    7, 2,
    11, 6,
    7, 11,
    1, 6
};

static const int directionalOffsets[] = {
    0, -1, 
    1, 0, 
    0, 1, 
    -1, 0
};

void initRobot(Robot* robot, DrawMode mode) {
    robot->pos.x = 0;
    robot->pos.y = 1;
    robot->dir = EAST;
    robot->anim = STEPS;
    robot->mode = mode;
}

void drawRobot(Robot* robot, Maze* maze) {
    if (robot->mode == TWODEE) {
        int x = SIZE*robot->pos.x;
        int y = SIZE*robot->pos.y;
        int i = 2*robot->dir;

        foreground();
        clear();
        setColour(darkgray);
        fillOval(x+1, y+1, 21, 21);
        setColour(red);
        fillOval(x+circleOffsets[i], y+circleOffsets[i+1], 12, 12);
    } else if (robot->mode == THREEDEE) {
        drawThreeDee(robot, maze);
    }
}

CellRef getForwardCell(Robot* robot) {
    int i = 2*robot->dir;
    return addCells(
        robot->pos,
        (CellRef){directionalOffsets[i], directionalOffsets[i+1]}
    );
}

void right(Robot* robot, Maze* maze) {
    robot->dir = (robot->dir + 1) % 4;
    if (robot->anim >= TURNS) advanceRobot(robot, maze);
}

void left(Robot* robot, Maze* maze) {
    robot->dir = (robot->dir + 3) % 4;
    if (robot->anim >= TURNS) advanceRobot(robot, maze);
}

// does not check
void forward(Robot* robot, Maze* maze) {
    if (!canMoveForward(robot, maze)) {
        message("cannot move forward\n");
        return;
    }

    robot->pos = getForwardCell(robot);
    if (robot->anim >= STEPS) advanceRobot(robot, maze);
}

int atMarker(Robot* robot, Maze* maze) {
    return (getCell(maze, robot->pos) == MARKER);
}

int canMoveForward(Robot* robot, Maze* maze) {
    return (getCell(maze, getForwardCell(robot)) != WALL);
}

void advanceRobot(Robot* robot, Maze* maze) {
    drawRobot(robot, maze);
    sleep(SLEEP);
}

