#pragma once
#include "headers.h"
#include <windows.h>
#include <conio.h>

using namespace std;

void goToXY(pair<int, int> coor);

void showConsoleCursor(bool flag);

// for whole board draw
void drawMatrix(const vector<vector<bool>> &board);
// for partial draw
void drawMatrix(pair<int, int> coord, const vector<vector<bool>> &board);