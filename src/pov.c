#include "include.h"
#include "maze.h"
#include "robot.h"
#include "pov.h"
#include <math.h>

void clearScene(Scene* scene) {
    scene->quadCount = 0;
}

void appendQuadToScene(Scene* scene, Quad quad) {
    if (scene->quadCount >= STACK) return;

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

Vec rotateVectorDegrees(Vec v, int d) {
    double a = (double)d / 180.0 * M_PI;
    double c = cos(a);
    double s = sin(a);
    Vec result;

    result.x = (float)(c*v.x - s*v.y);
    result.y = (float)(s*v.x + c*v.y);
    
    return result;
}

Vec calculateViewVector(Vec pos, Robot* robot) {
    Vec differenceVector = {
        pos.x - (float)robot->pos.x,
        pos.y - (float)robot->pos.y
    };

    int angle = -90 * robot->dir;

    return rotateVectorDegrees(differenceVector, angle);
}

Edge calculateEdge(Vec v) {
    Edge edge;

    edge.height = POV_EDGE_HEIGHT / v.y;

    edge.x = ((v.x / (v.y / POV_FOV)) + POV_FOV) / (POV_FOV * 2);

    return edge;
}

void populateScene(Scene* scene, Robot* robot, Maze* maze) {
    int width = maze->width;
    int height = maze->height;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) { 
            Cell cell = getCell(maze, (CellRef){i, j});
            if (cell == WALL) {
                Edge edges[4];
                for (int k = 0; k < 4; k++) {
                    Vec pos = {
                        (float)i - 0.5 + (float)((int)(k / 2)) * 1.0,
                        (float)j - 0.5 + (float)(k % 2) * 1.0
                    };
                    Vec viewVector = calculateViewVector(pos, robot);
                    edges[k] = calculateEdge(viewVector);
                }

                int walls[] = {
                    0, 1,
                    1, 3,
                    3, 2,
                    2, 0
                };
                for (int k = 0; k < 4; k++) {
                    Wall wall = {edges[walls[2*k]], edges[walls[2*k + 1]]};
                    appendWallToScene(scene, wall);
                }
            }
        }
    }
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
    populateScene(&scene, robot, maze);
    drawScene(&scene);

    /*
    Quad testQuad = {
        {0, 0}, {50, 0}, {50, 50}, {0, 50}
    };
    appendQuadToScene(&scene, testQuad);

    Wall testWall = {
        {-1.0, 0.5}, {0.5, 0.8}
    };
    appendWallToScene(&scene, testWall);

    drawScene(&scene);
    */
};

