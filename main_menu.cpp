#include <ncurses.h>
#include <cstring>
#include <string>
#include "user_interface.h"
using namespace std;

int choiceUI(OptionType optionType) {
    const Option modeOptions[] = {
        {"Classic Mode", 0},
        {"Frog Mode", 1},
        {"End Game", 2}
    };

    const Option difficultyOptions[] = {
        {"Easy", 0},
        {"Medium", 1},
        {"Difficult", 2}
    };

    const Option* options;
    int numOptions;

    if (optionType == MODE) {
        options = modeOptions;
        numOptions = sizeof(modeOptions) / sizeof(modeOptions[0]);
    } else if (optionType == DIFFICULTY) {
        options = difficultyOptions;
        numOptions = sizeof(difficultyOptions) / sizeof(difficultyOptions[0]);
    } else {
        return -1; // 无效的选项类型
    }

    // 初始化ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // 获取屏幕尺寸
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);

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
            mvprintw(9 + i, 2, "· ");
            mvprintw(9 + i, 4, options[i].text);
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
                mvprintw(maxRows/2, maxCols/2 - strlen(options[currentOption].text)/2, "Selected: %s", options[currentOption].text);
                refresh();
                getch();
                clear();
                endwin();
                return options[currentOption].value;
        }
    }

    // 清理ncurses
    endwin();
    return -1; // 选择失败
}
