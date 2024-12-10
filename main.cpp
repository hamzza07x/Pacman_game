//required header files
#include <iostream>
#include <windows.h> 
#include <stdexcept>
#include <fstream>
#include "game.h"
//color macros for printing on console
#define RED "\033[31m"
#define RESET "\033[0m"
using namespace std;
//displays pacman intro graphics
void display_pacmana_intro() {
    cout << RED;
    cout << "  PPPP    AAAAA   CCCCC  M     M    AAAAA   N     N " << endl;
    cout << "  P   P   A   A   C      MM   MM   A   A   NN    N " << endl;
    cout << "  PPPP    AAAAA   C      M M M M   AAAAA   N N   N " << endl;
    cout << "  P       A   A   C      M  M  M   A   A   N  N  N " << endl;
    cout << "  P       A   A   CCCCC  M     M   A   A   N   N N " << endl;
    cout << RESET;
}
//displays the control instructions for the game
void display_controls() {
    cout << "Controls: " << endl;
    cout << "W or UP arrow key: Move up" << endl;
    cout << "S or DOWN arrow key: Move down" << endl;
    cout << "A or LEFT arrow key: Move left" << endl;
    cout << "D or RIGHT arrow key: Move right" << endl;
    cout << "Q or to quit" << endl;
    cout << "Press Enter to return to main menu" << endl;
    cin.ignore();
}
//displays pacman game details
void about_pacman() {
    cout << "==================================================<<" << endl;
    cout << "This is a pacman clone" << endl;
    cout << "Designed by: " << endl;
    cout << "Muhammad Hamza " << endl;
    cout << "        &&        " << endl;
    cout << "Rana Zain" << endl;
    cout << "=============================" << endl;
    cout << "Press Enter to return to menu" << endl;
}
//loads the highest score form a file if it exists
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
            new_score_file << 0; 
            new_score_file.close();
        }
    }
    return score;//returns the loaded score
}

//saves the highest score to a file if exists else creates one and then saves
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
//main driving function for the whole system
int main() {
    int user_choice;
    int highest_score = load_highest_score();  

    try {
        do {
            system("cls");//clear the sscreen
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
                cin.clear();//clears if any errors
                cin.ignore();
                cout << "Invalid input" << endl;
                throw exception("Invalid choice");
                continue;//skips to the end of main
            }
            //play choice
            if (user_choice == 1) {
                Game game;//game object
                Player player(game);//player object
                system("cls");
                //loop running if the user choice is 1 and input direction is not q
                while (player.get_direction() != 'q') {
                    game.save_map();
                    player.display();
                    player.move();
                    game.update_ghost_blinky();
                    game.update_ghost_clyde();
                    game.update_ghost_inky();
                    game.update_ghost_pinky();
                    game.update_power_up();
                    Sleep(150);//delay of 100 milisecond for next frame
                    //checks player collision
                    if (game.check_collision()) {
                        cout << "......GAME OVER...." << endl;
                        cout << "Your Score: " << game.get_score() << endl;
                        if (game.get_score() > highest_score) {
                            //storing the highesdt score and comparing with previous one
                            highest_score = game.get_score();
                            save_highest_score(highest_score);  
                        }
                        cout << "Press Enter to return to main menu" << endl;
                        cin.ignore();
                        game.save_map();
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
                system("cls");
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
    catch (const exception& e) {//exception thrown
        cout << "Game exited unexpectedly: " << e.what() << endl;
    }
    cin.get();
    return 0;
}
