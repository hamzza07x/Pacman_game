//necessary header files
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include<math.h>
#include "game.h"
//color macros for console output
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define PINK "\033[35m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
//directional key codes for arrows
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//constructor to intialzie game state
Game::Game() : pacman_x(19), pacman_y(18), score(0), power_up_duration(75), power_up_timer(0),lives(3) {
    srand(time(0));//generates random time
    ghost_inky = { 15, 11 };
    ghost_pinky = { 16, 11 };
    ghost_blinky = { 17, 11 };
    ghost_clyder = { 16, 10 };
    this->power_up = false;
}
//activates power up and starts power up timer
void Game::activate_power_up() {
    power_up = true;
    this->power_up_timer = this->power_up_duration;
}
//update power up timer deactivate if time runs out
void Game::update_power_up() {
    if (this->power_up) {
        if (this->power_up_timer > 0) {
            this->power_up_timer--;//decrease timer
        }
        else {
            this->power_up = false;//deactivates powerup
        }
    }
}
//print game map to the console
void Game::print_map() const {
    //system("cls");
    gotoxy(pacman_x, pacman_y);
    cout << GREEN << 'P' << RESET;

    gotoxy(ghost_inky.x, ghost_inky.y);
    cout << RED << 'G' << RESET;

    gotoxy(ghost_pinky.x, ghost_pinky.y);
    cout << PINK << 'Q' << RESET;

    gotoxy(ghost_blinky.x, ghost_blinky.y);
    cout << BLUE << 'O' << RESET;

    gotoxy(ghost_clyder.x, ghost_clyder.y);
    cout << YELLOW << 'X' << RESET;

    for (int y = 0; y < 30; y++) {//map rows
        for (int x = 0; x < 40; x++) {//map columns
            gotoxy(x, y);
            if (x == pacman_x && y == pacman_y) {
                cout << GREEN << 'P' << RESET;//pacman
            }
            else if (x == ghost_inky.x && y == ghost_inky.y) {
                cout << RED << 'G' << RESET;//inky
            }
            else if (x == ghost_pinky.x && y == ghost_pinky.y) {
                cout << PINK << 'Q' << RESET;//pinky
            }
            else if (x == ghost_blinky.x && y == ghost_blinky.y) {
                cout << BLUE << 'O' << RESET;//blinky
            }
            else if (x == ghost_clyder.x && y == ghost_clyder.y) {
                cout << YELLOW << 'X' << RESET;//clyde
            }
            else if (pacman_map[y][x] == '.') {//coins or dots
                cout << YELLOW << pacman_map[y][x] << RESET;
            }
            else if (pacman_map[y][x] == 'o') {
                cout << RED << pacman_map[y][x] << RESET;//power pellets
            }
            else {
                cout << BLUE << pacman_map[y][x] << RESET;//walss or remaining map
            }
        }
        cout << endl;
    }
    gotoxy(0, 30);
    //gotoxy(0, 30);
    cout << "Score: " << this->score << endl;
    cout << "Lives: " << this->lives - 1 << endl;
    //system("cls");
}
//updates pacman position according to user input
void Game::update_position(char direction) {
    if ((direction == 'w' || direction == 'W' || direction == UP) && pacman_map[pacman_y - 1][pacman_x] != '*') {
        pacman_y--;
        if (pacman_map[pacman_y][pacman_x] == '.') {
            this->score++;//increment score for eating food
            pacman_map[pacman_y][pacman_x] = ' ';
        }
        else if (pacman_map[pacman_y][pacman_x] == 'o') {
            activate_power_up();
            this->score = this->score + 10;
            pacman_map[pacman_y][pacman_x] = ' ';//create empty space
        }
    }
    else if ((direction == 's' || direction == 'S' || direction == DOWN) && pacman_map[pacman_y + 1][pacman_x] != '*') {
        pacman_y++;
        if (pacman_map[pacman_y][pacman_x] == '.') {
            this->score++;//increment score for eating food
            pacman_map[pacman_y][pacman_x] = ' ';
        }
        else if (pacman_map[pacman_y][pacman_x] == 'o') {
            activate_power_up();
            this->score = this->score + 10;
            pacman_map[pacman_y][pacman_x] = ' ';//create empty space
        }
    }
    else if ((direction == 'a' || direction == 'A' || direction == LEFT) && pacman_map[pacman_y][pacman_x - 1] != '*') {
        pacman_x--;
        if (pacman_map[pacman_y][pacman_x] == '.') {
            this->score++;//increment score for eating food
            pacman_map[pacman_y][pacman_x] = ' ';
        }
        else if (pacman_map[pacman_y][pacman_x] == 'o') {
            activate_power_up();
            this->score = this->score + 10;
            pacman_map[pacman_y][pacman_x] = ' ';//create empty space
        }
    }
    else if ((direction == 'd' || direction == 'D' || direction == RIGHT) && pacman_map[pacman_y][pacman_x + 1] != '*') {
    pacman_x++;
    if (pacman_map[pacman_y][pacman_x] == '.') {
        this->score++;//increment score for eating food
        pacman_map[pacman_y][pacman_x] = ' ';
    }
    else if (pacman_map[pacman_y][pacman_x] == 'o') {
        activate_power_up();
        this->score = this->score + 10;
        pacman_map[pacman_y][pacman_x] = ' ';//create empty space
    }
    }
}
//updates inky position based on its logic
void Game::update_ghost_inky() {
    update_inky_chase(ghost_inky);
}
//inky chase behaviour
void Game::update_inky_chase(Ghost& ghost) {
    if (get_poer_up_status()) {
        if (rand() % 2 == 0) {
            int direction = rand() % 4;
            if (direction == 0 && pacman_map[ghost_inky.y][ghost_inky.x - 1] != '*') {
                ghost_inky.x--;
            }
            else if (direction == 1 && pacman_map[ghost_inky.y][ghost_inky.x + 1] != '*') {
                ghost_inky.x++;
            }
            else if (direction == 2 && pacman_map[ghost_inky.y + 1][ghost_inky.x] != '*') {
                ghost_inky.y++;;
            }
            else if (direction == 3 && pacman_map[ghost_inky.y - 1][ghost_inky.x] != '*') {
                ghost_inky.y--;;
            }
        }
    }
    else {
        int direction_x = 40 - ghost.x;
        int direction_y = this->pacman_y - ghost.y;
        if (abs(direction_x) > abs(direction_y)) {
            if (direction_x > 0 && pacman_map[ghost.y][ghost.x + 1] != '*') {
                ghost.x++;
            }
            else if (direction_x < 0 && pacman_map[ghost.y][ghost.x - 1] != '*') {
                ghost.x--;
            }
            else if (direction_y > 0 && pacman_map[ghost.y + 1][ghost.x] != '*') {
                ghost.y++;
            }
            else if (direction_y < 0 && pacman_map[ghost.y - 1][ghost.x] != '*') {
                ghost.y--;
            }
        }
    }
}
//updates pinky according to its logic
void Game::update_ghost_pinky() {
    update_pinky_chase(ghost_pinky);
}
//pinky chase behaviour
void Game::update_pinky_chase(Ghost& ghost) {
    if (get_poer_up_status()) {
        int direction = rand() % 4;
        if (direction == 0 && pacman_map[ghost.y - 1][ghost.x] != '*') {
            ghost.y--;
        }
        else if (direction == 1 && pacman_map[ghost.y + 1][ghost.x] != '*') {
            ghost.y++;
        }
        else if (direction == 2 && pacman_map[ghost.y][ghost.x - 1] != '*') {
            ghost.x--;
        }
        else if (direction == 3 && pacman_map[ghost.y][ghost.x + 1] != '*') {
            ghost.x++;
        }
    }
    else {
        int direction_x = this->pacman_x - ghost.x;
        int direction_y = this->ghost_clyder.y - ghost.y;

        if (abs(direction_x) > abs(direction_y)) {
            if (direction_x > 0 && pacman_map[ghost.y][ghost.x + 1] != '*') {
                ghost.x++;
            }
            else if (direction_x < 0 && pacman_map[ghost.y][ghost.x - 1] != '*') {
                ghost.x--;
            }
            else if (direction_y > 0 && pacman_map[ghost.y + 1][ghost.x] != '*') {
                ghost.y++;
            }
            else if (direction_y < 0 && pacman_map[ghost.y - 1][ghost.x] != '*') {
                ghost.y--;
            }
        }
        else {
            if (direction_y > 0 && pacman_map[ghost.y + 1][ghost.x] != '*') {
                ghost.y++;
            }
            else if (direction_y < 0 && pacman_map[ghost.y - 1][ghost.x] != '*') {
                ghost.y--;
            }
            else if (direction_x > 0 && pacman_map[ghost.y][ghost.x + 1] != '*') {
                ghost.x++;
            }
            else if (direction_x < 0 && pacman_map[ghost.y][ghost.x - 1] != '*') {
                ghost.x--;
            }
        }
    }
}
//updates blinky according to its logic
void Game::update_ghost_blinky() {
    update_blinky_chase(ghost_blinky);
}
//blinky chase behaviour
void Game::update_blinky_chase(Ghost& ghost) {
    if (get_poer_up_status()) {
        if (rand() % 3 == 0) {
            int direction = rand() % 4;
            if (direction == 0 && pacman_map[ghost.y - 1][ghost.x] != '*') {
                ghost.y--;
            }
            else if (direction == 1 && pacman_map[ghost.y + 1][ghost.x] != '*') {
                ghost.y++;
            }
            else if (direction == 2 && pacman_map[ghost.y][ghost.x - 1] != '*') {
                ghost.x--;
            }
            else if (direction == 3 && pacman_map[ghost.y][ghost.x + 1] != '*') {
                ghost.x++;
            }
        }
    }
    else {
        int direction_x = this->ghost_clyder.x - ghost.x;
        int direction_y = this->pacman_y - ghost.y;

        if (abs(direction_x) > abs(direction_y)) {
            if (direction_x > 0 && pacman_map[ghost.y][ghost.x + 1] != '*') {
                ghost.x++;
            }
            else if (direction_x < 0 && pacman_map[ghost.y][ghost.x - 1] != '*') {
                ghost.x--;
            }
            else if (direction_y > 0 && pacman_map[ghost.y + 1][ghost.x] != '*') {
                ghost.y++;
            }
            else if (direction_y < 0 && pacman_map[ghost.y - 1][ghost.x] != '*') {
                ghost.y--;
            }
        }
    }
}
//updates clyde according to its logic
void Game::update_ghost_clyde() {
    update_clyde_chase(ghost_clyder);
}
//clyde chase behaviour
void Game::update_clyde_chase(Ghost& ghost) {
    if (get_poer_up_status()) {
        int direction = rand() % 4;
        if (direction == 0 && pacman_map[ghost.y - 1][ghost.x] != '*') {
            ghost.y--;
        }
        else if (direction == 1 && pacman_map[ghost.y + 1][ghost.x] != '*') {
            ghost.y++;
        }
        else if (direction == 2 && pacman_map[ghost.y][ghost.x - 1] != '*') {
            ghost.x--;
        }
        else if (direction == 3 && pacman_map[ghost.y][ghost.x + 1] != '*') {
            ghost.x++;
        }
    }
    else {
        int direction_x = this->pacman_x - ghost.x;
        int direction_y = this->pacman_y - ghost.y;
        if (abs(direction_y) >= abs(direction_x)) {
            if (direction_y > 0 && pacman_map[ghost.y + 1][ghost.x] != '*') {
                ghost.y++;
            }
            else if (direction_y < 0 && pacman_map[ghost.y - 1][ghost.x] != '*') {
                ghost.y--;
            }
            else if (direction_x > 0 && pacman_map[ghost.y][ghost.x + 1] != '*') {
                ghost.x++;
            }
            else if (direction_x < 0 && pacman_map[ghost.y][ghost.x - 1] != '*') {
                ghost.x--;
            }
        }
        else {
            if (direction_x > 0 && pacman_map[ghost.y][ghost.x + 1] != '*') {
                ghost.x++;
            }
            else if (direction_x < 0 && pacman_map[ghost.y][ghost.x - 1] != '*') {
                ghost.x--;
            }
            else if (direction_y > 0 && pacman_map[ghost.y + 1][ghost.x] != '*') {
                ghost.y++;
            }
            else if (direction_y < 0 && pacman_map[ghost.y - 1][ghost.x] != '*') {
                ghost.y--;
            }
        }
    }
}
//return current pacman position x axis
int Game::get_pacman_x() const {
    return this->pacman_x;
}
//returns pacman current postion y axis
int Game::get_pacman_y() const {
    return this->pacman_y;
}
//returns current score
int Game::get_score() const {
    return this->score;
}
//return cureent or remaining lives
int Game::get_lives()const {
    return this->lives;
}
//returns power up state
bool Game::get_poer_up_status()const {
    return this->power_up;
}
//handles collision logic and power up states
bool Game::check_collision() {
    //when power is activated
    if (this->power_up) {
        if (pacman_x == ghost_inky.x && pacman_y == ghost_inky.y) {
            reset_ghosts(ghost_inky);
            this->score += 50;
            return false;
        }
        else if (pacman_x == ghost_pinky.x && pacman_y == ghost_pinky.y) {
            reset_ghosts(ghost_pinky);
            this->score += 50;
            return false;
        }
        else if (pacman_x == ghost_blinky.x && pacman_y == ghost_blinky.y) {
            reset_ghosts(ghost_blinky);
            this->score += 50;
            return false;
        }
        else if (pacman_x == ghost_clyder.x && pacman_y == ghost_clyder.y) {
            reset_ghosts(ghost_clyder);
            this->score += 50;
            return false;
        }
    }
    //without power up
    else {
        if ((pacman_x == ghost_inky.x && pacman_y == ghost_inky.y) ||
            (pacman_x == ghost_pinky.x && pacman_y == ghost_pinky.y) ||
            (pacman_x == ghost_blinky.x && pacman_y == ghost_blinky.y) ||
            (pacman_x == ghost_clyder.x && pacman_y == ghost_clyder.y)) {
            this->lives--;
            this->pacman_x = 19;
            this->pacman_y = 18;

            if (this->lives ==0) {
                return true;
            }
            return false;
        }
    }
    return false;
}

void Game::reset_ghosts(Ghost& ghost) {
    if (&ghost == &ghost_pinky) {
        ghost.x = 16;
        ghost.y = 11;
    }
    else if (&ghost == &ghost_blinky) {
        ghost.x = 17;
        ghost.y = 11;
    }
    else if (&ghost == &ghost_inky) {
        ghost.x = 15;
        ghost.y = 11;
    }
    else if (&ghost == &ghost_clyder) {
        ghost.x = 16;
        ghost.y = 10;
    }
}
//saves the map grid to a temporary map so that it reloads the map after each play
void Game::save_map() {
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 40; y++) {
            temp_map[x][y] = pacman_map[x][y];
        }
    }
}
//restores the map so that map map reloads after each play
void Game::restore_map() {
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 40; y++) {
            pacman_map[x][y] = temp_map[x][y];
        }
    }
}
//game destructor to destroy game object
Game::~Game() {

}
//player constructor
Player::Player(Game& game) :game(game),direction(' ') {

}
//moves the pacman according to the input direction
void Player::move() {
    if (_kbhit() != 0) {
        this->direction = _getch();
        set_direction(this->direction);
    }
    game.update_position(direction);
    game.update_power_up();
}
//dispalyes the map grid and alert if power up activates 
void Player::display() {
    game.print_map();
    if (game.get_poer_up_status()) {
        gotoxy(0, 34);
        cout << RED << "POWER UP activate eat ghosts...." << RESET << endl;
    }
    else {
        gotoxy(0, 34);
        cout << "                                                " << endl;
    }
}
//sets the direction to some random initial direction as i have set to dir first user input
void Player::set_direction(char dir) {
    this->direction = dir;
}
//returns current direction from user input
char Player::get_direction()const {
    return this->direction;
}
//player destructor
Player::~Player() {

}
