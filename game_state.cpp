#include "game_state.h"
#include <iostream>
using namespace std;

void updateRank(vector<int>& rank, int time) {
    // Add time record to rank
    rank.push_back(time);
    
    // Sort ranking in ascending time
    sort(rank.begin(), rank.end());
}



void saveGame(const GameState& gameState) {
    // Get filename
    string filename = "save_file.txt";
    ofstream fout(filename);

    // Write player name
    fout << gameState.player_name << endl;

    // Write gamemode and difficulty
    fout << gameState.mode << " " << gameState.difficulty << endl;
    
    // Write player position
    fout << gameState.player_x << " " << gameState.player_y << endl;

    // Write exit location
    fout << gameState.end_x << " " << gameState.end_y << endl;

    // Write maze dimensions
    fout << gameState.width << " " << gameState.height << endl;

    // Write time left
    fout << gameState.elapsed << endl;

    // Write bombs left
    fout << gameState.bomb << endl;

    // Write maze
    for (int i = 0; i < gameState.width; ++i) {
        for (int j = 0; j < gameState.height; ++j) {
            fout << gameState.maze[i][j].top_w << " "
                 << gameState.maze[i][j].right_w << " "
                 << gameState.maze[i][j].left_w << " "
                 << gameState.maze[i][j].down_w << " "
                 << gameState.maze[i][j].revealed << endl;
        }
    }

    
    fout.close();
}

void loadGame(GameState& gameState) {
    string filename = "save_file.txt";
    ifstream fin(filename);

    // Read player name
    fin >> gameState.player_name;

    // Read gamemode and difficulty
    fin >> gameState.mode >> gameState.difficulty;

    // Read player position
    fin >> gameState.player_x >> gameState.player_y;

    // Read exit location
    fin >> gameState.end_x >> gameState.end_y;

    // Read maze dimensions
    fin >> gameState.width >> gameState.height;

    // Read time left
    fin >> gameState.elapsed;

    // Read bombs left
    fin >> gameState.bomb;

    // Allocate memory for maze
    gameState.maze = new cell*[gameState.width];
    for (int i = 0; i < gameState.width; ++i) {
        gameState.maze[i] = new cell[gameState.height];
    }

    // Read maze
    for (int i = 0; i < gameState.width; ++i) {
        for (int j = 0; j < gameState.height; ++j) {
            fin >> gameState.maze[i][j].top_w
                >> gameState.maze[i][j].right_w
                >> gameState.maze[i][j].left_w
                >> gameState.maze[i][j].down_w
                >> gameState.maze[i][j].revealed;
        }
    }


    fin.close();
}
