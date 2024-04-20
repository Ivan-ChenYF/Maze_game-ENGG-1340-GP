#ifndef RANDOM_MAZE_H
#define RANDOM_MAZE_H

#include <vector>
#include <string>

struct cell {
    int x, y;
    bool visited, revealed;
    bool top_w, left_w, right_w, down_w;
};

void init(cell* now, int initX, int initY);
void generateMaze(cell** &maze, int width, int height, int start_x, int start_y,int &end_x,int &end_y);
void printMaze(cell** maze, int width, int height, int player_x, int player_y,int end_x,int end_y);
void PrintFromFile(std::string filename);

#endif
