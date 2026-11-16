#include "maze.h"

typedef enum {
    NORTH = 0, EAST, SOUTH, WEST
} Direction;

typedef enum {
    TWODEE = 0, THREEDEE
} DrawMode;

typedef struct {
    CellVec pos;
    Vec aPos;       // animated/interpolated
    Direction dir;
    float aDir;     // animated/interpolated
    DrawMode mode;
    float speed;
} Robot;

#include "pov.h"

void initRobot(Robot* robot, DrawMode mode, float speed);
void drawRobot(Robot* robot, Maze* maze, Scene* scene);
void right(Robot* robot, Maze* maze, Scene* scene);
void left(Robot* robot, Maze* maze, Scene* scene);
void forward(Robot* robot, Maze* maze, Scene* scene);
int atMarker(Robot* robot, Maze* maze);
int canMoveForward(Robot* robot, Maze* maze);
int canMoveLeft(Robot* robot, Maze* maze);
int canMoveRight(Robot* robot, Maze* maze);

