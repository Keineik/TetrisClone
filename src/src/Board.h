#pragma once
#include "headers.h"
#include "Block.h"

using namespace std;

class Board {
private:
    vector<vector<bool>> board;
    long long score;
    Block curBlock;
    pair<int, int> curBlockCoord;

public:
    Board(int n = 10, int m = 20);

    const vector<vector<bool>>& getBoard() { return board; }
    const vector<vector<bool>>& getCurBlock() { return curBlock.getBlock(); }
    long long getScore() { return score; }
    pair<int, int> getCurBlockCoord() { return curBlockCoord; }

    void clearRow();
    void setBlockToBoard();

    void getNewBlock();
    void moveBlock(char command);
    bool checkCollision(pair<int, int> coord);
    bool checkGameOver();
};