#include "Board.h"

Board::Board(int n, int m) {
    board.resize(m, vector<char>(n, '.'));
    level = 0;
    score = 0;
}

const int Board::dropFrames[15] = {48, 43, 38, 33, 28, 23, 18, 13, 8, 6, 5, 4, 3, 2, 1};
double Board::getDropSpeed() {
    int spdLevel;
    if (level <= 9) spdLevel = level;
    else if (level <= 12) spdLevel = 10;
    else if (level <= 15) spdLevel = 11;
    else if (level <= 18) spdLevel = 12;
    else if (level <= 28) spdLevel = 13;
    else spdLevel = 14;

    return double(dropFrames[spdLevel])/60.0;
}

void Board::updateScore(int rowsDeleted) {
    int pointCoef[5] = {0, 40, 100, 300, 1200};
    score += pointCoef[rowsDeleted]*(int(level) + 1);
    if (rowsDeleted == 0) score += 1; // manually move the block down gain 1 point
}

void Board::getNewBlock(bool startFlag) {
    if (startFlag) {
        curBlock = Block();
        blockStatistic[curBlock.getBlockName()]++;
        nextBlock = Block();
    }
    else {
        curBlock = nextBlock;
        blockStatistic[curBlock.getBlockName()]++;
        nextBlock = Block();
    }
    curBlockCoord = {-1, (board[0].size() - curBlock.getSize())/2};
}

bool Board::checkCollision(pair<int, int> coord){
    int n = curBlock.getSize();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (curBlock[i][j] == 0) continue;

            // check board borders collision
            if (j + coord.second < 0 || j + coord.second >= BOARD_WIDTH || i + coord.first >= BOARD_HEIGHT) 
                return true;

            // check occupied tiles collision
            if (board[i + coord.first][j + coord.second] != '.') 
                return true;
        }
    }
    return false;
}

bool Board::checkGameOver(){
    if (curBlockCoord.first == -1 && checkCollision(curBlockCoord))
        return true;
    for (int j = 0; j < BOARD_WIDTH; j++) {
        int count = 0;
        for (int i = 0; i < BOARD_HEIGHT; i++)
            if (board[i][j] != '.') count++;
        if (count == BOARD_HEIGHT) return true;
    }
    return false;
}

void Board::clearRow(){
    int n = BOARD_HEIGHT - 1;
    vector<char> blankRow(BOARD_WIDTH, '.');

    int rowsDeleted = 0;
    for (int i = n; i >= 0; i--) {
        int count = 0;
        for (int j = 0; j < BOARD_WIDTH; j++)
            if (board[i][j] != '.') count++;

        if (count == BOARD_WIDTH) {
            rowsDeleted++;
            for (int j = i; j >= 1; j--){
                board[j] = board[j - 1];
                board[0] = blankRow;
            }
            i++;
        }
    }
    updateScore(rowsDeleted);
    level += 0.1*rowsDeleted;
}

void Board::setBlockToBoard(){
    int n = curBlock.getSize();
    char name = curBlock.getBlockName();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (curBlock[i][j])
                board[i + curBlockCoord.first][j + curBlockCoord.second] = name;
}

void Board::moveBlock(char command) {
    switch(command) {
        case 'd':
            if (!checkCollision({curBlockCoord.first, curBlockCoord.second + 1})){
                curBlockCoord.second++;
            }
            break;
        case 'a':
            if (!checkCollision({curBlockCoord.first, curBlockCoord.second - 1})){
                curBlockCoord.second--;
            }
            break;
        case 's':
            if (!checkCollision({curBlockCoord.first + 1, curBlockCoord.second})){
                curBlockCoord.first++;
                updateScore(0);
            }
            break;
        case 'j':
            curBlock.leftRotate();
            if(checkCollision({curBlockCoord.first, curBlockCoord.second}))
                curBlock.rightRotate();
            break;
        case 'k':
            curBlock.rightRotate();
            if(checkCollision({curBlockCoord.first, curBlockCoord.second}))
                curBlock.leftRotate();
            break;
        case ' ':
            while(!checkCollision({curBlockCoord.first + 1, curBlockCoord.second})){
                curBlockCoord.first++;
                updateScore(0);
            }
            updateBoard();
    }
}

void Board::updateBoard(){
    if (!checkCollision({curBlockCoord.first + 1, curBlockCoord.second})){
        curBlockCoord.first++;
    }
    else{
        setBlockToBoard();
        clearRow();
        getNewBlock(false);
    }
}
