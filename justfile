build:
    gcc -Wall ./src/*.c ./src/include/*.c -o maze -lm

run:
    ./maze | java -jar ./src/include/drawapp-5.0.jar

run-pov:
    ./maze --pov | java -jar ./src/include/drawapp-5.0.jar
    
[parallel]
run-both: run run-pov

test: build run

[default]
test-pov: build run-pov

test-both: build run-both

