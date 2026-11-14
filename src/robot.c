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
    robot->aPos.x = 0.0;
    robot->aPos.y = 1.0;
    robot->dir = EAST;
    robot->aDir = 1.0;
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

Vec interpolateForwardCell(Robot* robot, float f) {
    int i = 2*robot->dir;
    return (Vec){
        (float)robot->pos.x + f*(float)directionalOffsets[i],
        (float)robot->pos.y + f*(float)directionalOffsets[i+1]
    };
}

void turn(Robot* robot, Maze* maze, int amount) {
    for (int i = 0; i <= FPS; i++) {
        robot->aDir += (float)amount / FPS;
        //drawRobot(robot, maze);
        sleep(SLEEP); 
    }

    Direction newDir = (robot->dir + amount) % 4;
    robot->aDir = (float)newDir;
    //drawRobot(robot, maze);
    robot->dir = newDir;
}

void right(Robot* robot, Maze* maze) {
    turn(robot, maze, 1);
}

void left(Robot* robot, Maze* maze) {
    turn(robot, maze, -1);
}

// does not check
void forward(Robot* robot, Maze* maze) {
    if (!canMoveForward(robot, maze)) {
        message("cannot move forward\n");
        return;
    }

    for (int i = 0; i <= FPS; i++) {
        float f = (float)i / FPS;
        robot->aPos = interpolateForwardCell(robot, f);
        drawRobot(robot, maze);
        sleep(SLEEP);
    }

    CellRef forwardCell = getForwardCell(robot);
    robot->aPos.x = (float)forwardCell.x;
    robot->aPos.y = (float)forwardCell.y;
    // (Vec)(forwardCell)???
    robot->pos = forwardCell;
    drawRobot(robot, maze);
}

int atMarker(Robot* robot, Maze* maze) {
    return (getCell(maze, robot->pos) == MARKER);
}

int canMoveForward(Robot* robot, Maze* maze) {
    return (getCell(maze, getForwardCell(robot)) != WALL);
}

