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

    // Sets the frames per second.
    timeout(MILLISECONDS_PER_FRAME);

    initialize_entities();

    while(!game_over) {
        draw_game();
        capture_keystroke();
        update_game();
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

    // Swarm starts on the center top of the terminal. 
    int swarm_row_offset = 2;
    int swarm_col_offset = COLS / 2  - (num_enemy_rows - 1) * WAVE_COL_SPACING;

    // Initialize enemy grid (pyramid shaped).
    for(int row_pos = 0; row_pos < num_enemy_rows; ++row_pos) {
        std::vector<Entity> Wave;

        for(int col_pos = 0; col_pos < row_pos * 2 + 1; ++col_pos) {
            // Calculates the horionztal offset for the pyramid row.
            int pyramid_offset = num_enemy_rows - row_pos - 1;

            // Constructs an enemy with given coordinates, then stores the enemy in the wave.
            Entity Enemy(
                    (col_pos + pyramid_offset) * WAVE_COL_SPACING + swarm_col_offset,
                    row_pos * WAVE_ROW_SPACING + swarm_row_offset
            );
            Wave.push_back(Enemy);
        }

        Waves.push_back(Wave); // Add a new row (wave).
    }

}

void Galaxian::draw_game() {
    clear();

    mvprintw(0, 0, "Score: %d", score);

    // Draw player.
    mvprintw(Player.getY(), Player.getX(), "^");
    // This line is temporarly disabled because an emoji has a width > 1, which messes with the alignment.
    // mvprintw(Player.getY(), Player.getX(), "🤖"); 

    // Draw enemies.
    for(unsigned i = 0; i < Waves.size(); ++i) {
        for(unsigned j = 0; j < Waves[i].size(); ++j) {
            mvprintw(Waves[i][j].getY(), Waves[i][j].getX(), "M");
            // This line is temporarily disabled because an emoji has a width > 1, which messes with the alignment.
            // mvprintw(Waves[i][j].getY(), Waves[i][j].getX(), "👾"); 
        }
    }

    // Draw bullets.
    for (unsigned i = 0; i < Bullets.size(); ++i) {
        mvprintw(Bullets[i].getY(), Bullets[i].getX(), "|");
    }

    refresh();
}

void Galaxian::capture_keystroke() {
    // FIXME: Declaring an object in a case gives a cross-initialization error.
    // int ch = getch();
    // switch(ch) {
    //     case KEY_LEFT:
    //         if(Player.getX() > 0)
    //             Player.moveLeft();
    //         break;
    //     case KEY_RIGHT:
    //         if(Player.getX() < COLS - 1)
    //             Player.moveRight();
    //         break;
    //     case ' ':
    //         // TODO: Create a bullet at Player's current position and store it.
    //         break;
    //     case 'q':
    //         game_over = true;
    //         break;
    // }
    int ch = getch();
    if(ch == KEY_LEFT) {
        if(Player.getX() > 0)
            Player.moveLeft();
    }
    else if(ch == KEY_RIGHT) {
        if(Player.getX() < COLS - 1)
            Player.moveRight();
    }
    else if(ch == ' ') {
        // Create a bullet at Player's current position and store it.
        Entity Projectile(Player.getX(), Player.getY() - 1);
        Bullets.push_back(Projectile);
    }
    else if(ch == 'q') {
        game_over = true;
    }
}

void Galaxian::update_game() {
    for (unsigned i = 0; i < Bullets.size(); ++i) {
        Bullets[i].moveUp();
    }
}
