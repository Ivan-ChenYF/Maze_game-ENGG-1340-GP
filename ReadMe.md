# Enigma Maze Game 🚀🎮 

🎩✨ Welcome to the Enigma Maze Game! Get ready for an awesome adventure where you'll explore a maze full of surprises and challenges!

🔍💡 Ever wondered what it's like to navigate through a maze with a time limit or fog blocking your vision? Well, you're about to find out! In this text-based adventure, you'll be thrown into a maze filled with unpredictability and quirky characters.

🌟🧠 You're in for a real challenge with different exciting difficulty levels to choose from! Whether you're a maze master or just starting out, there's something for everyone. Pick your level wisely as you navigate through the maze – see if you can be the top player in Enigma Maze Game.

📜 Inside this README, you'll find everything you need to know about the game. From understanding the purpose of Enigma Maze to setting up your game environment and mastering the gameplay, consider this your ultimate guide to maze-navigating madness.

 

## Table of Contents
- [Project Overview](#project-overview)
- [How to Play](#how-to-play)
- [Project Structure](#project-structure)
- [Installation and Setup](#installation-and-setup)
- [Contributors](#contributors)
- [License](#license)

## Project Overview
The Enigma Maze Game is a simple text maze game based on ncurses library where players can create user profiles, explore a randomly generated maze, and try to reach the end. The game features ASCII art, interactive menus, and a variety of gameplay options.

## How to Play
After launching the game, follow the on-screen instructions to create a user and navigate through the maze.
- 🗺️Classical mode: Navigate the maze directly in the most classical way
- 🌫️Fog mode: This will be more difficult as your vision is blocked by a crowd fog.
<p align="center">
  <a href="https://www.youtube.com/watch?v=gTnuDBI7-Vk">
    <img src="https://img.youtube.com/vi/gTnuDBI7-Vk/0.jpg" alt="Watch the video">
  </a>
</p>


### Game Controls
- **Navigation**: Use Enter for double click and arrow key for navigating the choices.
- **Movement**: Use arrow keys or specific letters (`w`, `a`, `s`, `d`) to move through the maze.
- **Pause/Exit**: Use a designated key to pause or exit the game (e.g., `q` to quit).
- **Bomb**: Use a `b` key to pick up the bomb, then use the arrow keys to select the direction of the wall you want to destroy.

## Project Structure
**Library Used**
- Standard library is used with addition of ncurses, ctime and unistd
- Here is an overview of the key files and their functions in the project:

**Source Code**
- `main.cpp`: The main entry point for the game, responsible for initialization and setup. It allows the player to choose the game mode they want.
- `game_state.cpp` and `game_state.h`: Handles the game state, including player position, score, and maze information.
- `random_maze.cpp` and `random_maze.h`: Contains the logic for generating random mazes, relying on DFS algorithms that uses the backtracking principle and providing unqie maze for each play.
- `player_control.cpp` and `player_control.h`: Manages player controls, movement logic and bomb function.
- `print_maze.cpp`: Responsible for printing and displaying maze content. It includes  the visualization of the maze using ncurses, defining boundary and time remains.
- `main_menu.cpp`: Contains logic for the main menu.
- `print_file.cpp`: Handles the printing of files and interface components, including features like displaying ASCII art and accepting user names to engage player
- `user_interface.h`: Defines functions related to the user interface.

**ASCII Art Files**
- `ASCII - Create_User.txt`: ASCII art for the user creation screen.
- `ASCII - Main_Menu.txt`: ASCII art for the main menu.
- `ASCII - Enigma_Maze.txt`: ASCII art for the game title screen.
- `ASCII - Try_Again.txt`: ASCII art for the end-of-game screen(lose).
- `ASCII - Well_Done.txt`: ASCII art for the end-of-game screen(win).
- `ASCII - End.txt`: ASCII art for the end-of-game screen(quit).

**Record**
- `c_e.txt, c_m, c_d.txt` are used for storing records of classical mode
- `f_e.txt, f_m, f_d.txt` are used for storing records of fog mode

**coding requirements**
- ✅ Generation of random game sets or events
   - the maze is generated randomly in each new game using DFS algorithms.  (see **generateMaze()** in [random_maze.cpp](https://github.com/Ivan-ChenYF/ENGG-1340-GP/blob/main/random_maze.cpp))
- ✅ Data structures for storing game status 
   - Dynamic array is used for storing and updating player movement and location inside the maze. (see **player_movement()** in [player_control.cpp](https://github.com/Ivan-ChenYF/ENGG-1340-GP/blob/main/player_control.cpp) [main.cpp] 
- ✅ Dynamic memory management
   - This feature is reflected in the customize mode where player is allowed to input the size of maze they want. (see [main.cpp](https://github.com/Ivan-ChenYF/ENGG-1340-GP/blob/main/main.cpp)
- ✅ File input/output 
   - Players can quit the game in the middle while saving the game status through the game_state function. (see [game_state.cpp](https://github.com/Ivan-ChenYF/ENGG-1340-GP/blob/main/game_state.cpp)
- ✅ Program codes in multiple files 
   - UI design, player control, maze generation and game saving function are coded separately. 
- ✅ Proper indentation and naming styles
- ✅ In-code documentation

## Installation and Setup
To run the game, you'll need a C++ compiler and a terminal or command prompt. Follow these steps to compile and start the game:

1. **Clone the Repository**
   - Open the Terminal in your computer.
   - Download or clone the project to your local machine by using the command line here.
     ```bash
     git clone https://github.com/Ivan-ChenYF/ENGG-1340-GP.git
     ```

3. **Compile the Code**
   - Switch to the directory where you clone the game
   - Compile the source code. With Makefile, you can use the following command to create an executable file:
     ```bash
     make compile
     ```

4. **Run the Game**
   - Once the code is compiled, you can run the executable to start the game:
     ```bash
     make run
     ```

## Contributors
 **Main developers and designers of the Enigma Maze Game:**
- **YiFan Chen  3036253809 ivan2004@connect.hku.hk**
- **Xie Yee Lam  3036222719  bylinmou@connect.hku.hk**
- **Wu Yu Kwan  3036003670  yukwan24@connect.hku.hk**
- **Lok Hoi Cheuk  3036066763  tlhc@connect.hku.hk**

## License


