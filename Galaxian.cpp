#include <locale.h>  // Allows UTF-8 Support for emojis.
#include <ncurses.h> // Gives us a text based interface.
#include "Galaxian.h"

#define MILLISECONDS_PER_FRAME 50

// Constructs a game with specified difficulty.
Galaxian::Galaxian(int difficulty) {
    // Default to 3 if out of bounds.
    if (difficulty < 0 || difficulty > 5) {
        difficulty = 3;
    }
    num_enemy_rows = difficulty;

    score = 0;
    game_over = false;
}

// Starts a single round of the game.
void Galaxian::play() {
    // Enable UTF-8 support for emojis.
    // Not currently used, since UTF-8 characters are wider, 
    // and messes with the alignment/hitboxes.
    setlocale(LC_ALL, "");

    initscr();             // Initializes ncurses library.
    keypad(stdscr, TRUE);  // Enable keyboard input.
    noecho();              // Disable output of keypresses.
    curs_set(FALSE);       // Disable blinking cursor.

    // Sets the frames per second, and also allows non-blocking input.
    // Comment this out if you want each frame to update after a keystroke.
    timeout(MILLISECONDS_PER_FRAME);

    initialize_entities();

    while(!game_over) {
        draw_game();
        capture_keystroke();
        update_game();
    }

    endwin();
}

int Galaxian::getScore() const {
    return score;
}

void Galaxian::initialize_entities() {
    // Player starts in the bottom center. COLS and LINES are global variables from ncurses.
    Player = Entity(COLS / 2, LINES - 2, "^");

    Waves = build_swarm("pyramid");
}

void Galaxian::draw_game() {
    clear(); // Ncurses function: clears the frame so the previous frame doesn't overlap.

    // Prepare frame before outputting it.
    buffer_scoreboard();
    buffer_player();
    buffer_swarm();
    buffer_bullets();

    refresh(); // Ncurses function: Ouptut the buffered frame to the terminal window.
}

void Galaxian::capture_keystroke() {
    int ch = getch();
    if(ch == KEY_LEFT) {
        Player.moveLeft();
    }
    else if(ch == KEY_RIGHT) {
        Player.moveRight();
    }
    else if(ch == ' ') {
        // Create a bullet above Player's current position and store it.
        Entity Projectile(Player.getX(), Player.getY() - 1, "|");
        Bullets.push_back(Projectile);
    }
    else if(ch == 'q') {
        game_over = true;
    }
}

// TODO: The goal of this function is to keep the class attributes updated.
// This will allow the display functions to correctly show the updated frame.
void Galaxian::update_game() {
    for (unsigned i = 0; i < Bullets.size(); ++i) {
        Bullets[i].moveUp();
    }

    // TODO: Find a way to update the the relevant class attributes.
    //
    // For examples:
    //     - if a bullet has the same coordinates as an enemy,
    //           remove the bullet from the vector,
    //           remove the enemy from the 2D vector,
    //           and update the score.
    //     - if there are no more enemies,
    //           update the boolean "game_over", which should terminate the game on the next frame.
}

////////////////////////////////////////////////
// Helper functions for initialize_entities() //
////////////////////////////////////////////////
std::vector<std::vector<Entity>> Galaxian::build_swarm(std::string shape) {
    std::vector<std::vector<Entity>> Formation;

    const int WAVE_COL_SPACING = 3; // Each enemy is 3 characters apart (horizontally).
    const int WAVE_ROW_SPACING = 2; // Each enemy is 2 characters apart (vertically).

    // Swarm starts on the center top of the terminal. 
    int swarm_row_offset = 2;
    int swarm_col_offset = COLS / 2  - (num_enemy_rows - 1) * WAVE_COL_SPACING;

    // Shape algorithm inspired from ZyBooks, 4.14.5.
    if (shape == "pyramid") {
        for(int row_pos = 0; row_pos < num_enemy_rows; ++row_pos) {
            std::vector<Entity> Wave;

            for(int col_pos = 0; col_pos < row_pos * 2 + 1; ++col_pos) {
                // Calculates the horionztal offset for the pyramid row.
                int pyramid_offset = num_enemy_rows - row_pos - 1;

                // Constructs an enemy with given coordinates, then stores the enemy in the wave.
                Entity Enemy(
                        (col_pos + pyramid_offset) * WAVE_COL_SPACING + swarm_col_offset,
                        row_pos * WAVE_ROW_SPACING + swarm_row_offset,
                        "M"
                );
                Wave.push_back(Enemy);
            }

            Formation.push_back(Wave); // Add a new row (wave).
        }
    }
    return Formation;
}

//////////////////////////////////////
// Helper functions for draw_game() //
//////////////////////////////////////

void Galaxian::buffer_scoreboard() {
    mvprintw(0, 0, "Score: %d", score);
    mvprintw(1, 0, "Waves: %ld", Waves.size());
}

void Galaxian::buffer_player() {
    mvprintw(Player.getY(), Player.getX(), "%s", Player.getSymbol().c_str());
}

void Galaxian::buffer_swarm() {
    for(unsigned i = 0; i < Waves.size(); ++i) {
        for(unsigned j = 0; j < Waves[i].size(); ++j) {
            mvprintw(Waves[i][j].getY(), Waves[i][j].getX(), "%s", Waves[i][j].getSymbol().c_str());
        }
    }
}

void Galaxian::buffer_bullets() {
    for (unsigned i = 0; i < Bullets.size(); ++i) {
        mvprintw(Bullets[i].getY(), Bullets[i].getX(), "%s", Bullets[i].getSymbol().c_str());
    }
}
