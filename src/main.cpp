#include "console.cpp"
#include "Board.cpp"

void run() {
    system("cls");
    Board board;
    drawMatrix(board.getBoard());
    board.getNewBlock();
    drawMatrix(board.getCurBlockCoord(), board.getCurBlock());
    time_t t1 = time(0);
    while (!board.checkGameOver()) {
        time_t t2 = time(0);
        if (kbhit()) {
            char key;
            key = getch();
            board.moveBlock(key);
            drawMatrix(board.getBoard());
            drawMatrix(board.getCurBlockCoord(), board.getCurBlock());
        }
        if (difftime(t2, t1) > 0.5){
            t1 = t2;
            drawMatrix(board.getBoard());
            drawMatrix(board.getCurBlockCoord(), board.getCurBlock());
            board.processBlock();
        }
    }
}

int main() {
    showConsoleCursor(false);
    run();
    return 0;
}

// g++ -o main main.cpp Block.cpp Board.cpp console.cpp