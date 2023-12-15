#ifndef CHEESEBOARD_H
#define CHEESEBOARD_H

#include "board.h"

const double TIME_LIMIT = 120;

class CheeseBoard : public Board {
protected:
    chrono::_V2::system_clock::time_point timerStart;
public:
    CheeseBoard(int n = 10, int m = 20, int cheeseHeight = 10, int lvl = 0);

    auto getStartTime() { return timerStart; }
    
    void clearRow();

    bool checkGameOver();
    bool isWon();
};

#endif