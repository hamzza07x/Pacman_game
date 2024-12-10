//ghost class for representing ghosts

class Ghost {
public:
    //x cordinate for ghosts
    int x;
    //y coordinate for ghosts
    int y;
  
};
//game class that is the class which has the game logic and data
class Game {
private:
    //pacman current x position
    int pacman_x;
    //pacman current y position
    int pacman_y;
    //pacman current score
    int score;
    //pacman cureent power up state
    bool power_up;
    //duration of power up timer
    int power_up_duration;
    //timer that tracks the remaining power up duration or initializes the timer
    int power_up_timer;
    //player lives
    int lives;
    //Inky ghost of class ghost
    Ghost ghost_inky;
    //Pinky ghost of class ghost
    Ghost ghost_pinky;
    //Blinky ghost of ghost class
    Ghost ghost_blinky;
    //Clyde ghost of ghost class
    Ghost ghost_clyder;
    //temporary map so that map reloads after each play
    char temp_map[20][40];
public:
    //default map grid for the game
    char pacman_map[30][40] = {
        "***************************************",
        "*o...................................o*",
        "*..*..*********...*********...****...o*",
        "*..*.....o*o.........o*o..............*",
        "*..*......*...........*............*..*",
        "*..*...............................*..*",
        "*..******....................*******..*",
        "*.....................................*",
        "*************...............***********",
        "*o...................................o*",
        "*.............***...***...............*",
        "*..*...*......*.......*........*..*...*",
        "*..*...*.......................*..*...*",
        "*..*...*......*.......*........*..*...*",
        "*..*...*......****.****....*...*..*...*",
        "*..*...*...................*...*..*...*",
        "*..*...*......*******......*...*..*...*",
        "*..*...*.........*.........*...*..*...*",
        "*.....................................*",
        "*.....................................*",
        "*..*..*********...*********...****...o*",
        "*..*.....o*o.........o*o..............*",
        "*..*......*...........*............*..*",
        "*..*...............................*..*",
        "*..******....................*******..*",
        "*.....................................*",
        "*************...............***********",
        "*o...................................o*",
        "***************************************"
    };
    //game constructor
    Game();
    //function of printing map grid
    void print_map() const;
    //updates pacman position according to direction input
    void update_position(char direction);
    //updates inky
    void update_ghost_inky();
    //updates pinky
    void update_ghost_pinky();
    //updates blinky
    void update_ghost_blinky();
    //updates clyde
    void update_ghost_clyde();
    //return the current x position of pacman 
    int get_pacman_x() const;
    //return current y position of pacman
    int get_pacman_y() const;
    //check for collision between pacman or wall "*"
    bool check_collision();
    //return current score
    int get_score() const;
    //return cureent lives remaining
    int get_lives()const;
    //updates power up if pacman encounters o
    void activate_power_up();
    //activates power up 
    void update_power_up();
    //returns current power up state of pacman
    bool get_poer_up_status()const;
    //resets all the ghosts to their initial positions as were initialized in the construc of game
    void reset_ghosts(Ghost& ghost);
    //chase behaviour for clyde
    void update_clyde_chase(Ghost& ghost);
    //chase behaviour for blinky
    void update_blinky_chase(Ghost& ghost);
    //chase behaviour for pinky
    void update_pinky_chase(Ghost& ghost);
    //chase behaviour for inky
    void update_inky_chase(Ghost&ghost);
    //restores the map from the temporary map so that map reloads after each play
    void save_map();
    //reset the map to the original map grid from temporary map
    void restore_map();
    //destructor that destroys game object
    ~Game();
};
//player class that handles player instructions and moments
class Player {
private:
    //refrence to game object to start game 
    Game& game;
    //direction for pacman
    char direction;
public:
    //player contructor
    Player(Game& game);
    //executes player movements in the game
    void move();
    //displays the map grid and power up state if activated
    void display();
    //sets the direction to some random initial direction as i have set to dir first user input
    void set_direction(char dir);
    //returns the current direction input of the player
    char get_direction()const;
    //player destructor
    ~Player();
};