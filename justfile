build:
    gcc -Wall ./src/*.c ./src/include/*.c -o maze -lm
    
run:
    ./maze | java -jar ./src/include/drawapp-5.0.jar

run-3d:
    ./maze --3d | java -jar ./src/include/drawapp-5.0.jar

[parallel]
run-both: run run-3d

[default]
test: build run

test-3d: build run-3d

test-both: build run-both

