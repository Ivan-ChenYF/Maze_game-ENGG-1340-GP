FLAGS = -pedantic-errors -std=c++11

maze: main.o random_maze.o print_file.o print_maze.o main_menu.o player_control.o game_state.o
	g++  $(FLAGS) -o maze main.o random_maze.o  print_maze.o print_file.o main_menu.o player_control.o game_state.o -lncurses

main.o: main.cpp random_maze.h user_interface.h
	g++ $(FLAGS) -c main.cpp

random_maze.o: random_maze.cpp random_maze.h
	g++ $(FLAGS) -c random_maze.cpp

print_maze.o: print_maze.cpp random_maze.h
	g++ $(FLAGS) -c print_maze.cpp
	
print_file.o: print_file.cpp user_interface.h
	g++ $(FLAGS) -c print_file.cpp

game_state.o: game_state.cpp game_state.h
	g++ $(FLAGS) -c game_state.cpp

main_menu.o: main_menu.cpp user_interface.h
	g++ $(FLAGS) -c main_menu.cpp

player_control.o: player_control.cpp player_control.h
	g++ $(FLAGS) -c player_control.cpp

compile:
	make maze
clean:
	rm -f *.o maze
run:
	./maze
.PHONY: clean run compile
