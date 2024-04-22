#include <ncurses.h>
#include "random_maze.h"
#include <cstring>
#include <string>
using namespace std;

int choiceUI(string choice) {
    // 初始化ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // 获取屏幕尺寸
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);

    // 初始化选项
    const int numOptions = 3;
    if (choice == "mode"){
        const char* options[numOptions] = {
            "Classic Mode",
            "Frog Mode",
            "End Game"
        };
    }
    else if (choice == "difficulty"){   
        const char* options[numOptions] = {
            "Easy",
            "Medium",
            "Difficult"
        };
    }
    int currentOption = 0;

    while (true) {
        // 清空屏幕
        clear();

        PrintFromFile("ASCII - Main_Menu.txt");
        // 打印选项
        for (int i = 0; i < numOptions; i++) {
            if (i == currentOption) {
                // 设置选中项的颜色为白底黑字
                attron(A_REVERSE);
                attron(COLOR_PAIR(1));
            }
            mvprintw(maxRows/2 - numOptions/2 + i, maxCols/2 - strlen(options[i])/2, options[i]);
            attroff(A_REVERSE);
            attroff(COLOR_PAIR(1));
        }

        // 刷新屏幕
        refresh();

        // 获取用户输入
        int input = getch();
        switch (input) {
            case KEY_UP:
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case KEY_DOWN:
                currentOption = (currentOption + 1) % numOptions;
                break;
            case '\n':
                // 用户按下Enter键，选择当前选项
                clear();
                mvprintw(maxRows/2, maxCols/2 - strlen(options[currentOption])/2, "Selected: %s", options[currentOption]);
                refresh();
                getch();
                clear();
                endwin();
                return currentOption;
        }
    }

    // 清理ncurses
    endwin();
    return 2; //END GAME
}
