#include <iostream>
#include <vector>
#include <map>

using namespace std;
typedef vector<vector<bool>> BlockMatrix;

class Block {
private:
    static map<char, BlockMatrix> getBlockMatrix;

    BlockMatrix block;

public:
    Block(char c) : block(getBlockMatrix[c]) {}

    void rotateLeft();
    void rotateRight();
    void print();
};

map<char, BlockMatrix> Block::getBlockMatrix = {
    {'I', {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {'J', {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}}},
    {'L', {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}}},
    {'O', {{1, 1}, {1, 1}}},
    {'S', {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}},
    {'T', {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}}},
    {'Z', {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}}
};

void Block::rotateLeft() {
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

void Block::rotateRight() {
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