#include "game_state.h"
using namespace std;

void initializeNewGame(GameState& gameState) {
    // Set player's initial position
    gameState.player_x = 0;
    gameState.player_y = 0;

    // Initialize inventory
    gameState.inventory.clear();
}

void saveGame(const GameState& gameState) {
    string filename;
    cout << "File name: " << endl;
    cin >> filename;
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

    // Write inventory
    int inventory_size = gameState.inventory.size();
    fout << inventory_size << endl;
    
    for (int i = 0; i < inventory_size; i++) {
        fout << gameState.inventory[i].name << " "
             << gameState.inventory[i].quantity << endl;
    }
    
    fout.close();
}

void loadGame(GameState& gameState, const string& filename) {
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

    // Read inventory
    int inventory_size;
    fin >> inventory_size;
    
    for (int i = 0; i < inventory_size; i++) {
        fin >> gameState.inventory[i].name
            >> gameState.inventory[i].quantity
    }
    
    fin.close();
}
