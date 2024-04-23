# Enigma Maze Game

Welcome to the Enigma Maze Game! This project is a text-based maze game where players navigate through a randomly generated maze with specific goals and challenges to overcome. The following sections explain the project's purpose, structure, setup, and gameplay instructions.

## Table of Contents
- [Project Overview](#project-overview)
- [Project Structure](#project-structure)
- [Installation and Setup](#installation-and-setup)
- [How to Play](#how-to-play)
  - [Game Controls](#game-controls)
  - [Gameplay Mechanics](#gameplay-mechanics)
- [Contributors](#contributors)
- [License](#license)

## Project Overview
The Enigma Maze Game is a simple ASCII-based maze game where players can create user profiles, explore a randomly generated maze, and try to reach the end. The game features ASCII art, interactive menus, and a variety of gameplay options.

## Project Structure
Here is an overview of the key files and their functions in the project:

- **Source Code**
  - `random_maze.cpp`: Contains the main game logic and random maze generation functions.
  - `random_maze.h`: Header file for maze-related definitions and functions.
  - `user_interface.h`: Header file for the user interface functions.

- **ASCII Art Files**
  - `ASCII - Create_User.txt`: ASCII art for the user creation menu.
  - `ASCII - Main_Menu.txt`: ASCII art for the main menu screen.
  - `ASCII - Enigma_Maze.txt`: ASCII art for the game title screen.
  - `ASCII - End.txt`: ASCII art for the game ending screen.

## Installation and Setup
To run the game, you'll need a C++ compiler and a terminal or command prompt. Follow these steps to compile and start the game:

1. **Clone the Repository**
   - Download or clone the project to your local machine.

2. **Compile the Code**
   - Open a terminal in the project's root directory.
   - Compile the source code. With Makefile, you can use the following command to create an executable file:
     ```bash
     make compile
     ```

3. **Run the Game**
   - Once the code is compiled, you can run the executable to start the game:
     ```bash
     make run
     ```

## How to Play
After launching the game, follow the on-screen instructions to create a user and navigate through the maze.

### Game Controls
- **Movement**: Use arrow keys or specific letters (`w`, `a`, `s`, `d`) to move through the maze.
- **Pause/Exit**: Use a designated key to pause or exit the game (e.g., `q` to quit).

### Gameplay Mechanics
- **Maze Navigation**: The maze is randomly generated, so each playthrough is unique.
- **Goals**: Reach the end of the maze or complete specific tasks to win the game.
- **Score**: Depending on the game's structure, there may be a scoring system based on completion time or other factors.

## Contributors
- **ENGG1340 Group 41**: Main developers and designers of the Enigma Maze Game.
- **YIFAN CHEN**
- ****

## License



