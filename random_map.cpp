#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
using namespace std;

//每一个点的信息
struct cell{
    int x,y;
    bool visited, top_w, left_w, right_w, down_w;
};

void init(cell* now,int initX, int initY);
void generateMaze(cell** &maze, int width,int height,int start_x,int start_y);
void printMaze(cell** maze, int width, int height, int play_posit_x,int play_posit_y);
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
}

void init(cell *now,int initX, int initY) {
    //初始化点的所有信息
    now->x = initX;
    now->y = initY;
    now->visited = false;
    now->top_w = true;
    now->left_w = true;
    now->right_w = true;
    now->down_w = true;
}
//使用了DFS算法实现的maze地图随机生成
void generateMaze(cell** &maze, int width,int height,int start_x,int start_y){
    srand(time(nullptr));
    stack <cell*> cellstack; //创建栈记录走过的点以便直接从堆顶读取并弹出数据
    int totalcells=width*height;
    int visitedcells=1;
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
        }else{//如果没有相邻的点能去
            if (!cellstack.empty()){//并且栈里有东西
                current=cellstack.top();//返回到上一次的cell
                cellstack.pop();//将最后的cell弹出
            }
        }
    }
    
}

//这段来自ChatGPT需要Elaine修改
//ONLY FOR TEST FOR CODING
void printMaze(cell** maze, int width, int height, int player_x,int player_y) {
    initscr();          // Start ncurses mode
    cbreak();           // Disable line buffering
    noecho();           // Don't echo user input
    keypad(stdscr, TRUE); // Enable function keys
    curs_set(0);        // Hide the cursor
    start_color();          // 启动颜色功能

    init_pair(1, COLOR_RED, COLOR_WHITE); // 定义颜色对，红色前景，白色背景

    bkgd(COLOR_PAIR(1));    // 设置默认背景颜色为白色
    attron(COLOR_PAIR(1));  // 使用红色前景和白色背景

 
    mvaddch(2 * player_y + 1, 3 * player_x + 1, '@');

    // The corner and edges need to be handled for the entire grid
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            int x = 3 * i;
            int y = 2 * j;

            // Display the walls of the cell
            mvaddch(y, x, '+'); // Corner of the cell
            if (maze[i][j].top_w || j == 0) {
                mvaddch(y, x + 1, '-'); // Top wall
                mvaddch(y, x + 2, '-');
            }
            if (maze[i][j].left_w || i == 0) {
                mvaddch(y + 1, x, '|'); // Left wall
            }
            if (maze[i][j].right_w || i == width - 1) {
                mvaddch(y + 1, x + 3, '|'); // Right wall
            }
            if (maze[i][j].down_w || j == height - 1) {
                mvaddch(y + 2, x, '+'); // Bottom corner
                mvaddch(y + 2, x + 1, '-'); // Bottom wall
                mvaddch(y + 2, x + 2, '-');
            }
        }
    }

    // Correctly handling the last row and the last column
    // Add corners and vertical lines on the right edge of the maze
    for (int j = 0; j <= height; j++) {
        mvaddch(2 * j, 3 * width, '+'); // Add corners
        if (j < height) {
            mvaddch(2 * j + 1, 3 * width, '|'); // Add vertical lines
        }
    }

    // Add corners and horizontal lines on the bottom edge of the maze
    for (int i = 0; i <= width; i++) {
        mvaddch(2 * height, 3 * i, '+'); // Add corners
        if (i < width) {
            mvaddch(2 * height, 3 * i + 1, '-'); // Add horizontal lines
            mvaddch(2 * height, 3 * i + 2, '-');
        }
    }
    attroff(COLOR_PAIR(1)); // 关闭颜色属性
    refresh();         // Refresh the screen to show the maze
    getch();           // Wait for user input
    endwin();          // End ncurses mode
}
