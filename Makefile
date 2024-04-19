FLAGS = -pedantic-errors -std=c++11

maze: main.o maze.o
    g++ $(FLAGS) -o maze main.o maze.o 

main.o: main.cpp random_maze.h
    g++ $(FLAGS) -c main.cpp 

maze.o: random_maze.cpp random_maze.h
    g++ $(FLAGS) -c maze.cpp 

compile:
    maze
clean:
    rm -f *.o maze
run:
    ./maze
.PHONY: clean run
