#ifndef BOARD_H
#define BOARD_H
#include "Block.cpp"

class Board {
private:
    static const int dropFrames[15];

    double level;
    long long score;

    vector<vector<bool>> board;

    Block curBlock;
    pair<int, int> curBlockCoord;

public:
    Board(int n = 10, int m = 20);

    int getLevel() { return int(level); }
    const vector<vector<bool>>& getBoard() { return board; }
    const vector<vector<bool>>& getCurBlock() { return curBlock.getBlock(); }
    long long getScore() { return score; }
    pair<int, int> getCurBlockCoord() { return curBlockCoord; }

    double getDropSpeed();

    void updateScore(int rowsDeleted);

    void clearRow();
    void getNewBlock();
    void setBlockToBoard();
    void moveBlock(char command);
    void updateBoard();
    
    bool checkCollision(pair<int, int> coord);
    bool checkGameOver();
};

#endif