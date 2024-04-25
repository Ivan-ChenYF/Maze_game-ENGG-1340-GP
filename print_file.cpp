#include <ncurses.h>
#include <fstream>
#include <string>
#include <vector>
#include "user_interface.h"
using namespace std;


void PrintFromFile(string filename){
    
    // OPEN FILE
    ifstream fin;
    fin.open(filename);

    if (fin.fail()) 
        printw("fail to opoen file");

    string line;
    int row = 0;

    // PRINT FILE
    while (getline(fin, line)) {
        move(row, 0);
        printw("%s", line.c_str());
        ++row;
    }

    // CLOSE FILE
    fin.close();
    
    refresh();
}
