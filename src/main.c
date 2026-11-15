#include "include.h"
#include "maze.h"
#include "gen.h"
#include "robot.h"
#include "solve.h"
#include <string.h>
#include <time.h>

int main(int argc, char** argv) {
    displayImageURL("https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Ftse3.mm.bing.net%2Fth%2Fid%2FOIP.scHvyIKsLexn0eOtLY4PQwAAAA%3Fr%3D0%26pid%3DApi&f=1&ipt=0877f0748ce0d2c32f1483db716648655d0f364d8d4a46f7d7235682cc741b40&ipo=images", 0, 0);

    DrawMode mode = TWODEE;
    int seed = time(NULL);
    float speed = 1.0;
    SolveAlg solve = HUG;
    GenAlg gen = RDFS;

    // #noChecks #fragileProgramming
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--pov") == 0) {
            mode = THREEDEE;
        } else if (strcmp(argv[i], "--seed") == 0) {
            seed = atoi(argv[i+1]);
        } else if (strcmp(argv[i], "--speed") == 0) {
            speed = atof(argv[i+1]);
        } else if (strcmp(argv[i], "--gen") == 0) {
            // TODO
        } else if (strcmp(argv[i], "--solve") == 0) {
            if (strcmp(argv[i+1], "hugright") == 0) {
                solve = HUGRIGHT;
            } else if (strcmp(argv[i+1], "dfs") == 0) {
                solve = DFS;
            }
        }
    }

    srand(seed);
    setWindowSize(SIZE*WIDTH, SIZE*HEIGHT);

    Maze maze;
    initMaze(&maze, WIDTH, HEIGHT);
    
    if (gen == RDFS) {
        genMazeDFS(&maze);
    }
    
    clear();
    drawMaze(&maze);
    if (mode == THREEDEE) sleep(1000);

    Robot robot;
    initRobot(&robot, mode, speed);
    drawRobot(&robot, &maze);

    if (solve == HUG) {
        solveMazeHug(&robot, &maze);
    } else if (solve == HUGRIGHT) {
        solveMazeHugRight(&robot, &maze);
    } else if (solve == DFS) {
        solveMazeDFS(&robot, &maze);
    }

    uninitMaze(&maze);

    return 0;
}

