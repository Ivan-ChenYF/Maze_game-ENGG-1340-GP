#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include "random_maze.h"
using namespace std;

void init(cell *now,int initX, int initY) {
    //初始化点的所有信息
    now->x = initX;
    now->y = initY;
    now->visited = false;
    now->top_w = true;
    now->left_w = true;
    now->right_w = true;
    now->down_w = true;
    now->revealed=false;
}
//使用了DFS算法实现的maze地图随机生成
void generateMaze(cell** &maze, int width,int height,int start_x,int start_y,int &end_x,int &end_y){
    srand(time(nullptr));
    stack <cell*> cellstack; //创建栈记录走过的点以便直接从堆顶读取并弹出数据
    int totalcells=width*height;
    int visitedcells=1;
    int maxDistance=0;
    int currentDistance;
    cell *current=&maze[start_x][start_y]; // 起始点
    current->visited=true;//走过的点更新状态
    //一直运行直到所有点都走过
    
    while (visitedcells<totalcells){
        vector <cell*> neighbour; //记录周围的点
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
            cell* next = neighbour[rand() % neighbour.size()]; //随机从neighbour vector中选一个方向
            //移除他们之间的墙壁
            if (next->y == current->y){
                //往右走
                if (next->x-current->x==1){
                    //移除current右边和next左边的墙
                    current->right_w=next->left_w=false;
                }
                //往左走
                else{
                    //移除current左边和next右边的墙
                    current->left_w=next->right_w=false;
                }
            }
            else{
                //往下走
                if (next->y - current->y == 1){
                    //移除current下边和next上边的墙
                    current->down_w=next->top_w=false;
                }
                //往上走
                else{
                    //移除current上边和next下边的墙
                    current->top_w=next->down_w=false;
                }
            }
            cellstack.push(current);//在栈的最后插入当前点
            current=next; //pointer移动到下一个位置
            current->visited=true;
            visitedcells++;
            currentDistance = cellstack.size(); // Distance is the stack size
            if (currentDistance > maxDistance) {
                maxDistance = currentDistance;
                end_x = current->x;
                end_y = current->y;
            }
            
            
        }else{//如果没有相邻的点能去
            if (!cellstack.empty()){//并且栈里有东西
                current=cellstack.top();//返回到上一次的cell
                cellstack.pop();//将最后的cell弹出
            }
        }
    }
    
}

