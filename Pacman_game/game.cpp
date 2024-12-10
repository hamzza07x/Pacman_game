#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include<math.h>
#include "game.h"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define PINK "\033[35m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;

char pacman_map[20][40] = {
    "#######################################",
    "#oo###############..##############.. .#",
    "#oo...................................#",
    "#.#############...############......#.#",
    "#.#.#.............................#.#.#",
    "#.#.#.#######...........###########.#.#",
    "#.#.#.#...........o.................#.#",
    "#.#.#.#####.................#######.#.#",
    "#.#.#.#............#...#..........#.#.#",
    "#.#.#.# ##.........#...#............#.#",
    "#.#.#.# ##.........#.o.#.........##.#.#",
    "#.#.#o#............##.##o.........o.#.#",
    "#.###############.......###########...#",
    "#.#######...........................###",
    "#...o######.....##.......o#########.###",
    "#.#..#...........#.................o###",
    "#.#...................................#",
    "#.#o.#...#####........#############...#",
    "#.####.....................o######....#",
    "#######################################",
};

Game::Game() : pacman_x(36), pacman_y(1), score(0),power_up_duration(75),power_up_timer(0) {
    srand(time(0));
    ghost_inky = { 1, 1 };
    ghost_pinky = { 2, 1 };
    ghost_blinky = { 2, 2 };
    ghost_clyder = { 1, 2 };
    this->power_up = false;
}

void Game::activate_power_up() {
    power_up = true;
    this->power_up_timer = this->power_up_duration;
}

void Game::update_power_up() {
    if (this->power_up) {
        if (this->power_up_timer > 0) {
            this->power_up_timer--;
        }
        else {
            this->power_up = false;
        }
   }
}

void Game::print_map() const {
    system("cls");
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 40; x++) {
            if (x == pacman_x && y == pacman_y) {
                cout << GREEN << 'P' << RESET;
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
                cout << YELLOW << 'O' << RESET;//clyde
            }
            else {
                cout <<GREEN<< pacman_map[y][x];
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

void Game::update_position(char direction) {
    if ((direction == 'w' || direction == 'W' || direction == UP) && pacman_map[pacman_y - 1][pacman_x] != '#') {
        pacman_y--;
        if (pacman_map[pacman_y][pacman_x] == '.') {  // Check if there is a dot
            score++;  // Increase score for eating the dot
            pacman_map[pacman_y][pacman_x] = ' ';  // Remove the dot
        }
        else if (pacman_map[pacman_y][pacman_x] == 'o') {
            activate_power_up();
            this->score = this->score + 10;
            pacman_map[pacman_y][pacman_x] = ' ';
        }
    }
    else if ((direction == 's' || direction == 'S' || direction == DOWN) && pacman_map[pacman_y + 1][pacman_x] != '#') {
        pacman_y++;
        if (pacman_map[pacman_y][pacman_x] == '.') {
            score++;
            pacman_map[pacman_y][pacman_x] = ' ';
        }
        else if (pacman_map[pacman_y][pacman_x] == 'o') {
            activate_power_up();
            this->score = this->score + 10;
            pacman_map[pacman_y][pacman_x] = ' ';
        }
    }
    else if ((direction == 'a' || direction == 'A' || direction == LEFT) && pacman_map[pacman_y][pacman_x - 1] != '#') {
        pacman_x--;
        if (pacman_map[pacman_y][pacman_x] == '.') {
            score++;
            pacman_map[pacman_y][pacman_x] = ' ';
        }
        else if (pacman_map[pacman_y][pacman_x] == 'o') {
            activate_power_up();
            this->score = this->score + 10;
            pacman_map[pacman_y][pacman_x] = ' ';
        }
    }
    else if ((direction == 'd' || direction == 'D' || direction == RIGHT) && pacman_map[pacman_y][pacman_x + 1] != '#') {
        pacman_x++;
        if (pacman_map[pacman_y][pacman_x] == '.') {
            score++;
            pacman_map[pacman_y][pacman_x] = ' ';
        }
        else if (pacman_map[pacman_y][pacman_x] == 'o') {
            activate_power_up();
            this->score = this->score + 10;
            pacman_map[pacman_y][pacman_x] = ' ';
        }
    }
}

void Game::update_ghost_inky() {
    update_inky_chase(ghost_inky);
}
void Game::update_inky_chase(Ghost& ghost) {
    if (rand() % 2 == 0) { // Move every other frame
        int direction = rand() % 4;
        if (direction == 2 && pacman_map[ghost_inky.y][ghost_inky.x - 1] != '#') {
            ghost_inky.x--;
        }
        else if (direction == 3 && pacman_map[ghost_inky.y][ghost_inky.x + 1] != '#') {
            ghost_inky.x++;
        }
    }
    int direction_x = this->pacman_x - ghost.x;
    int direction_y = 20 - ghost.y;
    if (abs(direction_x) > abs(direction_y)) {
        if (direction_x > 0 && pacman_map[ghost.y][ghost.x + 1] != '#') {
            ghost.x++;
        }
        else if (direction_x < 0 && pacman_map[ghost.y][ghost.x - 1] != '#') {
            ghost.x--;
        }
        else if (direction_y > 0 && pacman_map[ghost.y + 1][ghost.x] != '#') {
            ghost.y++;
        }
        else if (direction_y < 0 && pacman_map[ghost.y - 1][ghost.x] != '#') {
            ghost.y--;
        }
    }
}
void Game::update_ghost_pinky() {
    update_pinky_chase(ghost_pinky);
}

void Game::update_pinky_chase(Ghost& ghost) {
    int direction = rand() % 4;
    if (direction == 0 && pacman_map[ghost.y - 1][ghost.x] != '#') {
        ghost.y--;
    }
    else if (direction == 1 && pacman_map[ghost.y + 1][ghost.x] != '#') {
        ghost.y++;
    }
    else if (direction == 2 && pacman_map[ghost.y][ghost.x - 1] != '#') {
        ghost.x--;
    }
    else if (direction == 3 && pacman_map[ghost.y][ghost.x + 1] != '#') {
        ghost.x++;
    }
    int direction_x = this->ghost_blinky.x - ghost.x;
    int direction_y = this->ghost_clyder.y - ghost.y;

    if (abs(direction_x) > abs(direction_y)) {
        if (direction_x > 0 && pacman_map[ghost.y][ghost.x + 1] != '#') {
            ghost.x++;
        }
        else if (direction_x < 0 && pacman_map[ghost.y][ghost.x - 1] != '#') {
            ghost.x--;
        }
        else if (direction_y > 0 && pacman_map[ghost.y + 1][ghost.x] != '#') {
            ghost.y++;
        }
        else if (direction_y < 0 && pacman_map[ghost.y - 1][ghost.x] != '#') {
            ghost.y--;
        }
    }
    else {
        if (direction_y > 0 && pacman_map[ghost.y + 1][ghost.x] != '#') {
            ghost.y++;
        }
        else if (direction_y < 0 && pacman_map[ghost.y - 1][ghost.x] != '#') {
            ghost.y--;
        }
        else if (direction_x > 0 && pacman_map[ghost.y][ghost.x + 1] != '#') {
            ghost.x++;
        }
        else if (direction_x < 0 && pacman_map[ghost.y][ghost.x - 1] != '#') {
            ghost.x--;
        }
    }
}

void Game::update_ghost_blinky() {
    update_blinky_chase(ghost_blinky);
}

void Game::update_blinky_chase(Ghost& ghost) {
    if (rand() % 3 == 0) { // for slow movement
        int direction = rand() % 4;
        if (direction == 0 && pacman_map[ghost.y - 1][ghost.x] != '#') {
            ghost.y--;
        }
        else if (direction == 1 && pacman_map[ghost.y + 1][ghost.x] != '#') {
            ghost.y++;
        }
        else if (direction == 2 && pacman_map[ghost.y][ghost.x - 1] != '#') {
            ghost.x--;
        }
        else if (direction == 3 && pacman_map[ghost.y][ghost.x + 1] != '#') {
            ghost.x++;
        }
    }

    int direction_x = this->ghost_clyder.x - ghost.x;
    int direction_y = this->pacman_y - ghost.y;

    if (abs(direction_x) > abs(direction_y)) {
        if (direction_x > 0 && pacman_map[ghost.y][ghost.x + 1] != '#') {
            ghost.x++;
        }
        else if (direction_x < 0 && pacman_map[ghost.y][ghost.x - 1] != '#') {
            ghost.x--;
        }
        else if (direction_y > 0 && pacman_map[ghost.y + 1][ghost.x] != '#') {
            ghost.y++;
        }
        else if (direction_y < 0 && pacman_map[ghost.y - 1][ghost.x] != '#') {
            ghost.y--;
        }
    }
}

void Game::update_ghost_clyde() {
    update_clyde_chase(ghost_clyder);
}

void Game::update_clyde_chase(Ghost& ghost) {
    int direction_x = this->pacman_x - ghost.x;
    int direction_y = this->pacman_y - ghost.y;
    if (abs(direction_y) >= abs(direction_x)) {
        if (direction_y > 0 && pacman_map[ghost.y + 1][ghost.x] != '#') {
            ghost.y++;
        }
        else if (direction_y < 0 && pacman_map[ghost.y - 1][ghost.x] != '#') {
            ghost.y--;
        }
        else if (direction_x > 0 && pacman_map[ghost.y][ghost.x + 1] != '#') {
            ghost.x++;
        }
        else if (direction_x < 0 && pacman_map[ghost.y][ghost.x - 1] != '#') {
            ghost.x--;
        }
    }
    else {
        if (direction_x > 0 && pacman_map[ghost.y][ghost.x + 1] != '#') {
            ghost.x++;
        }
        else if (direction_x < 0 && pacman_map[ghost.y][ghost.x - 1] != '#') {
            ghost.x--;
        }
        else if (direction_y > 0 && pacman_map[ghost.y + 1][ghost.x] != '#') {
            ghost.y++;
        }
        else if (direction_y < 0 && pacman_map[ghost.y - 1][ghost.x] != '#') {
            ghost.y--;
        }
    }
}
int Game::get_pacman_x() const {
    return this->pacman_x;
}
int Game::get_pacman_y() const {
    return this->pacman_y;
}
int Game::get_score() const {
    return this->score;
}
bool Game::get_poer_up_status()const {
    return this->power_up;
}
bool Game::check_collision()  {
    if (this->power_up) {
        if (pacman_x == ghost_inky.x && pacman_y == ghost_inky.y){
            reset_ghosts(ghost_inky);
            return false;
        }
        else if (pacman_x == ghost_pinky.x && pacman_y == ghost_pinky.y) {
            reset_ghosts(ghost_pinky);
            return false;
        }
        else if (pacman_x == ghost_blinky.x && pacman_y == ghost_blinky.y) {
            reset_ghosts(ghost_blinky);
            return false;
        }
        else if(pacman_x == ghost_clyder.x && pacman_y == ghost_clyder.y) {
            reset_ghosts(ghost_clyder);
            return false;
        }
    }
    else {
        if ((pacman_x == ghost_inky.x && pacman_y == ghost_inky.y)
            ||
            (pacman_x == ghost_pinky.x && pacman_y == ghost_pinky.y)
            ||
            (pacman_x == ghost_blinky.x && pacman_y == ghost_blinky.y)
            ||
            (pacman_x == ghost_clyder.x && pacman_y == ghost_clyder.y)) {
            return true;
        }
    }
    return false;
}

void Game::reset_ghosts(Ghost &ghost) {
    if (&ghost == &ghost_pinky) {
        ghost.x = 2;
        ghost.y = 1;
    }
    else if (&ghost == &ghost_blinky) {
        ghost.x = 2;
        ghost.y = 2;
    }
    else if (&ghost == &ghost_inky) {
        ghost.x = 1;
        ghost.y = 1;
    }
    else if (&ghost == &ghost_clyder) {
        ghost.x = 1;
        ghost.y = 2;
    }
}

Game::~Game() {

}
Player::Player(Game& game) :game(game) {

}
void Player::move() {
    if (_kbhit()) {
        char direction = _getch();
        if (direction == 'q' || direction == 'Q') {
            throw runtime_error("Quiting......");
        }
        game.update_position(direction);
    }
    game.update_power_up();
}

void Player::display() {
    game.print_map();
    if (game.get_poer_up_status()) {
        cout << RED << "POWER UP activate eat ghosts...." << RESET << endl;
    }
}

Player::~Player(){

}