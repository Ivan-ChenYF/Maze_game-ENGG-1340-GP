#include "game_state.h"
using namespace std;

void updateRank(vector<int>& rank, int time) {
    // Add time record to rank
    rank.push_back(time);
    
    // Sort ranking in ascending time
    sort(rank.begin(), rank.end());
}

void initializeNewGame(GameState& gameState) {
    // Reset player's name
    gameState.player_name = "";

    // Initialize inventory
    gameState.inventory.clear();
}

void saveGame(const GameState& gameState) {
    // Get filename
    string filename = "save_file";
    cout << "File name (end with .txt): " << endl;
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
                 << gameState.maze[i][j].down_w << " "
                 << gameState.maze[i][j].revealed << endl;
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
    string filename;
    cout << "File name (end with .txt): " << endl;
    cin >> filename;
    ifstream fin(filename);

    if (fin) {
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
                    >> gameState.maze[i][j].down_w
                    >> gameState.maze[i][j].revealed;
            }
        }
    
        // Read inventory
        int inventory_size;
        fin >> inventory_size;
        
        for (int i = 0; i < inventory_size; i++) {
            fin >> gameState.inventory[i].name
                >> gameState.inventory[i].quantity
        }
    }
    else {
        cout << "File not found" << endl;
    }
    fin.close();
}
