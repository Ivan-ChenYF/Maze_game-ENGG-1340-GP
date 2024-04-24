#include <ncurses.h>
#include <cstring>
#include <string>
#include <unistd.h>
#include "user_interface.h"
using namespace std;

int choiceUI(OptionType optionType, string username) {
    const Option modeOptions[] = {
        {"Classic Mode", 0},
        {"Fog Mode", 1},
        {"Resume Game", 2},
        {"End Game", 3}
    };

    const Option difficultyOptions[] = {
        {"Easy", 0},
        {"Medium", 1},
        {"Difficult", 2},
        {"Customize", 3}
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


void customize(int &width, int &height, int &timelimit, int &bomb, string username) {
    // 初始化ncurses
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
    string names[4] = {"Width(5-30)", "Height(5-30)", "Time Limit(>0)", "Number of Bomb(>=0)"};

    // 初始化输入框的值
    string values[4];

    // 当前选中的输入框索引
    int currentField = 0;
    bool invalid = false;

    while (true) {
        clear();
        PrintFromFile("ASCII - Main_Menu.txt");
        mvprintw(9, 0, (" Hi, " + username + ".").c_str());
        if (invalid)
            mvprintw(16, 2, "**Invalid Input!");

        // 打印输入框和值
        for (int i = 0; i < 4; i++) {
            if (i == currentField) {
                attron(A_REVERSE);  // 高亮当前选中的输入框
            }

            mvprintw(11 + i, 2, "· %s: %s", names[i].c_str(), values[i].c_str());

            if (i == currentField) {
                attroff(A_REVERSE);
            }
        }

        // 刷新屏幕
        refresh();

        // 获取用户输入
        int key = getch();

        // 处理用户输入
        if (key == KEY_UP) {
            if (invalid == false)
                currentField = (currentField - 1 + 4) % 4;  // 上移当前选中的输入框
        } else if (key == KEY_DOWN) {
            if (invalid == false )
                currentField = (currentField + 1) % 4;  // 下移当前选中的输入框
        } else if (key == '\n') {
            bool allFilled = true; // CHECK IF EMPTY
            for (const auto& value : values)
                if (value.empty()) 
                    allFilled = false;
            invalid = false;
            for (const auto& value : values[currentField])
                if (value < '0' || value > '9'){
                    invalid = true;
                }
            if (invalid)
                continue;
            if (values[currentField].empty()){
                currentField = (currentField + 1) % 4;
                continue;
            }
            int value = stoi(values[currentField]); // CHECK VALID INPUT
            if ((currentField == 0 || currentField == 1) && (value < 5 || value > 30))
                invalid = true;
            else if ((currentField == 2) && (value <= 0))
                invalid = true;
            else if ((currentField == 3) && (value < 0))
                invalid = true;
            else if (allFilled) {
                width = stoi(values[0]);
                height = stoi(values[1]);
                timelimit = stoi(values[2]);
                bomb = stoi(values[3]);
                return;
            }
            else{
                currentField = (currentField + 1) % 4;
            }
        } else if (key == KEY_BACKSPACE || key == 127) {
            // 处理退格键
            if (!values[currentField].empty()) {
                values[currentField].pop_back();  // 删除输入框中的最后一个字符
            }
        } else {
            // 处理数值输入
            values[currentField] += key;  // 将输入字符添加到当前选中的输入框中
            invalid = false;
            if (key < '0' || key > '9'){
                invalid = true;
                continue;
            }
            int value = stoi(values[currentField]); // CHECK VALID INPUT
            if ((currentField == 0 || currentField == 1) && (value < 5 || value > 30))
                invalid = true;
            else if ((currentField == 2) && (value <= 0))
                invalid = true;
            else if ((currentField == 3) && (value < 0))
                invalid = true;
        }
    }

    return;
}
