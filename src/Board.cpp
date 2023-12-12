#include "Board.h"

Board::Board(int n, int m) { 
    board.resize(m, vector<bool>(n, 0));
    score = 0;
}

void Board::getNewBlock() {
    curBlock = Block();
    curBlockCoord = {0, (board[0].size() - curBlock.getSize())/2};
}

bool Board::checkCollision(pair<int, int> coord){
    int n = curBlock.getSize();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (curBlock[i][j] == 0) continue;

            // check board borders collision
            if (j + coord.y < 0 || j + coord.y >= BOARD_WIDTH || i + coord.x >= BOARD_HEIGHT) 
                return true;

            // check occupied tiles collision
            if (board[i + coord.x][j + coord.y]) 
                return true;
        }
    }
    return false;
}

bool Board::checkGameOver(){
    if (curBlockCoord.x == 0 && checkCollision(curBlockCoord))
        return true;
    for (int j = 0; j < BOARD_WIDTH; j++) {
        int count = 0;
        for (int i = 0; i < BOARD_HEIGHT; i++)
            if (board[i][j]) count++;
        if (count == BOARD_HEIGHT) return true;
    }
    return false;
}

void Board::clearRow(){
    int n = BOARD_HEIGHT - 1;
    vector<bool> blankRow(BOARD_WIDTH, 0);

    for (int i = n; i >= 0; i--) {
        int count = 0;
        for (int j = 0; j < BOARD_WIDTH; j++)
            if (board[i][j]) count++;

        if (count == BOARD_WIDTH) {
            score++;
            for (int j = i; j >= 1; j--){
                board[j] = board[j - 1];
                board[0] = blankRow;
            }
            i++;
        }
    }
}

void Board::setBlockToBoard(){
    int n = curBlock.getSize();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (curBlock[i][j])
                board[i + curBlockCoord.x][j + curBlockCoord.y] = curBlock[i][j];
}

void Board::moveBlock(char command) {
    switch(command){
        case 'd':
            if (!checkCollision({curBlockCoord.x, curBlockCoord.y + 1})){
                curBlockCoord.y++;
            }
            break;
        case 'a':
            if (!checkCollision({curBlockCoord.x, curBlockCoord.y - 1})){
                curBlockCoord.y--;
            }
            break;
        case 's':
            if (!checkCollision({curBlockCoord.x + 1, curBlockCoord.y})){
                curBlockCoord.x++;
            }
            break;
        case 'j':
            curBlock.leftRotate();
            if(checkCollision({curBlockCoord.x, curBlockCoord.y}))
                curBlock.rightRotate();
            break;
        case 'k':
            curBlock.rightRotate();
            if(checkCollision({curBlockCoord.x, curBlockCoord.y}))
                curBlock.leftRotate();
    }
}

void Board::processBlock(){
    if (!checkCollision({curBlockCoord.first + 1, curBlockCoord.second})){
        curBlockCoord.first++;
    }
    else{
        setBlockToBoard();
        clearRow();
        getNewBlock();
    }
}