#include "include.h"
#include "maze.h"
#include "robot.h"
#include "pov.h"

void clearScene(Scene* scene) {
    scene->quadCount = 0;
}

void appendQuadToScene(Scene* scene, Quad quad) {
    int i = scene->quadCount * 4;
    float* quadPtr = (float*)quad;      // sick pointer stuff B4
                                        //                    ^ this is a dog with shades

    for (int j = 0; j < 4; j++) {
        scene->x[i + j] = (int)quadPtr[2*j];
        scene->y[i + j] = (int)quadPtr[2*j + 1];
    }

    scene->quadCount += 1;
}

void appendWallToScene(Scene* scene, Wall wall) {
    Quad quad;
    
    for (int i = 0; i < 2; i++) {
        Vec v1;
        Vec v2;
        v1.x = 600.0 * wall[i].x;
        v2.x = v1.x;
        v1.y = 200.0 * (1 + wall[i].height);
        v2.y = 200.0 * (1 - wall[i].height);
        
        // surely there's a clever way TODO this
        if (i == 0) {
            quad[0] = v1;
            quad[1] = v2;
        } else {
            quad[2] = v2;
            quad[3] = v1;
        }
    }

    appendQuadToScene(scene, quad);
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

    Quad testQuad = {
        {0, 0}, {50, 0}, {50, 50}, {0, 50}
    };
    appendQuadToScene(&scene, testQuad);

    Wall testWall = {
        {-1.0, 0.5}, {0.5, 0.8}
    };
    appendWallToScene(&scene, testWall);

    drawScene(&scene);
};

