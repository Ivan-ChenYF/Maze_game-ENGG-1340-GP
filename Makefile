FLAGS = -pedantic-errors -std=c++11

maze: main.o random_maze.o
	g++  $(FLAGS) -o maze main.o random_maze.o  -lncurses

main.o: main.cpp random_maze.h
	g++ $(FLAGS) -c main.cpp

random_maze.o: random_maze.cpp random_maze.h
	g++ $(FLAGS) -c random_maze.cpp

compile:
	make maze
clean:
	rm -f *.o maze
run:
	./maze
.PHONY: clean run compile
