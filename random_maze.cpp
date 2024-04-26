#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "random_maze.h"
using namespace std;

void init(cell *now,int initX, int initY) {
    // initialization 
    now->x = initX;
    now->y = initY;
    now->visited = false;
    now->top_w = true;
    now->left_w = true;
    now->right_w = true;
    now->down_w = true;
    now->revealed=false;
}
// Generating the maze with DFS algorithms
void generateMaze(cell** &maze, int width,int height,int start_x,int start_y,int &end_x,int &end_y){
    srand(time(nullptr));
    stack <cell*> cellstack; //storing the visited point
    int totalcells=width*height;
    int visitedcells=1;
    int maxDistance=0;
    int currentDistance;
    cell *current=&maze[start_x][start_y]; // starting point
    current->visited=true;

    
    while (visitedcells<totalcells){
        vector <cell*> neighbour; //record of cell surrounding 
        //left
        if (current->x > 0 && maze[current->x - 1][current->y].visited==false){
            neighbour.push_back(&maze[current->x - 1][current->y]);
        }
        //right
        if (current->x < width-1 && maze[current->x + 1][current->y].visited==false){
            neighbour.push_back(&maze[current->x + 1][current->y]);
        }
        //up
        if (current->y > 0 && maze[current->x ][current->y-1].visited==false){
            neighbour.push_back(&maze[current->x][current->y-1]);
        }
        //down
        if (current->y < height-1 && maze[current->x][current->y+1].visited==false){
            neighbour.push_back(&maze[current->x][current->y+1]);
        }
        
        if (!neighbour.empty()) {
            cell* next = neighbour[rand() % neighbour.size()]; // pickup a random direction
            if (next->y == current->y){
                if (next->x-current->x==1){
                    //remove the wall of current's right and next's left
                    current->right_w=next->left_w=false;
                }
                else{
                    current->left_w=next->right_w=false;
                }
            }
            else{
                if (next->y - current->y == 1){
                    current->down_w=next->top_w=false;
                }
                else{
                    current->top_w=next->down_w=false;
                }
            }
            cellstack.push(current);
            current=next; //move the pointer to next
            current->visited=true;
            visitedcells++;
            currentDistance = cellstack.size(); // Distance is the stack size
            if (currentDistance > maxDistance) {
                maxDistance = currentDistance;
                end_x = current->x;
                end_y = current->y;
            }
            
            
        }else{// if no more connected cell to go
            if (!cellstack.empty()){
                current=cellstack.top();
                cellstack.pop();
            }
        }
    }
    
}

