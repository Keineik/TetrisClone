#include "board.h"

void Board::userInput(){
    char key;
    key = getchar();
    switch(key){
        case 'd':
            if (!checkCollision(x + 1, y)){
                movePieceLR(x + 1, y);
            }
            break;
        case 'a':
            if (!checkCollision(x - 1, y)){
                movePieceLR(x - 1, y);
            }
            break;
        case 's':
            if (!checkCollision(x, y + 1)){
                movePieceLR(x, y + 1);
            }
            break;
        case 'w':
            currentBlock.rotation();
    }
}

void Board::copyCurrentBoard(){
    // do something
}

void Board::movePieceDown(){
    
}

void Board::run(){
    // do something
}

void Board::clearScreen(){
    system("cls");
}

void Board::initDrawBoard(){
    
}

void Board::redrawBoard(){

}

void Board::movePieceLR(int _x, int _y){

}

bool Board::checkCollision(int _x, int _y){
    int n = currentBlock.getSize();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (currentBlock.getValue(i, j) && !board[i + _x][j + _y]){
                return true;
            }
        }
    }
    return false;
}

bool Board::checkGameOver(){

}

void Board::clearRow(){

}