#include "console.h"

void goToXY(pair<int, int> coord) {
    HANDLE handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD outCoord = {(SHORT) coord.second, (SHORT) coord.first};
    SetConsoleCursorPosition(handleOutput, outCoord);
}

void showConsoleCursor(bool show) {
    HANDLE handleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(handleOutput, &cursorInfo);
    cursorInfo.bVisible = show; // set the cursor visibility
    SetConsoleCursorInfo(handleOutput, &cursorInfo);
}


// for whole board draw
void drawMatrix(const vector<vector<bool>> &board) {
    goToXY({0, 0});
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            cout << ".#"[board[i][j]] << " ";
        }
        cout << "\n";
    }
}

// for partial draw
void drawMatrix(pair<int, int> coord, const vector<vector<bool>> &board) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board[i][j]) {
                goToXY({coord.x + i, 2 * (coord.y + j)});
                cout << "#";
            }
        }
    }
}

