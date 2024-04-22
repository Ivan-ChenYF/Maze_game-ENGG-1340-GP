#include "random_maze.h"
#include "game_state.h"
#include "player_control.h"
#include <iostream>
#include <ncurses.h>
#include <string>
using namespace std;

int main(){
    GameState game; // Initialize gameState
    
    setlocale(LC_ALL, "");
    
    // LOADING PAGE
    initscr();
    PrintFromFile("ASCII - Enigma_Maze.txt");
    getch();
    clear();
    endwin();

    // INPUT USERNAME
    initscr();
    PrintFromFile("ASCII - Create_User.txt");
    char ch;
    while ((ch = getch()) != '\n') {
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (!game.player_name.empty()) {
                game.player_name.pop_back();
                move(getcury(stdscr), getcurx(stdscr) - 1);
                mvdelch(getcury(stdscr), getcurx(stdscr));
                refresh();
            }
        } else {
            game.player_name.push_back(ch);
            refresh();
        }
    }
    clear();
    endwin();

    cout << "Your user name is " << game.player_name << endl;

    int width;
    int height;
    int start_x,start_y;
    int end_x,end_y;
    cout<<"Width: ";
    cin>>width;
    cout<<"Height: ";
    cin>>height;
    cout<<"start_x: ";
    cin>>start_x;
    cout<<"start_y: ";
    cin>>start_y;
    
    time_t start_time = time(nullptr);
    time_t current_time;
    cell** maze = new cell*[width]; //使用动态数组创建maze
    for (int i = 0; i < width; ++i) {
        maze[i] = new cell [height];
    }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            init(&maze[i][j],i,j);
        }
    }
    initscr();          // Start ncurses mode
    cbreak();           // Disable line buffering
    noecho();           // Don't echo user input
    keypad(stdscr, TRUE); // Enable function keys
    curs_set(0);        // Hide the cursor
    timeout(100);     //100毫秒没有接收到新的输入返回ERR
    
    
    generateMaze(maze, width,height,start_x,start_y,end_x,end_y);
    printMaze(maze, width,height,start_x,start_y,end_x,end_y);
    player_movement(maze, width, height, start_x, start_y);
    


    int player_x = start_x;
    int player_y = start_y;
    int ch;

    while ((ch = getch()) != 'q') {
        
        int centerIndex = 2; // 5x5区域的中心索引
        int displaySize = 5; // 显示区域尺寸
        
        int minX = max(0, player_x - centerIndex);
        int maxX = min(width - 1, player_x + centerIndex);
        int minY = max(0, player_y - centerIndex);
        int maxY = min(height - 1, player_y + centerIndex);

        // 确保显示区域为5x5，如果接近边界，则调整
        if (maxX - minX < displaySize - 1) {
            if (minX == 0) maxX = displaySize - 1; // 靠近左边界
            if (maxX == width - 1) minX = width - displaySize; // 靠近右边界
        }
        if (maxY - minY < displaySize - 1) {
            if (minY == 0) maxY = displaySize - 1; // 靠近上边界
            if (maxY == height - 1) minY = height - displaySize; // 靠近下边界
        }

        // 设置显示区域
        for (int i = minX; i <= maxX; i++) {
            for (int j = minY; j <= maxY; j++) {
                maze[i][j].revealed = true;
            }
        }
        

        current_time = time(nullptr);
        double elapsed = difftime(current_time, start_time);
        if (elapsed>50||(player_x==end_x&&player_y==end_y)){
            break;
        }
        clear();
        printMaze(maze, width, height, player_x, player_y,end_x,end_y);
        mvprintw(2*height+1, 0, "Time elapsed: %.0f seconds", elapsed);// Display elapsed time on screen
        refresh();


        for (int i = minX; i <= maxX; i++) {
            for (int j = minY; j <= maxY; j++) {
                maze[i][j].revealed = false;
            }
        }
        
        if (ch == ERR) continue;
        //for test only
        switch(ch) {
            case KEY_LEFT:
                if (player_x > 0) player_x--;
                break;
            case KEY_RIGHT:
                if (player_x < width - 1) player_x++;
                break;
            case KEY_UP:
                if (player_y > 0) player_y--;
                break;
            case KEY_DOWN:
                if (player_y < height - 1) player_y++;
                break;
        }
    }
    endwin();
    
    // Clean up
    for (int i = 0; i < width; i++) {
        delete[] maze[i];
    }
    delete[] maze;
    return 0;
}


