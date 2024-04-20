#ifndef PLAY_CONTROL_H
#define PLAY_CONTROL_H

#include "random_maze.h" // Include the header file where the cell struct is defined

void clearScreen();
char getSingleKeyPress();
bool isValidMove(cell **maze, int newY, int newX, int height, int width);
void player_movement(cell **maze, int width, int height, int player_x, int player_y);

#endif

