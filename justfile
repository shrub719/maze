build:
    gcc -Wall ./src/*.c ./src/include/*.c -o maze -lm
    
[parallel]
run-both: run run-3d

test-2d: build run

[default]
test-3d: build run-3d

test-both: build run-both

