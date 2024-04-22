#include <iostream>
#include <vector>
#include <stack>
#include <termios.h>
#include <unistd.h>
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
            mvprintw(0, height + 2, "cant move");
            break;
        }
        break;
    case 97:
        if (playerX > 0 && !maze[playerX][playerY].right_w)
        {
            playerX--;
        }
        else
        {
            mvprintw(0, height + 2, "cant move");
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
            mvprintw(0, height + 2, "cant move");
            break;
        }
        break;
    case 100:
        if (playerX < width - 1 && !maze[playerX][playerY].right_w)
        {
            playerX++;
        }

    case KEY_UP:
        if (playerY > 0 && !maze[playerX][playerY].top_w)
        {
            playerY--;
        }
        else
        {
            mvprintw(0, height + 2, "cant move");
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
            mvprintw(0, height + 2, "cant move");
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
            mvprintw(0, height + 2, "cant move");
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
            mvprintw(0, height + 2, "cant move");
            // refresh();
        }
    case 98: // 'b' for bomb
        mvprintw(0, 2 * height + 1, "You got a bomb, press arrow key to choose wall to destroy");
        refresh();
        int ch = getch();
        // Assume the bomb destroys the wall in the direction pressed
        switch (ch)
        {
        case KEY_UP:
            if (playerY > 0 && maze[playerX][playerY].top_w)
            {
                maze[playerX][playerY].top_w = false;
            }
            break;
        case KEY_LEFT:
            if (playerX > 0 && maze[playerX][playerY].left_w)
            {
                maze[playerX][playerY].left_w = false;
            }
            break;
        case KEY_DOWN:
            if (playerY < height - 1 && maze[playerX][playerY].down_w)
            {
                maze[playerX][playerY].down_w = false;
            }
            break;
        case KEY_RIGHT:
            if (playerX < width - 1 && maze[playerX][playerY].right_w)
            {
                maze[playerX][playerY].right_w = false;
            }
            break;
        }

    default:
        break;
    }

    refresh(); // Refresh the screen to show the changes
}
