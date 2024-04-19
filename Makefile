FLAGS = -pedantic-errors -std=c++11

maze: main.o random_maze.o print_file.o
	g++  $(FLAGS) -o maze main.o random_maze.o print_file.o print_map.o -lncurses

main.o: main.cpp random_maze.h
	g++ $(FLAGS) -c main.cpp

random_maze.o: random_maze.cpp random_maze.h
	g++ $(FLAGS) -c random_maze.cpp

print_map.o: print_map.cpp random_maze.h
	g++ $(FLAGS) -c print_map.cpp
print_file.o: print_file.cpp random_maze.h
	g++ $(FLAGS) -c print_file.cpp

compile:
	make maze
clean:
	rm -f *.o maze
run:
	./maze
.PHONY: clean run compile
