#include <iostream>
#include "Galaxian.h"

int main() {
    
    int difficulty;
    std::cout << "What difficulty do you want (1 - 5)? ";
    std::cin >> difficulty;
    Galaxian Round(difficulty);

    Round.play();

    int final_score = Round.getScore();
    std::cout << "Game over!" << std::endl;
    std::cout << "Final Score: " << final_score << std::endl;
}
