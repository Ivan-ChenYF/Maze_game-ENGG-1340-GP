#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <vector>
#include <string>
using namespace std;

enum OptionType {
    MODE,
    DIFFICULTY
};

struct Option {
    const char* text;
    int value;
};

void PrintFromFile(std::string filename);
int choiceUI(OptionType optionType, string username);
void customize(int &width, int &height, int &start_x, int &start_y);

#endif
