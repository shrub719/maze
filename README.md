# Maze

Maze program for my Principles of Programming coursework.

## Description

TODO

## Requirements

In order to build and run the program, you will need to put the "drawing app files" in
`src/include/`. This includes:
- `graphics.c`
- `graphics.h`
- `drawapp-5.0`

You will also need Java 21 or later.

## Building

From the root directory, build the program with 

```bash
gcc ./src/*.c ./src/include/*.c -o maze
```

Run the program with

```bash
./maze | java -jar ./src/include/drawapp-5.0.jar
```

