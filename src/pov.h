#pragma once

typedef struct {
    // sometimes in grid units; sometimes in pixel coords
    float x;
    float y;
} Vec;
typedef Vec Quad[4];

typedef struct {
    // normalised
    float x;
    float height;
} Edge;
typedef Edge Wall[2];

typedef struct {
    int quadCount;
    int x[STACK];
    int y[STACK];
} Scene;

void drawThreeDee(Robot* robot, Maze* maze);

// to calculate walls:
// - for every wall cell:
//   - for every corner of the wall:
//     - calculate difference vector with the robot
//     - rotate difference vector so that forward facing is (0, 1) direction
//     - turn difference vector into an Edge with Maths
//   - for every pairwise wall combination:
//     - test if Wall is in pov (clipping?)
//     - add Wall to Scene
