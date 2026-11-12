#include "include.h"
#include "maze.h"
#include "gen.h"
#include "robot.h"

int main() {
    // displayImageURL("https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Ftse3.mm.bing.net%2Fth%2Fid%2FOIP.scHvyIKsLexn0eOtLY4PQwAAAA%3Fr%3D0%26pid%3DApi&f=1&ipt=0877f0748ce0d2c32f1483db716648655d0f364d8d4a46f7d7235682cc741b40&ipo=images", 0, 0);

    srand(3);
    setWindowSize(SIZE*WIDTH, SIZE*HEIGHT);

    Maze maze;
    initMaze(&maze, WIDTH, HEIGHT);
    
    clear();
    genMazeDFS(&maze);
    drawMaze(&maze);

    Robot robot;
    initRobot(&robot);
    drawRobot(&robot);

    while (1) {
        forward(&robot, &maze);
        drawRobot(&robot);
        sleep(1000);
    }

    uninitMaze(&maze);

    return 0;
}

