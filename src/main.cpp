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
    int highscore = 0;
    ifstream ifs(HIGHSCORE_FILENAME);
    if (ifs) {
        string inData; ifs >> inData;
        highscore = stoi(decodeString(inData));
        ifs.close();
    }

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
            cout << "Highscore: " << ((highscore > board.getScore()) ? highscore : board.getScore()); cout << endl;
            cout << "Remaining time: " << TIME_LIMIT - int(chrono::duration<double>(t_end - board.getStartTime()).count()) << endl;
            for (auto m : board.getStatistics()) cout << "tetromino: " << m.first << ": " << m.second << " times" << endl;

            drawMatrix(board.getCurBlockCoord(), (board.getCurBlock()).getBlock());
        }
        if (chrono::duration<double>(t_end-t_start).count() > board.getDropSpeed()) {
            t_start = t_end;
            drawMatrix(board.getBoard());
            cout << "Level: " << board.getLevel() << endl;
            cout << "Score: " << board.getScore() << endl;
            cout << "Highscore: " << ((highscore > board.getScore()) ? highscore : board.getScore()); cout << endl;
            cout << "Remaining time: " << TIME_LIMIT - int(chrono::duration<double>(t_end - board.getStartTime()).count()) << endl;
            for (auto m : board.getStatistics()) cout << "tetromino: " << m.first << ": " << m.second << " times" << endl;

            drawMatrix(board.getCurBlockCoord(), (board.getCurBlock()).getBlock());
            drawNextBlock((board.getNextBlock()).getBlock(), board.getBoard());
            board.updateBoard();
        }
    }
    
    system("cls");
    drawMatrix(board.getBoard());
    cout << "Level: " << board.getLevel() << endl;
    cout << "Score: " << board.getScore() << endl;
    cout << "Highscore: " << ((highscore > board.getScore()) ? highscore : board.getScore()); cout << endl;
    cout << "Remaining time: " << 0 << endl;
    for (auto m : board.getStatistics()) cout << "tetromino: " << m.first << ": " << m.second << " times" << endl;
    if (board.isWon()) cout << "You won!";
    else cout << "You lost";

    

    
    
}

int main() {
    showConsoleCursor(false);
    run();
    return 0;
}

// g++ -o main main.cpp Block.cpp Board.cpp console.cpp