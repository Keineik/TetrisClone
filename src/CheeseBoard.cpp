#include "CheeseBoard.h"

CheeseBoard::CheeseBoard(int n, int m, int cheeseHeight, int lvl) : Board(n, m) {
    level = lvl;

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

void CheeseBoard::clearRow(){
    int n = BOARD_HEIGHT - 1;
    vector<char> blankRow(BOARD_WIDTH, '.');

    int rowsDeleted = 0, cheeseRowsDeleted = 0;
    for (int i = n; i >= 0; i--) {
        int count = 0;
        bool isCheeseRow = false;
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j] != '.') count++;
            if (board[i][j] == 'x') isCheeseRow = true;
        }

        if (count == BOARD_WIDTH) {
            if (isCheeseRow) cheeseRowsDeleted++;
            rowsDeleted++;
            for (int j = i; j >= 1; j--){
                board[j] = board[j - 1];
                board[0] = blankRow;
            }
            i++;
        }
    }
    updateScore(rowsDeleted);
    level += 0.1*cheeseRowsDeleted;
}