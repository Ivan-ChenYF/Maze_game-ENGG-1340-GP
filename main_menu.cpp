#include <ncurses.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include "user_interface.h"
using namespace std;

int choiceUI(OptionType optionType, string username) {
    const Option modeOptions[] = {
        {"Classic Mode", 0},
        {"Frog Mode", 1},
        {"Resume Game", 2},
        {"End Game", 3}
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
        mvprintw(9, 0, (" Hi, " + username + ".").c_str());

        // 打印选项
        for (int i = 0; i < numOptions; i++) {
            if (i == currentOption) {
                // 设置选中项的颜色为白底黑字
                attron(A_REVERSE);
                attron(COLOR_PAIR(1));
            }
            mvprintw(11 + i, 2, "· ");
            mvprintw(11 + i, 4, options[i].text);
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
                mvprintw(maxRows/2 - 1, maxCols/2 - (strlen(options[currentOption].text) + 10)/2, "Selected: %s", options[currentOption].text);
                refresh();
                usleep(700000);
                mvprintw(maxRows/2, maxCols/2 - strlen("Loading...")/2, "Loading...");
                refresh();
                usleep(1900000);
                clear();
                refresh();
                return options[currentOption].value;
        }
    }

    // 清理ncurses
    endwin();
    return -1; // 选择失败
}


void customize(int &width, int &height, int &start_x, int &start_y) {
    // 初始化 ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // 获取窗口尺寸
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);

    // 定义输入框的位置
    int startX = maxCols / 2 - 15;
    int startY = maxRows / 2 - 2;

    // 定义输入框的名称
    std::string names[4] = {" · Width(5-30)", " · Height(5-30)", " · Start Point(x)", " · Start Point(y)"};

    // 初始化输入框的值
    int values[4] = {15, 15, 0, 0};

    // 当前选中的输入框索引
    int currentField = 0;

    while (true) {
        clear();
        PrintFromFile("ASCII - Main_Menu.txt");

        // 打印界面标题
        mvprintw(9, 0, "Press left or right key to decrease or increase value");

        // 打印输入框
        for (int i = 0; i < 4; i++) {
            if (i == currentField) {
                attron(A_REVERSE);  // 高亮当前选中的输入框
            }

            mvprintw(11 + i, 0, "%s: %d", names[i].c_str(), values[i]);

            if (i == currentField) {
                attroff(A_REVERSE);
            }
        }

        // 刷新屏幕
        refresh();

        // 获取用户输入
        int key = getch();

        // 处理用户输入
        switch (key) {
            case KEY_UP:
                currentField = (currentField - 1 + 4) % 4;  // 上移当前选中的输入框
                break;
            case KEY_DOWN:
                currentField = (currentField + 1) % 4;  // 下移当前选中的输入框
                break;
            case KEY_LEFT:
                if (currentField == 0 || currentField == 1) {
                    values[currentField] -= 2;  // 减少第一个和第二个输入框的值
                    if (values[currentField] < 5) {
                        values[currentField] = 5;  // 保证值不小于5
                    }
                } else {
                    values[currentField]--;  // 减少第三个和第四个输入框的值
                    if (values[currentField] < 0 || values[currentField] >= values[currentField - 2]) {
                        values[currentField] = 0;  // 保证值不小于0且不大于第一个或第二个值
                    }
                }
                break;
            case KEY_RIGHT:
                if (currentField == 0 || currentField == 1) {
                    values[currentField] += 2;  // 增加第一个和第二个输入框的值
                    if (values[currentField] > 30) {
                        values[currentField] = 30;  // 保证值不大于30
                    }
                } else {
                    values[currentField]++;  // 增加第三个和第四个输入框的值
                    if (values[currentField] >= values[currentField - 2] || values[currentField] < 0) {
                        values[currentField] = values[currentField - 2] -1;  // 保证值不大于第一个或第二个值且不小于0
                    }
                }
                break;
            case '\n':
                if (currentField == 3) {
                    width = values[0];
                    height = values[1];
                    start_x = values[2];
                    start_y = values[3];
                    return;
                }
                currentField++;
                break;
            default:
                break;
        }
    }

    return;
}
