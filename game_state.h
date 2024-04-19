#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <fstream>
#include "random_maze.h"
using namespace std;

struct gameState {
    cell** maze;
    int width, height;
    int player_x, player_y;
};

void saveGame(const gameState& gameState, const string& filename);
void loadGame(const gameState& gameState, const string& filename);

#endif