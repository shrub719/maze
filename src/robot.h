#include "maze.h"

typedef enum {
    NORTH = 0, EAST, SOUTH, WEST
} Direction;

typedef enum {
    STEPS = 0, TURNS
} Animation;

typedef struct {
    CellRef pos;
    Direction dir;
    Animation anim;
} Robot;

void initRobot(Robot* robot);
void drawRobot(Robot* robot);
void right(Robot* robot);
void left(Robot* robot);
void forward(Robot* robot, Maze* maze);
int atMarker(Robot* robot, Maze* maze);
int canMoveForward(Robot* robot, Maze* maze);
void advanceRobot(Robot* robot);

