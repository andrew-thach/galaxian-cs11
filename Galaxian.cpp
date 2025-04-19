#include "Galaxian.h"

Galaxian::Galaxian() {
    score = 0;
}

void Galaxian::play() {
    initscr();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(FALSE);

    while(1) {
        draw_game();
        usleep(DELAY);
    }

    endwin();
}

void Galaxian::draw_game() {
    // clear();

    mvprintw(0, 0, "Score: %d", score);
    // Draw player
    mvprintw(LINES - 2, COLS / 2, "O");

    refresh();
}
