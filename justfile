build:
    gcc -Wall ./src/*.c ./src/include/*.c -o maze
    
[default]
run: build
    ./maze | java -jar ./src/include/drawapp-5.0.jar

