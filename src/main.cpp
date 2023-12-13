#include "console.cpp"
#include "Board.cpp"

void run() {
    system("cls");
    Board board;
    drawMatrix(board.getBoard());
    board.getNewBlock(true);
    drawMatrix(board.getCurBlockCoord(), board.getCurBlock());
    drawNextBlock(board.getNextBlock(), board.getBoard());
    auto t_start = chrono::high_resolution_clock::now();

    while (!board.checkGameOver()) {
        auto t_end = chrono::high_resolution_clock::now();
        if (kbhit()) {
            char key;
            key = getch();
            board.moveBlock(key);
            drawMatrix(board.getBoard());
            cout << "Level: " << board.getLevel() << endl;
            cout << "Score: " << board.getScore() << endl;
            drawMatrix(board.getCurBlockCoord(), board.getCurBlock());
        }
        if (chrono::duration<double>(t_end-t_start).count() > board.getDropSpeed()) {
            t_start = t_end;
            drawMatrix(board.getBoard());
            cout << "Level: " << board.getLevel() << endl;
            cout << "Score: " << board.getScore() << endl;
            drawMatrix(board.getCurBlockCoord(), board.getCurBlock());
            drawNextBlock(board.getNextBlock(), board.getBoard());
            board.updateBoard();
        }
    }
}

int main() {
    showConsoleCursor(false);
    run();
    return 0;
}

// g++ -o main main.cpp Block.cpp Board.cpp console.cpp