#include <string>
#include <vector>

#define MILLISECONDS_PER_FRAME 50

// These function prototypes are implemented inline.
class Entity {
    public:
        Entity() {
            setX(0);
            setY(0);
            setSymbol(".");
        }

        Entity(int newX, int newY, std::string newSymbol) {
            setX(newX);
            setY(newY);
            setSymbol(newSymbol);
        }

        int getX() const {return x;}
        int getY() const {return y;}
        std::string getSymbol() const {return symbol;}

        void setX(int newX) {x = newX;}
        void setY(int newY) {y = newY;}
        void setSymbol(std::string newSymbol) {symbol = newSymbol;}

        void moveUp() {y--;}
        void moveDown() {y++;}

        void moveLeft() {x--;}
        void moveRight() {x++;}

    private:
        int x;
        int y;
        std::string symbol;
};

// These function prototypes are implemented in the Galaxian.cpp file.
class Galaxian {
    public:
        Galaxian(int difficulty);
        void play();
        int getScore() const;

    private:
        int num_enemy_rows;
        int score;
        bool game_over;

        Entity Player;
        std::vector<std::vector<Entity>> Waves;
        std::vector<Entity> Bullets;

        void initialize_entities();
        void draw_game();
        void capture_keystroke();
        void update_game();

        // Helper functions for draw_game().
        void display_scoreboard();
        void display_player();
        void display_swarm();
        void display_bullets();
};
