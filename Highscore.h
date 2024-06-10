#pragma once
#include <string>

class Highscore {
public:
    Highscore(const std::string& filename);
    int getHighscore();
    void updateHighscore(int score);

private:
    std::string filename;
    int highscore;
};
