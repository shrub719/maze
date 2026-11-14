# Maze

Maze program for my Principles of Programming coursework.

## Description

TODO

## Requirements

In order to build and run the program, you will need to put the "drawing app files"
(`graphics.c` and `graphics.h`) in `src/include/`.

You also need `drawapp-5.0.jar` with Java 21 or later.

## Building

From the root directory, build the program with 

```bash
gcc ./src/*.c ./src/include/*.c -o maze
```

ensuring `graphics.c` and `graphics.h` are in the correct location.

## Usage

Run the program and pipe it into Draw App with

```bash
./maze [args] | java -jar ./drawapp-5.0.jar
```

### Arguments

- `--pov`  
    Run the program in a 3D view from the perspective of the robot.
- `--seed [int]`  
    Set a seed for maze generation.
- `--speed [float]`
    Set a speed multiplier for animation.

