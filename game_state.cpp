#include "game_state.h"
#include "random_maze.h"
#include <iostream>
#include <fstream>
using namespace std;

void updateRank(double time,int mode, int difficulty,string username) {
    // Add time record to rank
    if (mode==0&&difficulty==0){
        ofstream fout;
        fout.open ("c_e.txt",ios::app);
        fout<<username<<" "<<time<<endl;
        fout.close();
    }
    else if (mode==0&&difficulty==1){
        ofstream fout;
        fout.open ("c_m.txt",ios::app);
        fout<<username<<" "<<time<<endl;
        fout.close();
    }
    else if (mode==0&&difficulty==2){
        ofstream fout;
        fout.open ("c_d.txt",ios::app);
        fout<<username<<" "<<time<<endl;
        fout.close();
    }
    else if (mode==1&&difficulty==0){
        ofstream fout;
        fout.open ("fog_e.txt",ios::app);
        fout<<username<<" "<<time<<endl;
        fout.close();
    }
    else if (mode==1&&difficulty==1){
        ofstream fout;
        fout.open ("fog_m.txt",ios::app);
        fout<<username<<" "<<time<<endl;
        fout.close();
    }
    else if (mode==1&&difficulty==2){
        ofstream fout;
        fout.open("fog_d.txt",ios::app);
        fout<<username<<" "<<time<<endl;
        fout.close();
    }
}
void print_ranking(string filename){
    ifstream fin;
    fin.open(filename.c_str());
    string name;
    int record;
    int i=0;
    while(fin>>name>>record){
        mvprintw(i,0,"Name: %s  record: %d ",name.c_str(),record);
    }
    clear();
    fin.close();
}
void top(string filename,string &fastest_name, int &fastest, int timelimit){
    ifstream fin;
    fin.open(filename.c_str());
    fastest=timelimit;
    string name;
    int record;
    while(fin>>name>>record){
        if (record<fastest){
            fastest=record;
            fastest_name=name;
        }
    }
    fin.close();
}

void updateInventory(vector<Item>& inventory, Item item) {
    // Add item to inventory
    inventory.push_back(item);
}

void initializeNewGame(GameState& gameState) {
    // Reset player's name
    gameState.player_name = "";

    // Initialize inventory
    gameState.inventory.clear();
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

    // Write inventory
    int inventory_size = gameState.inventory.size();
    fout << inventory_size << endl;
    
    for (int i = 0; i < inventory_size; i++) {
        fout << gameState.inventory[i].name << " "
             << gameState.inventory[i].quantity << endl;
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
    for (int i = 0; i < gameState.width; i++) {
        for (int j = 0; j < gameState.height; j++) {
            init(&gameState.maze[i][j],i,j);
        }
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
        >> gameState.inventory[i].quantity;
    }

    fin.close();
}
