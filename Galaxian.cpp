#include "Galaxian.h"

Galaxian::Galaxian() {
    score = 0;
}

void Galaxian::play() {
    setlocale(LC_ALL, ""); // Enable UTF-8 support for emojis.

    initscr();             // Initializes ncurses library.
    keypad(stdscr, TRUE);  // Enable keyboard input.
    noecho();              // Disable output of keypresses.
    curs_set(FALSE);       // Disable blinking cursor.

    // Player starts in the bottom center.
    // COLS and LINES are global variables from ncurses.
    Player.setX(COLS / 2);
    Player.setY(LINES - 2);

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
    mvprintw(Player.getY(), Player.getX(), "🤖");


    refresh();
}
