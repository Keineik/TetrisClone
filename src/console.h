#ifndef CONSOLE_H
#define CONSOLE_H
#include "Board.h"

void goToXY(pair<int, int> coor);

void showConsoleCursor(bool flag);

// for whole board draw
void drawMatrix(const vector<vector<bool>> &board);
// for partial draw
void drawMatrix(pair<int, int> coord, const vector<vector<bool>> &board);
// for drawing next block
void drawNextBlock(const Block &board);

#endif