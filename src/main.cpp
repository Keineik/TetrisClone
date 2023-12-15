#include "console.cpp"
#include "Board.cpp"
#include "CheeseBoard.cpp"

// void run() {
//     system("cls");
//     Board board;
//     drawMatrix(board.getBoard());
//     board.getNewBlock(true);
//     drawMatrix(board.getCurBlockCoord(), (board.getCurBlock()).getBlock());
//     drawNextBlock((board.getNextBlock()).getBlock(), board.getBoard());
//     auto t_start = chrono::high_resolution_clock::now();

//     while (!board.checkGameOver()) {
//         auto t_end = chrono::high_resolution_clock::now();
//         if (kbhit()) {
//             char key;
//             key = getch();
//             board.moveBlock(key);
//             drawMatrix(board.getBoard());
//             cout << "Level: " << board.getLevel() << endl;
//             cout << "Score: " << board.getScore() << endl;
//             drawMatrix(board.getCurBlockCoord(), (board.getCurBlock()).getBlock());
//         }
//         if (chrono::duration<double>(t_end-t_start).count() > board.getDropSpeed()) {
//             t_start = t_end;
//             drawMatrix(board.getBoard());
//             cout << "Level: " << board.getLevel() << endl;
//             cout << "Score: " << board.getScore() << endl;
//             drawMatrix(board.getCurBlockCoord(), (board.getCurBlock()).getBlock());
//             drawNextBlock((board.getNextBlock()).getBlock(), board.getBoard());
//             board.updateBoard();
//         }
//     }
// }

void run() {
    system("cls");
    CheeseBoard board;
    drawMatrix(board.getBoard());
    board.getNewBlock(true);
    drawMatrix(board.getCurBlockCoord(), (board.getCurBlock()).getBlock());
    drawNextBlock((board.getNextBlock()).getBlock(), board.getBoard());
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
            cout << "Remaining time: " << TIME_LIMIT - int(chrono::duration<double>(t_end - board.getStartTime()).count());
            drawMatrix(board.getCurBlockCoord(), (board.getCurBlock()).getBlock());
        }
        if (chrono::duration<double>(t_end-t_start).count() > board.getDropSpeed()) {
            t_start = t_end;
            drawMatrix(board.getBoard());
            cout << "Level: " << board.getLevel() << endl;
            cout << "Score: " << board.getScore() << endl;
            cout << "Remaining time: " << TIME_LIMIT - int(chrono::duration<double>(t_end - board.getStartTime()).count());
            drawMatrix(board.getCurBlockCoord(), (board.getCurBlock()).getBlock());
            drawNextBlock((board.getNextBlock()).getBlock(), board.getBoard());
            board.updateBoard();
        }
    }
    
    system("cls");
    if (board.isWon()) cout << "You won!";
    else cout << "You lost";
}

int main() {
    showConsoleCursor(false);
    run();
    return 0;
}

// g++ -o main main.cpp Block.cpp Board.cpp console.cpp