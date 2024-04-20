#include "game_state.h"
using namespace std;

void saveGame(const gameState& gameState, const string& filename) {
    ofstream fout(filename);

    // Write player name
    fout << gameState.player_name << endl;
    
    // Write player position
    fout << gameState.player_x << " " << gameState.player_y << endl;

    // Write maze dimensions
    fout << gameState.width << " " << gameState.height << endl;

    // Write maze
    for (int i = 0; i < gameState.width; ++i) {
        for (int j = 0; j < gameState.height; ++j) {
            fout << gameState.maze[i][j].top_w << " "
                 << gameState.maze[i][j].right_w << " "
                 << gameState.maze[i][j].left_w << " "
                 << gameState.maze[i][j].down_w << endl;
        }
    }

    fout.close();
}

void loadGame(gameState& gameState, const string& filename) {
    ifstream fin(filename);

    // Read player name
    fin >> gameState.player_name;

    // Read player position
    fin >> gameState.player_x >> gameState.player_y;

    // Read maze dimensions
    fin >> gameState.width >> gameState.height;

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
                >> gameState.maze[i][j].down_w;
        }
    }

    fin.close();
}
