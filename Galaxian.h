#include <locale.h>  // Used for UTF-8 support.
#include <ncurses.h> // Gives us a text based interface.
#include <unistd.h>  // Used for delaying the refresh rate (TODO: Consider using <chrono> instead)

#define DELAY 100000

class Entity {
    public:
        int getX() const {return x;}
        int getY() const {return y;};

        void setX(int newX) {x = newX;}
        void setY(int newY) {y = newY;}

    private:
        int x;
        int y;
};

class Galaxian {
    public:
        Galaxian();
        void play();

    private:
        void draw_game();

        Entity Player;
        int score;
};
