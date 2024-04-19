#include "random_maze.h"
#include <iostream>

int main(){
    int width;
    int height;
    int start_x,start_y;
    cin>>width>>height>>start_x>>start_y;
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

