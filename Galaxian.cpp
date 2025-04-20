#include "Galaxian.h"

Galaxian::Galaxian(int difficulty) {
    game_over = false;
    score = 0;
    num_enemy_rows = difficulty;
}

void Galaxian::play() {
    setlocale(LC_ALL, ""); // Enable UTF-8 support for emojis.

    initscr();             // Initializes ncurses library.
    keypad(stdscr, TRUE);  // Enable keyboard input.
    noecho();              // Disable output of keypresses.
    curs_set(FALSE);       // Disable blinking cursor.

    initialize_entities();

    while(!game_over) {
        draw_game();
        capture_keystroke();
        usleep(DELAY);
    }

    endwin();
}

void Galaxian::initialize_entities() {
    // Player starts in the bottom center.
    // COLS and LINES are global variables from ncurses.
    Player.setX(COLS / 2);
    Player.setY(LINES - 2);

    const int WAVE_COL_SPACING = 3; // Each enemy is 3 characters apart (horizontally).
    const int WAVE_ROW_SPACING = 2; // Each enemy is 2 characters apart (vertically).

    // Not necessary, but these variables give room for a future upgrade, 
    // where one can adjust these variables and make the swarm move.
    int swarm_row_offset = 1; // Swarm starts below the first line.
    int swarm_col_offset = 0; // Swarm starts on the left.

    // Initialize enemy grid (pyramid shaped).
    for(int row_pos = 0; row_pos < num_enemy_rows; row_pos++) {
        std::vector<Entity> Wave;

        for(int col_pos = 0; col_pos < row_pos * 2 + 1; col_pos++) {
            // Calculates the horionztal offset for the pyramid row.
            int pyramid_offset = num_enemy_rows - row_pos - 1;

            // Constructs an enemy with given coordinates, then stores the enemy in the wave.
            Entity Enemy(
                    (col_pos + swarm_col_offset + pyramid_offset) * WAVE_COL_SPACING,
                    (row_pos + swarm_row_offset) * WAVE_ROW_SPACING
            );
            Wave.push_back(Enemy);
        }

        Waves.push_back(Wave); // Add a new row (wave).
    }

}

void Galaxian::draw_game() {
    // clear();

    mvprintw(0, 0, "Score: %d", score);

    // Draw player.
    mvprintw(Player.getY(), Player.getX(), "🤖");

    // Draw enemies.
    for(unsigned i = 0; i < Waves.size(); i++) {
        for(unsigned j = 0; j < Waves[i].size(); j++) {
            mvprintw(Waves[i][j].getY(), Waves[i][j].getX(), "👾");
        }
    }


    refresh();
}

void Galaxian::capture_keystroke() {
    int ch = getch();
    switch(ch) {
        case KEY_LEFT:
            if(Player.getX() > 0) Player.setX(Player.getX() - 1);
            break;
        case KEY_RIGHT:
            if(Player.getX() < COLS - 1) Player.setX(Player.getX() + 1);
            break;
        case ' ':
            // TODO: Bullets.
            break;
        case 'q':
            game_over = true;
            break;
    }
}
