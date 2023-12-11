#include "headers.h"
#include "console.h"
#include "Board.h"

void run() {
    Board board;
    drawMatrix(board.getBoard());
    drawMatrix(board.getCurBlockCoord(), board.getCurBlock());
    board.getNewBlock();

    while (!board.checkGameOver()) {
        if (kbhit()) {
            char key;
            key = getch();
            board.moveBlock(key);
            drawMatrix(board.getBoard());
            drawMatrix(board.getCurBlockCoord(), board.getCurBlock());
        }
    }
}

int main() {
    cout << "2";

    return 0;
}