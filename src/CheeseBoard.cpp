#include "CheeseBoard.h"

CheeseBoard::CheeseBoard(int n, int m, int cheeseHeight) : Board(n, m) {
    if (cheeseHeight + 4 >= m) 
        throw::invalid_argument("Cheese height must be at least 4 cells lower than board height");

    timerStart = chrono::high_resolution_clock::now();

    vector<char> filledRow(m, 'x');

    uniform_int_distribution<int> range(0, n - 1);
    for (int i = 0; i < cheeseHeight; i++) {
        board[board.size() - 1 - i] = filledRow;
        board[board.size() - 1 - i][range(randomGenerator)] = '.';
    }
}

bool CheeseBoard::checkGameOver() {
    auto timerNow = chrono::high_resolution_clock::now();
    if (chrono::duration<double>(timerNow - timerStart).count() > TIME_LIMIT)
        return true;
    if (isWon()) return true;
    return Board::checkGameOver();
}

bool CheeseBoard::isWon() {
    for (auto row : board) {
        if (any_of(row.begin(), row.end(), [](char i) {return i == 'x';}))
            return false;
    }
    return !checkGameOver();
}

