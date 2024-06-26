#include <iostream>
#include <ctime>
#include <ncurses.h>
#include "random_maze.h"
using namespace std;

void printMaze(cell** maze, int width, int height, int player_x,int player_y,int end_x,int end_y,int bomb,double elapsed,int fastest,
               string fastest_name) {

    mvprintw(2*height+4, 0, "Top Record: \nPlayer: %s  time: %ds",fastest_name.c_str(),fastest );
   
    mvprintw(2 * end_y + 1, 4 * end_x + 2, "#");
    mvprintw(2*height+2, 0, "Time remaining: %.0f seconds", elapsed);
    mvprintw(2 * player_y + 1, 4 * player_x + 2, "@");
    mvprintw(0, 4 * width + 3, "Bomb: %d", bomb);
    // The corner and edges need to be handled for the entire grid
    mvprintw(2*height-2, 4 * width + 3, "Player position: @");
    mvprintw(2*height-1, 4 * width + 3, "Destination: #");
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (maze[i][j].revealed==true){
                int x = 4 * i;
                int y = 2 * j;
                // Display the walls of the cell
                mvaddch(y, x, '+'); // Corner of the cell
                if (maze[i][j].top_w || j == 0) {
                    mvaddch(y, x + 1, '-'); // Top wall
                    mvaddch(y, x + 2, '-');
                    mvaddch(y, x + 3, '-');
                }
                if (maze[i][j].left_w || i == 0) {
                    mvaddch(y + 1, x, '|'); // Left wall
                }
                if (maze[i][j].right_w || i == width - 1) {
                    mvaddch(y + 1, x + 4, '|'); // Right wall
                }
                if (maze[i][j].down_w || j == height - 1) {
                    mvaddch(y + 2, x, '+'); // Bottom corner
                    mvaddch(y + 2, x + 1, '-'); // Bottom wall
                    mvaddch(y + 2, x + 2, '-');
                    mvaddch(y + 2, x + 3, '-');
                }
            }
        }
    }

    // Correctly handling the last row and the last column
    // Add corners and vertical lines on the right edge of the maze
    for (int j = 0; j <= height; j++) {
        mvaddch(2 * j, 4 * width, '+'); // Add corners
        if (j < height) {
            mvaddch(2 * j + 1, 4 * width, '|'); // Add vertical lines
        }
    }
    
    for (int j = 0; j <= height; j++) {
        mvaddch(2 * j, 0, '+'); // Add corners
        if (j < height) {
            mvaddch(2 * j + 1, 0, '|'); // Add vertical lines
        }
    }
    // Add corners and horizontal lines on the bottom edge of the maze
    for (int i = 0; i <= width; i++) {
        mvaddch(2 * height, 4 * i, '+'); // Add corners
        if (i < width) {
            mvaddch(2 * height, 4 * i + 1, '-'); // Add horizontal lines
            mvaddch(2 * height, 4 * i + 2, '-');
            mvaddch(2 * height, 4 * i + 3, '-');
        }
    }
    
    for (int i = 0; i <= width; i++) {
        mvaddch(0, 4 * i, '+'); // Add corners
        if (i < width) {
            mvaddch(0, 4 * i + 1, '-'); // Add horizontal lines
            mvaddch(0, 4 * i + 2, '-');
            mvaddch(0, 4 * i + 3, '-');
        }
    }
    


}

