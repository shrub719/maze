# Maze

Maze program for my Principles of Programming coursework.

## Description

Maze is a program which generates a maze and lets a robot with limited
capabilities and perception solve it using different algorithms.

The program can be configured via the command line to run different
generation and solving algorithms, as well as viewing the maze
solution from the perspective of the robot.

## Requirements

In order to build and run the program, you will need to put the "drawing app files"
(`graphics.c` and `graphics.h`) in `src/include/`.

You also need `drawapp-5.0.jar` with Java 21 or later.

## Building

From the root directory, build the program with 

```bash
gcc ./src/*.c ./src/include/*.c -o maze -lm
```

ensuring `graphics.c` and `graphics.h` are in the correct location.

## Usage

Run the program and pipe it into Draw App with

```sh
./maze [args] | java -jar ./drawapp-5.0.jar
```

### Arguments

- `--gen [algorithm]`
    Choose a maze generation algorithm. One of:
    - `prim`: Randomised Prim's algorithm
    - `dfs`: Randomised Depth First Search
- `--solve [algorithm]`
    Choose a maze solving algorithm. One of:
    - `hug`: simple left wall hug (DFS)
    - `hugright`: ditto, but right wall
    - `random`: random mouse algorithm
- `--pov`  
    Run the program in a 3D view from the perspective of the robot.
- `--seed [int]`  
    Set a seed for maze generation.
- `--speed [float]`  
    Set a speed multiplier for animation.
- `--width [int]`  
    Set the width of the maze. Must be odd.
- `--height [int]`  
    Set the height of the maze. Must be odd.
-  `--help`  
    Display this help information.

> One of my favourite things to do is run
> ```sh
> ./maze --solve random --speed 10.0 | java -jar ./drawapp-5.0.jar 
> ```

