#ifndef PLAY_CONTROL_H
#define PLAY_CONTROL_H

#include "random_maze.h" // Include the header file where the cell struct is defined


void player_movement(cell **&maze, int width, int height, int &playerX, int &playerY, int input, int &bomb);

#endif

