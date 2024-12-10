struct Ghost {
    int x;
    int y;
};
class Game {
private:
    int pacman_x;
    int pacman_y;
    int score;
    bool power_up;
    int power_up_duration;
    int power_up_timer;
    Ghost ghost_inky;
    Ghost ghost_pinky;
    Ghost ghost_blinky;
    Ghost ghost_clyder;
public:
    Game();
    void print_map() const;
    void update_position(char direction);
    void update_ghost_inky();
    void update_ghost_pinky();
    void update_ghost_blinky();
    void update_ghost_clyde();
    int get_pacman_x() const;
    int get_pacman_y() const;
    bool check_collision();
    int get_score() const;
    void activate_power_up();
    void update_power_up();
    bool get_poer_up_status()const;
    void reset_ghosts(Ghost &ghost);
    void update_clyde_chase(Ghost& ghost);
    void update_blinky_chase(Ghost& ghost);
    void update_pinky_chase(Ghost& ghost);
    void update_inky_chase(Ghost&ghost);
    ~Game();
};
class Player {
private:
    Game& game;
public:
    Player(Game& game);
    void move();
    void display();
    ~Player();
};