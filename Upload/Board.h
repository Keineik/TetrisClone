#ifndef BOARD_H
#define BOARD_H
#include "Block.cpp"

class Board {
protected:
    static const int dropFrames[15];
    map<char, int> statistics;
    
    double level;
    long long score;

    vector<vector<char>> board;
    Block curBlock;
    pair<int, int> curBlockCoord;
    Block nextBlock;

public:
    Board(int n = 10, int m = 20);
    ~Board();

    int getLevel() const { return int(level); }
    const vector<vector<char>>& getBoard() { return board; }
    Block& getCurBlock() { return curBlock; } // Needt to change to Block&
    Block& getNextBlock() { return nextBlock; }
    long long getScore() { return score; }
    pair<int, int> getCurBlockCoord() { return curBlockCoord; }
    map<char, int>& getStatistics() { return statistics; }

    double getDropSpeed();

    void updateScore(int rowsDeleted);

    virtual void clearRow();
    void getNewBlock(bool startFlag);
    void setBlockToBoard();
    void moveBlock(char command);
    void updateBoard();
    
    bool checkCollision(pair<int, int> coord);
    virtual bool checkGameOver(double elapsed = 0);
    virtual bool isWon(double elapsed = 0) {return false;}
};

#endif