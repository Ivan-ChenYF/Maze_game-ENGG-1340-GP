#include <iostream>
#include <vector>
#include <stack>
#include "player_control.h"
#include "random_maze.h"
#include <ncurses.h>

using namespace std;

void player_movement(cell **&maze, int width, int height, int &playerX, int &playerY, int input, int &bomb)
{

    switch (input)
    {
    case 119:
        if (playerY > 0 && !maze[playerX][playerY].top_w) //checking for the wall on the top and see if the player is moving within the maze
        {
            playerY--; // move upward
        }
        else
        {
            mvprintw(4, 4 * width + 3, "Invalid Move"); 
            break;
        }
        break;
    case 97:
        if (playerX > 0 && !maze[playerX][playerY].left_w) // checking for the wall on the left and see if the player is moving within the maze
        {
            playerX--; // move left
        }
        else
        {
            mvprintw(4, 4 * width + 3, "Invalid Move");
            break;
        }
        break;
    case 115:
        if (playerY < height - 1 && !maze[playerX][playerY].down_w) //checking for the wall on the down and see if the player is moving within the maze
        {
            playerY++; // move down 
        }
        else
        {
            mvprintw(4, 4 * width + 3, "Invalid Move");
            break;
        }
        break;
    case 100:
        if (playerX < width - 1 && !maze[playerX][playerY].right_w) //checking for the wall on the right and see if the player is moving within the maze
        {
            playerX++; // move right
        }
        else
        {
            mvprintw(4, 4 * width + 3, "Invalid Move");
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
            mvprintw(4, 4 * width + 3, "Invalid Move");
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
            mvprintw(4, 4 * width + 3, "Invalid Move");
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
            mvprintw(4, 4 * width + 3, "Invalid Move");
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
            mvprintw(4, 4 * width + 3, "Invalid Move");
            // refresh();
            break;
        }
        break;
    case 98: // 'b' button for bomb 

        time_t start_time = time(nullptr);
        time_t current_time;
        int ch;
        double elapsed;

        while (bomb != 0) //check if the player still have bomb
        {
            current_time = time(nullptr);
            elapsed = difftime(current_time, start_time);
            mvprintw(2 * height + 1, 0, "You got a bomb, press arrow key to choose wall to destroy");
            refresh();

            if (elapsed > 2)
            { //exit if exceed 2 seconds
                break;
            }

            ch = getch(); // 获取键盘输入
            switch (ch)
            {
            case ERR: // 如果没有输入，继续循环
                continue;
            case KEY_UP:
                if (playerY > 0 && maze[playerX][playerY].top_w)
                {
                    bomb--;
                    maze[playerX][playerY].top_w = false;
                    maze[playerX][playerY - 1].down_w = false;
                }
                break;
            case KEY_LEFT:
                if (playerX > 0 && maze[playerX][playerY].left_w)
                {
                    bomb--;
                    maze[playerX][playerY].left_w = false;
                    maze[playerX - 1][playerY].right_w = false;
                }
                break;
            case KEY_DOWN:
                if (playerY < height - 1 && maze[playerX][playerY].down_w)
                {
                    bomb--;
                    maze[playerX][playerY].down_w = false;
                    maze[playerX][playerY + 1].top_w = false;
                }
                break;
            case KEY_RIGHT:
                if (playerX < width - 1 && maze[playerX][playerY].right_w)
                {
                    bomb--;
                    maze[playerX][playerY].right_w = false;
                    maze[playerX + 1][playerY].left_w = false;
                }
                break;
            }
            break; // 一旦接收到有效输入即退出循环
        }
        mvprintw(2 * height + 1, 4 * width + 1, "No Bomb");
    }
    
 // Refresh the screen to show the changes
    refresh();
}


