#ifndef CHEESEBOARD_H
#define CHEESEBOARD_H

#include "board.h"

const double TIME_LIMIT = 60*5;

class CheeseBoard : public Board {
public:
    CheeseBoard(int n = 10, int m = 20, int cheeseHeight = 10, int lvl = 0, int points = 0);
    
    void clearRow();

    bool checkGameOver(double elapsed);
    bool isWon(double elapsed);
};

#endif