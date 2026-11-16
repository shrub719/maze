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

void initRobot(Robot* robot, DrawMode mode, float speed) {
    robot->pos.x = 0;
    robot->pos.y = 1;
    robot->aPos.x = 0.0;
    robot->aPos.y = 1.0;
    robot->dir = EAST;
    robot->aDir = 1.0;
    robot->mode = mode;
    robot->speed = speed;
}

void drawRobot(Robot* robot, Maze* maze, Scene* scene) {
    if (robot->mode == TWODEE) {
        float x = SIZE*robot->aPos.x;
        float y = SIZE*robot->aPos.y;
        int i = 2*robot->dir;

        foreground();
        clear();
        setColour(darkgray);
        fillOval(x+1, y+1, 21, 21);
        setColour(red);
        fillOval(x+circleOffsets[i], y+circleOffsets[i+1], 12, 12);
    } else if (robot->mode == THREEDEE) {
        drawThreeDee(robot, maze, scene);
    }
}

CellVec getForwardCell(Robot* robot) {
    int i = 2*robot->dir;
    return addCellVecs(
        robot->pos,
        (CellVec){directionalOffsets[i], directionalOffsets[i+1]}
    );
}

CellVec getTurnedCell(Robot* robot, int amount) {
    int i = 2*((robot->dir + amount) % 4);
    return addCellVecs(
        robot->pos,
        (CellVec){directionalOffsets[i], directionalOffsets[i+1]}
    );
}

// used to animate moving forwards
Vec interpolateForwardCell(Robot* robot, float f) {
    int i = 2*robot->dir;
    return (Vec){
        (float)robot->pos.x + f*(float)directionalOffsets[i],
        (float)robot->pos.y + f*(float)directionalOffsets[i+1]
    };
}

void turn(Robot* robot, Maze* maze, Scene* scene, int amount) {
    Direction newDir = (robot->dir + amount) % 4;
    robot->dir = newDir;

    for (int i = 0; i <= FPS; i++) {
        robot->aDir += (float)amount / FPS;
        drawRobot(robot, maze, scene);
        sleep(SLEEP / robot->speed); 
    }

    robot->aDir = (float)newDir;
    drawRobot(robot, maze, scene);
}

void right(Robot* robot, Maze* maze, Scene* scene) {
    turn(robot, maze, scene, 1);
}

void left(Robot* robot, Maze* maze, Scene* scene) {
    turn(robot, maze, scene, -1);
}

void forward(Robot* robot, Maze* maze, Scene* scene) {
    if (!canMoveForward(robot, maze)) {
        message("cannot move forward\n");
        return;
    }

    for (int i = 0; i <= FPS; i++) {
        float f = (float)i / FPS;
        robot->aPos = interpolateForwardCell(robot, f);
        drawRobot(robot, maze, scene);
        sleep(SLEEP / robot->speed);
    }

    CellVec forwardCell = getForwardCell(robot);
    robot->aPos.x = (float)forwardCell.x;
    robot->aPos.y = (float)forwardCell.y;
    // (Vec)(forwardCell)???
    robot->pos = forwardCell;
    drawRobot(robot, maze, scene);
}

int atMarker(Robot* robot, Maze* maze) {
    return (getCell(maze, robot->pos) == MARKER);
}

int canMoveForward(Robot* robot, Maze* maze) {
    return (getCell(maze, getForwardCell(robot)) != WALL);
}

// these are effectively the same as left(); canMoveForward(); right();
// and vice-versa; i've used them so the program doesn't give me a headache
// when running

int canMoveRight(Robot* robot, Maze* maze) {
    return (getCell(maze, getTurnedCell(robot, 1)) != WALL);
}

int canMoveLeft(Robot* robot, Maze* maze) {
    return (getCell(maze, getTurnedCell(robot, -1)) != WALL);
}

