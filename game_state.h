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
using Inventory = vector<Item>;

struct GameState {
    cell** maze;
    string player_name;
    int width, height;
    int player_x, player_y;
    int end_x, end_y;
    int mode, difficulty;
    int bomb;
    Inventory inventory;
    double elapsed;
};

void initializeNewGame(GameState& gameState);
void updateRank(double time,int mode, int difficulty,string username);
void saveGame(const GameState& gameState);
void loadGame(GameState& gameState);
void top(string filename,string &fastest_name, int &fastest,int limit);
#endif

