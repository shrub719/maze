#include "maze.h"

typedef enum {
    NORTH = 0, EAST, SOUTH, WEST
} Direction;

// which actions to actually animate as a single frame
typedef enum {
    STEPS = 0, TURNS
} Animation;

typedef enum {
    TWODEE = 0, THREEDEE
} DrawMode;

typedef struct {
    CellRef pos;
    Direction dir;
    Animation anim;
    DrawMode mode;
} Robot;

void initRobot(Robot* robot, DrawMode mode);
void drawRobot(Robot* robot, Maze* maze);
void right(Robot* robot, Maze* maze);
void left(Robot* robot, Maze* maze);
void forward(Robot* robot, Maze* maze);
int atMarker(Robot* robot, Maze* maze);
int canMoveForward(Robot* robot, Maze* maze);
void advanceRobot(Robot* robot, Maze* maze);

