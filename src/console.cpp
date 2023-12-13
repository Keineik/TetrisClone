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

void drawNextBlock(const vector<vector<bool>> &next, const vector<vector<bool>> &board){
    goToXY({0, BOARD_WIDTH * 2 + 5});
    cout << "NEXT BLOCK";
    for (int i = 0; i < 20; i++){
        for (int j = 0; j < 20; j++){
            goToXY({2 + i, BOARD_WIDTH * 2 + 2 * j});
            cout << " ";
        }
    }
    for (int i = 0; i < next.size(); i++){
        for (int j = 0; j < next[i].size(); j++){
            if (next[i][j]){
                goToXY({2 + i, BOARD_WIDTH * 2 + 8 + 2 * j});
                cout << "#";
            }
        }
    }
}