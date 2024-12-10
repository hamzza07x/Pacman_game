#include <iostream>
#include <windows.h> 
#include <stdexcept>
#include <fstream>
#include "game.h"
#define RED "\033[31m"
#define RESET "\033[0m"
using namespace std;

void display_pacmana_intro() {
    cout << RED;
    cout << "  PPPP    AAAAA   CCCCC  M     M    AAAAA   N     N " << endl;
    cout << "  P   P   A   A   C      MM   MM   A   A   NN    N " << endl;
    cout << "  PPPP    AAAAA   C      M M M M   AAAAA   N N   N " << endl;
    cout << "  P       A   A   C      M  M  M   A   A   N  N  N " << endl;
    cout << "  P       A   A   CCCCC  M     M   A   A   N   N N " << endl;
    cout << RESET;
}

void display_controls() {
    cout << "Controls: " << endl;
    cout << "W or UP arrow key: Move up" << endl;
    cout << "S or DOWN arrow key: Move down" << endl;
    cout << "A or LEFT arrow key: Move left" << endl;
    cout << "D or RIGHT arrow key: Move right" << endl;
    cout << "Press Enter to return to main menu" << endl;
    cin.ignore();
}

void about_pacman() {
    cout << "===== About Pac-Man =====" << endl;
    cout << "Pac-Man is an arcade game developed by Namco and first released in 1980." << endl;
    cout << "The player controls Pac-Man, navigating a maze while eating pellets and avoiding ghosts." << endl;
    cout << "Key features of the game include:" << endl;
    cout << "- Four ghosts: Blinky, Pinky, Inky, and Clyde, each with unique behavior." << endl;
    cout << "- Power pellets that allow Pac-Man to temporarily eat the ghosts." << endl;
    cout << "- A scoring system based on eating pellets, ghosts, and bonus items." << endl;
    cout << "Pac-Man is widely regarded as one of the most iconic video games of all time." << endl;
    cout << "==========================" << endl;
    cout << "Press Enter to return to the main menu." << endl;
    cout << "==================================================<<" << endl;
    cout << "This is a pacman clone" << endl;
    cout << "Designed by: " << endl;
    cout << "Muhammad Hamza " << endl;
    cout << "        &&        " << endl;
    cout << "Rana Zain" << endl;
    cout << "=============================" << endl;
    cout << "Press Enter to return to menu" << endl;
}

// Function to load the highest score from a file
int load_highest_score() {
    int score = 0;
    ifstream score_file("score.txt");
    if (score_file.is_open()) {
        score_file >> score;
        score_file.close();
    }
    else {
        ofstream new_score_file("score.txt");
        if (new_score_file.is_open()) {
            new_score_file << 0; // Initialize score if file doesn't exist
            new_score_file.close();
        }
    }
    return score;
}

// Function to save the highest score to a file
void save_highest_score(int score) {
    ofstream score_file("score.txt");
    if (score_file.is_open()) {
        score_file << score;
        score_file.close();
    }
    else {
        cerr << "Failed to save the score." << endl;
    }
}

int main() {
    int user_choice;
    int highest_score = load_highest_score();  // Load highest score at the start

    try {
        do {
            system("cls");
            display_pacmana_intro();
            cout << endl << endl;
            cout << "====Pacman Game Menu====" << endl;
            cout << "1. Play" << endl;
            cout << "2. Highest Score" << endl;
            cout << "3. Controls" << endl;
            cout << "4. About" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> user_choice;
            cin.ignore();
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                cout << "Invalid input" << endl;
                throw exception("Invalid choice");
                continue;
            }

            if (user_choice == 1) {
                Game game;
                Player player(game);
                system("cls");
                while (true) {
                    player.display();
                    player.move();
                    game.update_ghost_blinky();
                    game.update_ghost_clyde();
                    game.update_ghost_inky();
                    game.update_ghost_pinky();
                    game.update_power_up();
                    Sleep(150);

                    if (game.check_collision()) {
                        cout << "......GAME OVER...." << endl;
                        cout << "Your Score: " << game.get_score() << endl;
                        if (game.get_score() > highest_score) {
                            highest_score = game.get_score();
                            save_highest_score(highest_score);  // Save new highest score
                        }
                        cout << "Press Enter to return to main menu" << endl;
                        cin.ignore();
                        break;
                    }
                }
            }
            else if (user_choice == 2) {
                system("cls");
                cout << "Highest Score: " << highest_score << endl;
                cout << "Press Enter to return to main menu" << endl;
                cin.ignore();
            }
            else if (user_choice == 3) {
                system("cls");
                display_controls();
                cin.ignore();
            }
            else if (user_choice == 4) {
                about_pacman();
                cin.ignore();
                cin.get();
            }
            else if (user_choice == 5) {
                cout << "Exiting game............." << endl;
                cout << "Good Bye" << endl;
                cin.ignore();
            }
            else {
                cout << "Invalid choice " << endl;
                cout << "Try again" << endl;
                cin.ignore();
            }
        } while (user_choice != 5);
    }
    catch (const exception& e) {
        cout << "Game exited unexpectedly: " << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
        cin.ignore();
    }
    cin.get();
    return 0;
}
