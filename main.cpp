#include "random_maze.h"
#include "game_state.h"
#include "player_control.h"
#include "user_interface.h"
#include <iostream>
#include <ncurses.h>
#include <string>
#include <unistd.h>
using namespace std;
int fastest;
string fastest_name;

void classic_mode(cell** &maze,int width, int height, int player_x,int player_y,int start_time,double elapsed,int end_x,int end_y,int timelimit,int bomb){
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            maze[i][j].revealed = true;
        }
    }
    clear();
    printMaze(maze, width, height, player_x, player_y,end_x,end_y,bomb,timelimit-elapsed,fastest,fastest_name);
    refresh();
}
void fog_mode(cell** &maze,int width, int height, int player_x,int player_y,int start_time,double elapsed,int end_x,int end_y, int timelimit,int bomb){
    int centerIndex = 2; 
    int displaySize = 5; 
    int minX = max(0, player_x - centerIndex);
    int maxX = min(width - 1, player_x + centerIndex);
    int minY = max(0, player_y - centerIndex);
    int maxY = min(height - 1, player_y + centerIndex);

    // ensure the size of displayable area
    if (maxX - minX < displaySize - 1) {
        if (minX == 0) maxX = displaySize - 1; 
        if (maxX == width - 1) minX = width - displaySize;
    }
    if (maxY - minY < displaySize - 1) {
        if (minY == 0) maxY = displaySize - 1; 
        if (maxY == height - 1) minY = height - displaySize;
    }

    // set up the display area
    for (int i = minX; i <= maxX; i++) {
        for (int j = minY; j <= maxY; j++) {
            maze[i][j].revealed = true;
        }
    }


    clear();
    printMaze(maze, width, height, player_x, player_y,end_x,end_y,bomb,timelimit-elapsed,fastest,fastest_name);
    refresh();
    for (int i = minX; i <= maxX; i++) {
        for (int j = minY; j <= maxY; j++) {
            maze[i][j].revealed = false;
        }
    }
}

void difficult_level(int mode, int &width,int &height,int &start_x, int &start_y,int &timelimit,int &bomb, string username){
    if (mode==0){ //refer to easy
        width=height=10;
        timelimit=60;
        bomb=1;
    }
    else if (mode==1){ //refer to medium
        width=height=15;
        timelimit=100;
        bomb=2;
    }
    else if (mode==2){ // rerfer difficult
        width=height=20;
        timelimit=140;
        bomb=3;
    }
    else if (mode==3){ //customize mode
        customize(width, height, timelimit, bomb, username);
    }

    srand(time(nullptr));
    start_x=rand()%width;
    start_y=rand()%height;
}
int main(){ // the logical flow of the game
    int bomb=0;
    int timelimit;
    int ch;
    // Initialize maze parameters
    int width;
    int height;
    int start_x,start_y;
    int end_x,end_y;
    int difficulty;
    int mode;
    cell** maze=nullptr;
    double elapsed;
    double time_used;
    int player_x,player_y;
    GameState game; // Initialize gameState
    vector<double> time_rank; // Initialize ranking
    
   // LOADING PAGE
    setlocale(LC_ALL, "");
    initscr();
    curs_set(0);
    PrintFromFile("ASCII - Enigma_Maze.txt"); //the UI design
    getch();
    clear();
    refresh();
    
    // INPUT USERNAME
    PrintFromFile("ASCII - Create_User.txt");
    bool invalid = false;
    bool quit = false;
    while (true) {
        invalid = false;
        ch = getch();
        if (ch == KEY_BACKSPACE || ch == 127) {
            if (!game.player_name.empty()) {
                game.player_name.pop_back();
                refresh();
            }
        } else if (ch == '\n'){
            for (const auto& name : game.player_name)
                if (name == ' ')
                    invalid = true;
            if (game.player_name.empty())
                invalid = true;
            else
                quit = true;
        } else if (ch == ' ') {
            invalid = true;
        } else {
            game.player_name.push_back(ch);
        }
        clear();
        PrintFromFile("ASCII - Create_User.txt");
        printw(game.player_name.c_str());
        if (invalid)
            mvprintw(9,0,"**Username cannot contain whitespace or be empty!");
        if (quit)
            break;
    }
    clear();
    refresh();
    
    // cout << "Your user name is " << game.player_name << endl;
    bool gamestate=true;
    while (gamestate){
        mode = choiceUI(MODE, game.player_name);
        if (mode==0||mode==1){
            difficulty = choiceUI(DIFFICULTY, game.player_name);
            difficult_level(difficulty,width,height,start_x,start_y,timelimit,bomb, game.player_name);
            maze = new cell*[width]; //creating the maze using dynamic data
            for (int i = 0; i < width; ++i) {
                maze[i] = new cell [height];
            }
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    init(&maze[i][j],i,j);
                }
            }
            generateMaze(maze, width,height,start_x,start_y,end_x,end_y);
            time_used=0;
        }
        else if (mode == 2){
            int recordchoice = choiceUI(RECORD, game.player_name);
            switch(recordchoice)
            {
                case 0:
                    print_ranking("c_e.txt");
                    break;
                case 1:
                    print_ranking("c_m.txt");
                    break;
                case 2:
                    print_ranking("c_d.txt");
                    break;
                case 3:
                    print_ranking("fog_e.txt");
                    break;
                case 4:
                    print_ranking("fog_m.txt");
                    break;
                case 5:
                    print_ranking("fog_d.txt");
                    break;

            }
            continue;
        }


   


        else if (mode ==3){
            loadGame(game);  
            width=game.width;
            height=game.height;
            mode=game.mode;
            start_x=game.player_x;
            start_y=game.player_y;
            time_used=game.elapsed;   
            end_x=game.end_x;
            end_y=game.end_y;
            bomb=game.bomb;
            
            // After loading, we might need to setup the maze structure
            maze = new cell*[game.width];  
            for (int i = 0; i < game.width; ++i) {
                maze[i] = new cell[game.height];
            }

            // Initialize the maze cells with the loaded data
            for (int i = 0; i < game.width; ++i) {
                for (int j = 0; j < game.height; ++j) {
                    init(&maze[i][j], i, j);  // Assuming init() can set up each cell
                    // Alternatively, directly copy the data if available
                    maze[i][j].top_w = game.maze[i][j].top_w;  // Assuming deep copy is possible or necessary
                    maze[i][j].right_w = game.maze[i][j].right_w;
                    maze[i][j].left_w = game.maze[i][j].left_w;
                    maze[i][j].down_w = game.maze[i][j].down_w;
                    maze[i][j].revealed = game.maze[i][j].revealed;
                }
            }

        }
    
        else if (mode == 4){
            PrintFromFile("ASCII - End.txt");
            usleep(2000000);
            endwin();
            break;
        }


        if (mode==0&&difficulty==0){
            top("c_e.txt",fastest_name,fastest,timelimit);
        }
        else if (mode==0&&difficulty==1){
            top("c_m.txt",fastest_name,fastest,timelimit);
        }
        else if (mode==0&&difficulty==2){
            top("c_d.txt",fastest_name,fastest,timelimit);
        }
        else if (mode==1&&difficulty==0){
            top("fog_e.txt",fastest_name,fastest,timelimit);
        }
        else if (mode==1&&difficulty==1){
            top("fog_m.txt",fastest_name,fastest,timelimit);
        }
        else if (mode==1&&difficulty==2){
            top("fog_d.txt",fastest_name,fastest,timelimit);
        }

        
        
        time_t start_time = time(nullptr);
        time_t current_time;

        

        
        
        initscr();          // Start ncurses mode
        cbreak();           // Disable line buffering
        noecho();           // Don't echo user input
        keypad(stdscr, TRUE); // Enable function keys
        curs_set(0);        // Hide the cursor
        timeout(100);    
        
        

        
        
        player_x = start_x;
        player_y = start_y;
        
        

        
        while ((ch = getch()) != 'q') {
            
            
            current_time = time(nullptr);
            elapsed= difftime(current_time, start_time)+time_used;
            
            if (elapsed>timelimit){
                init_pair(1, COLOR_RED, COLOR_WHITE); // define the color 
                attron(COLOR_PAIR(1));  // define the color 
                usleep(100000);
                clear();
                PrintFromFile("ASCII - Try_Again.txt");
                usleep(2000000);
                attroff(COLOR_PAIR(1));
                break;
            }
            if (player_x==end_x&&player_y==end_y){
                init_pair(1, COLOR_RED, COLOR_WHITE); 
                attron(COLOR_PAIR(1));  
                usleep(100000);
                clear();
                PrintFromFile("ASCII - Well_Done.txt");
                usleep(2000000);
                attroff(COLOR_PAIR(1));
                
                break;
            }
            if (mode==0){
                classic_mode(maze,width, height, player_x,player_y, start_time, elapsed, end_x, end_y,timelimit,bomb);
            }
            else{
                fog_mode(maze,width, height, player_x,player_y, start_time, elapsed, end_x, end_y, timelimit,bomb);
            }
            if (ch == ERR) continue;
            
            player_movement(maze,width,height,player_x,player_y,ch,bomb);
            
        }
        // Get gameState
        game.mode = mode;
        game.difficulty = difficulty;
        game.maze = maze;
        game.width = width;
        game.height = height;
        game.player_x = player_x;
        game.player_y = player_y;
        game.end_x = end_x;
        game.end_y = end_y;
        game.bomb=bomb;
        game.elapsed=elapsed;
        saveGame(game);
        updateRank(elapsed,mode,difficulty,game.player_name);
        endwin();
    }
    
    PrintFromFile("ASCII - End.txt");
    usleep(2000000);
    endwin();
    return 0;
}

