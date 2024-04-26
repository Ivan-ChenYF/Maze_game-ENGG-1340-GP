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
        {"Record", 2},
        {"Resume Game", 3},
        {"End Game", 4}
    };

    const Option difficultyOptions[] = {
        {"Easy", 0},
        {"Medium", 1},
        {"Difficult", 2},
        {"Customize", 3}
    };

    const Option recordOptions[] = {
        {"Classic - Easy", 0},
        {"Classic - Medium", 1},
        {"Classic - Difficult", 2},
        {"Fog - Easy", 3},
        {"Fog - Medium", 4},
        {"Fog - Difficult", 5}
    };

    const Option* options;
    int numOptions;

    if (optionType == MODE) {
        options = modeOptions;
        numOptions = sizeof(modeOptions) / sizeof(modeOptions[0]);
    } else if (optionType == DIFFICULTY) {
        options = difficultyOptions;
        numOptions = sizeof(difficultyOptions) / sizeof(difficultyOptions[0]);
    } else if (optionType == RECORD){
        options = recordOptions;
        numOptions = sizeof(recordOptions) / sizeof(recordOptions[0]);
    } else {
        return -1; // INVALIE OPTION TYPE
    }

    // INITIALIZE NCURSES
    initscr();
    flushinp();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(-1);

    // GET SCREEN SIZE
    int maxRows, maxCols;
    getmaxyx(stdscr, maxRows, maxCols);

    int currentOption = 0;

    while (true) {

        // PRINT MAIN MENU
        clear();
        PrintFromFile("ASCII - Main_Menu.txt");
        mvprintw(9, 0, (" Hi, " + username + ".").c_str());

        // PRINT CHOICES
        for (int i = 0; i < numOptions; i++) {
            if (i == currentOption) {
                // SLECTED ITEM -> DIFFERENT COLOR
                attron(A_REVERSE);
                attron(COLOR_PAIR(1));
            }
            mvprintw(11 + i, 2, "· ");
            mvprintw(11 + i, 4, options[i].text);
            attroff(A_REVERSE);
            attroff(COLOR_PAIR(1));
        }

        refresh();

        // USER INPUT
        int input = getch();
        switch (input) {
            case KEY_UP:
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                break;
            case KEY_DOWN:
                currentOption = (currentOption + 1) % numOptions;
                break;
            case '\n':
                // SELECTION (ENTER)
                clear();
                mvprintw(maxRows/2 - 1, maxCols/2 - (strlen(options[currentOption].text) + 10)/2, "Selected: %s", options[currentOption].text);
                refresh();
                usleep(450000);
                mvprintw(maxRows/2, maxCols/2 - strlen("Loading...")/2, "Loading...");
                refresh();
                usleep(350000);
                clear();
                refresh();
                return options[currentOption].value;
        }
    }

    endwin();
    return -1; // SELECTION FAILED
}


void customize(int &width, int &height, int &timelimit, int &bomb, string username) {
    
    // INITIALIZE NCURSES
    initscr();
    flushinp();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    timeout(-1);

    // NAME OF INPUT BOX
    string names[4] = {"Width(5-30)", "Height(5-30)", "Time Limit(>0)", "Number of Bomb(>=0)"};

    // VALUE OF INPUT BOX
    string values[4];

    int currentField = 0;
    bool invalid = false;

    while (true) {
        clear();
        PrintFromFile("ASCII - Main_Menu.txt");
        mvprintw(9, 0, (" Hi, " + username + ".").c_str());
        if (invalid)
            mvprintw(16, 2, "**Invalid Input!");

        // PRINT INPUT BOX
        for (int i = 0; i < 4; i++) {
            if (i == currentField) {
                attron(A_REVERSE);  // CURRENT SELECTION -> DIFFERENT COLOR
            }

            mvprintw(11 + i, 2, "· %s: %s", names[i].c_str(), values[i].c_str());

            if (i == currentField) {
                attroff(A_REVERSE);
            }
        }

        refresh();

        // USER INPUT
        int key = getch();

        if (key == KEY_UP) {
            if (invalid == false)
                currentField = (currentField - 1 + 4) % 4;  // MOVE THE CURRENT SELECTION UP
        } else if (key == KEY_DOWN) {
            if (invalid == false )
                currentField = (currentField + 1) % 4;  // MOVE THE CURRENT SELECTION DOWN
        } else if (key == '\n') {
            bool allFilled = true; // CHECK IF EMPTY
            for (const auto& value : values)
                if (value.empty()) 
                    allFilled = false;
            invalid = false;
            for (const auto& value : values[currentField])
                if (value < '0' || value > '9')
                    invalid = true;
            if (invalid)
                continue; // INVALID INPUT
            if (values[currentField].empty()){
                currentField = (currentField + 1) % 4;
                continue; // SOME BOX ARE NOT FILLED
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
                return; // RETURN INPUT (PASS BY REFERENCE)
            }
            else{
                currentField = (currentField + 1) % 4;
            }
        } else if (key == KEY_BACKSPACE || key == 127) {
            // HANDLE BACKSPACE KEY
            if (!values[currentField].empty()) {
                values[currentField].pop_back();  // DELETE THE LAST CHAR OF THE BOX
            }
            invalid = false;
            if (values[currentField].empty())
                continue; // NO VALUE
            for (const auto& value : values[currentField])
                if (value < '0' || value > '9')
                    invalid = true;
            if (invalid)
                continue; // CONTAIN INVALID INPUT
            int value = stoi(values[currentField]); // CHECK VALID INPUT
            if ((currentField == 0 || currentField == 1) && (value < 5 || value > 30))
                invalid = true;
            else if ((currentField == 2) && (value <= 0))
                invalid = true;
            else if ((currentField == 3) && (value < 0))
                invalid = true;
        } else {
            // HANDLE VALUE INPUT
            values[currentField] += key;  // ADD INPUT TO THE VALUE
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
