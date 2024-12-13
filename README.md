### Pac-Man Game in C++

This is a simple Pac-Man clone built using C++ and a console-based interface. The game features Pac-Man, ghosts, power-ups, and a score system. The game allows the player to navigate Pac-Man through a maze, eat dots, avoid ghosts, and collect power-ups to gain temporary invincibility.

<p align="center">
  <img src="https://www.uzebox.org/wiki/images/1/18/Pacman.png" alt="Pacman" width="600" />
</p>

## Table of Contents

- [Features](#features)
- [Controls](#controls)
- [Requirements](#requirements)
- [How to Run](#how-to-run)
## Features

- **Pac-Man**: Navigate Pac-Man using the arrow keys or WASD.
- **Ghosts**: Four ghosts with different behaviors: Inky, Pinky, Blinky, and Clyde.
- **Power-ups**: Collect power pellets to temporarily turn the ghosts vulnerable.
- **Score**: Increase your score by eating dots and power-ups.
- **Lives**: You have a limited number of lives.
- **Maze**: Simple maze structure with walls, dots, and power pellets.

## Controls

- **W / Up Arrow**: Move Pac-Man up.
- **S / Down Arrow**: Move Pac-Man down.
- **A / Left Arrow**: Move Pac-Man left.
- **D / Right Arrow**: Move Pac-Man right.

## Requirements

- C++ compiler (e.g., GCC, Clang, MSVC)
- Windows OS (for `windows.h` and `gotoxy` functionality)
- The code relies on the `windows.h` library for console cursor movement.
<h3 align="left">Languages and Tools:</h3>
<p align="left"> 
  <a href="https://en.wikipedia.org/wiki/C%2B%2B#/media/File:ISO_C++_Logo.svg" target="_blank" rel="noreferrer">
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" alt="C++" width="40" height="40"/> 
  </a>
  <a href="https://en.wikipedia.org/wiki/Visual_Studio" target="_blank" rel="noreferrer">
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/visualstudio/visualstudio-plain.svg" alt="Visual Studio" width="40" height="40"/> 
  </a>
</p>

## How to Run

1. Clone this repository:

   ```bash
   git clone https://github.com/your-username/pacman-cpp.git
   cd pacman-cpp
2. Compile the code using your preferred C++ compiler. For example, using g++:
 ```bash
 g++ -o pacman game.cpp -lm
./pacman

