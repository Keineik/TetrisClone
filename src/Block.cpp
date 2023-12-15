#include "Block.h"

int Block::getSize() { 
    return block.size(); 
}

vector<bool>& Block::operator [] (int row) {
    return block[row];
}

const vector<vector<bool>>& Block::getBlock() {
    return block;
}
char Block::getBlockName(){return blockname;}
void Block::leftRotate() {
    int n = block.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(block[i][j], block[j][i]);
        }
    }

    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n; j++) {
            swap(block[i][j], block[n - 1 - i][j]);
        }
    }
}
void Block::rightRotate() {
    int n = block.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(block[i][j], block[j][i]);
        }
    }

    for (int j = 0; j < n / 2; j++) {
        for (int i = 0; i < n; i++) {
            swap(block[i][j], block[i][n - 1 - j]);
        }
    }
}

void Block::print() {
    for (const auto& row : block) {
        for (bool value : row) {
            cout << value;
        }
        cout << endl;
    }
    cout << endl;
}