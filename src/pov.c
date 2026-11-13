#include "include.h"
#include "maze.h"
#include "robot.h"
#include "pov.h"

void clearScene(Scene* scene) {
    scene->quadCount = 0;
}

void appendToScene(Scene* scene, IQuad quad) {
    int i = scene->quadCount * 4;
    int* quadPtr = (int*)quad;      // sick pointer stuff B4
                                    //                    ^ this is a dog with shades

    for (int j = 0; j < 4; j++) {
        scene->x[i + j] = quadPtr[2*j];
        scene->y[i + j] = quadPtr[2*j + 1];
    }

    scene->quadCount += 1;
}

void drawScene(Scene* scene) {
    setColour(gray);
    for (int i = 0; i < scene->quadCount; i++) {
        fillPolygon(4, &scene->x[i*4], &scene->y[i*4]);
    }
}

void drawThreeDee(Robot* robot, Maze* maze) {
    foreground();
    clear();
    setWindowSize(600, 400);
    setColour(lightgray);
    fillRect(0, 200, 600, 400);

    Scene scene;
    clearScene(&scene);

    IQuad testQuad = {
        {0, 0}, {50, 0}, {50, 50}, {0, 50}
    };
    appendToScene(&scene, testQuad);

    drawScene(&scene);
};

