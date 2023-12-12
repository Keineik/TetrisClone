#ifndef BLOCK_H
#define BLOCK_H
#include "headers.h"

// for better block generation
mt19937 randomGenerator{ static_cast<std::mt19937::result_type>(
	std::chrono::steady_clock::now().time_since_epoch().count()
) };
uniform_int_distribution<int> distribution(0, 6);
char toShape[7] = {'I', 'J', 'L', 'O', 'S', 'T', 'Z'};

char getRandomChar() {
    return toShape[distribution(randomGenerator)];
}

class Block {
private:
    static map<char, vector<vector<bool>>> getBlockMatrix;

    vector<vector<bool>> block;

public:
    Block() : block(getBlockMatrix[getRandomChar()]) {}

    int getSize();
    const vector<vector<bool>>& getBlock();
    vector<bool>& operator [] (int n);

    void leftRotate();
    void rightRotate();
    
    void print();   
};

map<char, vector<vector<bool>>> Block::getBlockMatrix = {
    {'I', {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {'J', {{1, 0, 0}, {1, 1, 1}, {0, 0, 0}}},
    {'L', {{0, 0, 1}, {1, 1, 1}, {0, 0, 0}}},
    {'O', {{1, 1}, {1, 1}}},
    {'S', {{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}},
    {'T', {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}}},
    {'Z', {{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}}
};

#endif