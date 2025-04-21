#include <string>
#include <vector>
#include "Entity.h"

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
        void update_game(); // TODO: Implement this function.

        // Helper for initialize_entities().
        std::vector<std::vector<Entity>> build_swarm(std::string shape);

        // Helpers for draw_game().
        void display_scoreboard();
        void display_player();
        void display_swarm();
        void display_bullets();
};
