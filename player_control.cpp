#include <iostream>
#include <vector>
#include <stack>
#include "player_control.h"
#include "random_maze.h"
#include <ncurses.h>

using namespace std;

void player_movement(cell **&maze, int width, int height, int &playerX, int &playerY, int input)
{
    // Draw player at initial position

    // char input = getSingleKeyPress();
    //  int playerY = start_y, playerX = start_x;
    switch (input)
    {
    case 119:
        if (playerY > 0 && !maze[playerX][playerY].top_w)
        {
            playerY--;
        }
        else
        {
            mvprintw(2 * height + 1, 4 * width + 1,"Invalid Move");
            break;
        }
        break;
    case 97:
        if (playerX > 0 && !maze[playerX][playerY].left_w)
        {
            playerX--;
        }
        else
        {
            mvprintw(2 * height + 1, 4 * width + 1,"Invalid Move");
            break;
        }
        break;
    case 115:
        if (playerY < height - 1 && !maze[playerX][playerY].down_w)
        {
            playerY++;
        }
        else
        {
            mvprintw(2 * height + 1, 4 * width + 1,"Invalid Move");
            break;
        }
        break;
    case 100:
        if (playerX < width - 1 && !maze[playerX][playerY].right_w)
        {
            playerX++;
        }
        else
        {
            mvprintw(2 * height + 1, 4 * width + 1,"Invalid Move");
            break;
        }
            break;

    case KEY_UP:
        if (playerY > 0 && !maze[playerX][playerY].top_w)
        {
            playerY--;
        }
        else
        {
            mvprintw(2 * height + 1, 4 * width + 1,"Invalid Move");
            break;
        }
        break;
    case KEY_LEFT:
        if (playerX > 0 && !maze[playerX][playerY].left_w)
        {
            playerX--;
        }
        else
        {
            mvprintw(2 * height + 1, 4 * width + 1,"Invalid Move");
            break;
        }
        break;
    case KEY_DOWN:
        if (playerY < height - 1 && !maze[playerX][playerY].down_w)
        {
            playerY++;
        }
        else
        {
            mvprintw(2 * height + 1, 4 * width + 1,"Invalid Move");
            break;
        }
        break;
    case KEY_RIGHT:
        if (playerX < width - 1 && !maze[playerX][playerY].right_w)
        {
            playerX++;
        }
        else
        {
            mvprintw(2 * height + 1, 4 * width + 1,"Invalid Move");
            // refresh();
            break;
        }
            break;
    case 98: // 'b' for bomb

            time_t start_time = time(nullptr);
            time_t current_time;
            int ch;
            double elapsed;
  

            while (true) {
                current_time = time(nullptr);
                elapsed = difftime(current_time, start_time);
                mvprintw(2 * height + 1, 0, "You got a bomb, press arrow key to choose wall to destroy");
                refresh();

                if (elapsed > 2) {  // 如果超过2秒，退出循环
                    break;
                }

                ch = getch();  // 获取键盘输入
                switch (ch) {
                    case ERR:  // 如果没有输入，继续循环
                        continue;
                    case KEY_UP:
                        if (playerY > 0 && maze[playerX][playerY].top_w) {
                            maze[playerX][playerY].top_w = false;
                            maze[playerX][playerY - 1].down_w = false;
                        }
                        break;
                    case KEY_LEFT:
                        if (playerX > 0 && maze[playerX][playerY].left_w) {
                            maze[playerX][playerY].left_w = false;
                            maze[playerX - 1][playerY].right_w = false;
                        }
                        break;
                    case KEY_DOWN:
                        if (playerY < height - 1 && maze[playerX][playerY].down_w) {
                            maze[playerX][playerY].down_w = false;
                            maze[playerX][playerY + 1].top_w = false;
                        }
                        break;
                    case KEY_RIGHT:
                        if (playerX < width - 1 && maze[playerX][playerY].right_w) {
                            maze[playerX][playerY].right_w = false;
                            maze[playerX + 1][playerY].left_w = false;
                        }
                        break;
                }
                break;  // 一旦接收到有效输入即退出循环
            }

    }

    refresh(); // Refresh the screen to show the changes
}
