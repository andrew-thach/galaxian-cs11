#include <locale.h>  // Used for UTF-8 support.
#include <ncurses.h> // Gives us a text based interface.
#include <unistd.h>  // Used for delaying the refresh rate (TODO: Consider using <chrono> instead)
#include <vector>

#define DELAY 10000

// These function prototypes are implemented inline.
class Entity {
    public:
        Entity() {x = 0; y = 0;}
        Entity(int newX, int newY) {x = newX; y = newY;}

        int getX() const {return x;}
        int getY() const {return y;}

        void setX(int newX) {x = newX;}
        void setY(int newY) {y = newY;}

    private:
        int x;
        int y;
};

// These function prototypes are implemented in the Galaxian.cpp file.
class Galaxian {
    public:
        Galaxian(int difficulty);
        void play();

    private:
        bool game_over;
        int score;
        int num_enemy_rows;

        Entity Player;
        std::vector<std::vector<Entity>> Waves;

        std::vector<Entity> Bullets;

        void initialize_entities();
        void draw_game();
        void capture_keystroke();
};
