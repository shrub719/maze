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
    GenAlg gen = PRIM;
    int width = WIDTH;
    int height = HEIGHT;

    // #noChecks #fragileProgramming
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--pov") == 0) {
            mode = THREEDEE;
        } else if (strcmp(argv[i], "--seed") == 0) {
            seed = atoi(argv[i+1]);
            i++;
        } else if (strcmp(argv[i], "--speed") == 0) {
            speed = atof(argv[i+1]);
            i++;
        } else if (strcmp(argv[i], "--gen") == 0) {
            if (strcmp(argv[i+1], "dfs") == 0) {
                gen = DFS;
            }
            i++;
        } else if (strcmp(argv[i], "--solve") == 0) {
            if (strcmp(argv[i+1], "hugright") == 0) {
                solve = HUGRIGHT;
            } else if (strcmp(argv[i+1], "random") == 0) {
                solve = RANDOM;
            }
            i++;
        } else if (strcmp(argv[i], "--width") == 0) {
            width = atoi(argv[i+1]);
            if (width % 2 == 0) width--;
            i++;
        } else if (strcmp(argv[i], "--height") == 0) {
            height = atoi(argv[i+1]);
            if (height % 2 == 0) height--;
            i++;
        }
    }

    char seedString[STACK];
    sprintf(seedString, "seed: %d\n", seed);
    message(seedString);
    setWindowSize(SIZE*width, SIZE*height);

    Maze maze;
    initMaze(&maze, width, height);
    
    if (gen == PRIM) {
        genMazePrim(&maze);
    } else if (gen == DFS) {
        genMazeDFS(&maze);
    }
    
    clear();
    drawMaze(&maze);
    
    Scene scene;
    scene.x = NULL;
    if (mode == THREEDEE) {
        initScene(&scene, &maze);
        sleep(1000);
        setWindowSize((int)POV_WIDTH, (int)POV_HEIGHT);
    }

    Robot robot;
    initRobot(&robot, mode, speed);
    drawRobot(&robot, &maze, &scene);

    if (solve == HUG) {
        solveMazeHug(&robot, &maze, &scene);
    } else if (solve == HUGRIGHT) {
        solveMazeHugRight(&robot, &maze, &scene);
    } else if (solve == RANDOM) {
        solveMazeRandom(&robot, &maze, &scene);
    }

    uninitScene(&scene);
    uninitMaze(&maze);

    return 0;
}

