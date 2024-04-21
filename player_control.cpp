#include <iostream>
#include <vector>
#include <stack>
#include <termios.h>
#include <unistd.h>
#include "play_control.h"
#include "random_maze.h"
#include <ncurses.h>

using namespace std;

char getSingleKeyPress()
{
    termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

    char key = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
    return key;
}

bool isValidMove(cell **maze, int newY, int newX, int height, int width, char direction)
{
    if (newY > 0 && newY < height && newX > 0 && newX < width)
    {
        switch (direction)
        {
        case 'w': // moving up
            if (!maze[newY][newX].down_w)
            {
                return true;
            }
            break;
        case 'a': // moving left
            if (!maze[newY][newX].right_w)
            {
                return true;
            }
            break;
        case 's': // moving down
            if (!maze[newY][newX].top_w)
            {
                return true;
            }
            break;
        case 'd': // moving right
            if (!maze[newY][newX].left_w)
            {
                return true;
            }
            break;
        default:
            return true; // smvprintw(0, 0, "Invalid input. Please enter w, a, s, or d.");
            break;
        }
    }
    return false;
}

void player_movement(cell **maze, int width, int height, int start_x, int start_y)
{
    int playerY = start_y, playerX = start_x;       // Initial player position
    mvaddch(2 * playerY + 1, 3 * playerX + 1, '@'); // Draw player at initial position

    while (true)
    {
        char input = getSingleKeyPress();
        // int playerY = start_y, playerX = start_x;
        switch (input)
        {
        case 'w':
            if (playerY > 0)
            {
                mvaddch(2 * playerY + 1, 3 * playerX + 1, ' '); // Clear current position
                playerY--;
                mvaddch(2 * playerY + 1, 3 * playerX + 1, '@'); // Draw player at new position
                start_y = playerY;
            }
            else
            {
                cout << "cant move" << endl;
                printMaze(maze, width, height, start_x, start_y);
                break;
            }
            break;
        case 'a':
            if (playerX > 0)
            {
                mvaddch(2 * playerY + 1, 3 * playerX + 1, ' '); // Clear current position
                playerX--;
                mvaddch(2 * playerY + 1, 3 * playerX + 1, '@'); // Draw player at new position
                start_x = playerX;
            }
            else
            {
                cout << "cant move" << endl;
                printMaze(maze, width, height, start_x, start_y);
                break;
            }
            break;
        case 's':
            if (playerY < height - 1)
            {
                mvaddch(2 * playerY + 1, 3 * playerX + 1, ' '); // Clear current position
                playerY++;
                mvaddch(2 * playerY + 1, 3 * playerX + 1, '@'); // Draw player at new position
                start_y = playerY;
            }
            else
            {
                cout << "cant move" << endl;
                printMaze(maze, width, height, start_x, start_y);
                break;
            }
            break;
        case 'd':
            if (playerX < width - 1)
            {
                mvaddch(2 * playerY + 1, 3 * playerX + 1, ' '); // Clear current position
                playerX++;
                mvaddch(2 * playerY + 1, 3 * playerX + 1, '@'); // Draw player at new position
                start_x = playerX;
            }
            else
            {
                cout << "cant move" << endl;
                printMaze(maze, width, height, start_x, start_y);
                // refresh();
            }
            break;
        case 'q':
            cout << "Quitting the game." << endl;
            return; // Exit the function and stop the game
        default:
            // smvprintw(0, 0, "Invalid input. Please enter w, a, s, or d.");
            break;
        }

        refresh(); // Refresh the screen to show the changes
        // printMaze(maze, width, height, start_x, start_y);
    }
}
