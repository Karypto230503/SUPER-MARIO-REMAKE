#include "Highscore.h"
#include <fstream>
#include <iostream>

Highscore::Highscore(const std::string& filename) : filename(filename), highscore(0) {}

int Highscore::getHighscore() {
    std::ifstream file(filename);
    highscore = 0;
    if (file.is_open()) {
        if (!(file >> highscore)) {
            std::cerr << "Failed to read highscore from file." << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Failed to open highscore file for reading." << std::endl;
    }
    return highscore;
}

void Highscore::updateHighscore(int score) {
    int currentHighscore = getHighscore();
    if (score > currentHighscore) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << score;
            file.close();
            std::cout << "Highscore updated to " << score << std::endl;
        }
        else {
            std::cerr << "Failed to open highscore file for writing." << std::endl;
        }
    }
    else {
        std::cout << "Current score (" << score << ") is not higher than highscore (" << currentHighscore << ")" << std::endl;
    }
}
