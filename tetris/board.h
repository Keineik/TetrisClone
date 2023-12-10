#ifndef BOARD_H
#define BOARD_H
#include "block.h"

class Board{
private:
    vector<vector<int>> board;
    long long int score;
    Block currentBlock;
    int x;
    int y;
public:
    void userInput();
    void copyCurrentBoard();
    void movePieceDown();
    void run();

    void clearScreen();
    void initDrawBoard();
    void redrawBoard();

    void getNewPiece();
    void movePieceLR(int _x, int _y);

    bool checkCollision(int _x, int _y);
    bool checkGameOver();
    void clearRow();


};

#endif