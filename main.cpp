#include "random_maze.h"
#include <iostream>
#include <ncurses.h>
#include <string>
using namespace std;

int main(){
    setlocale(LC_ALL, "");
    initscr();
    PrintFromFile("ASCII - Enigma_Maze.txt");
    getch();
    clear();
    endwin();

    int width;
    int height;
    int start_x,start_y;
    cout<<"Width: ";
    cin>>width;
    cout<<"Height: ";
    cin>>height;
    cout<<"start_x: ";
    cin>>start_x;
    cout<<"start_y: ";
    cin>>start_y;
    cell** maze = new cell*[width]; //使用动态数组创建maze
    for (int i = 0; i < width; ++i) {
        maze[i] = new cell [height];
    }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            init(&maze[i][j],i,j);
        }
    }
    generateMaze(maze, width,height,start_x,start_y);
    printMaze(maze, width,height,start_x,start_y);
    // Clean up
    for (int i = 0; i < width; i++) {
        delete[] maze[i];
    }
    delete[] maze;
    return 0;
}


