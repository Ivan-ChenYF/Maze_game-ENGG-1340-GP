#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "random_maze.h"
using namespace std;

struct Item {
    string name;
    int quantity;
};

struct GameState {
    cell** maze;
    string player_name;
    int width, height;
    int player_x, player_y;
    int end_x, end_y;
    int mode, difficulty;
    int bomb;
    double elapsed;
};

void initializeNewGame(GameState& gameState);
void updateRank(vector<double>& rank, double time);
void saveGame(const GameState& gameState);
void loadGame(const GameState& gameState);

#endif
