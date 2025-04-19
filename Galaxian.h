#include <ncurses.h>
#include <unistd.h>

#define DELAY 100000

class Galaxian {
    public:
        Galaxian();
        void play();
    private:
        void draw_game();
        int score;
};
