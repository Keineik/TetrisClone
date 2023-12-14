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
    static map<char, string> blockTexture;
    char blockname;
    string texturePath;
    vector<vector<bool>> block;

public:
    Block() : blockname(getRandomChar()), block(getBlockMatrix[blockname]), texturePath(blockTexture[blockname]) {}

    int getSize();
    const vector<vector<bool>>& getBlock();
    vector<bool>& operator [] (int n);
    const string &getTexturePath();
    void leftRotate();
    void rightRotate();
    
    void print();   
};
map<char, string> Block::blockTexture = {
    {'I', "assets/images/block01.png"},
    {'J', "assets/images/block02.png"},
    {'L', "assets/images/block03.png"},
    {'O', "assets/images/block01.png"},
    {'S', "assets/images/block02.png"},
    {'T', "assets/images/block01.png"},
    {'Z', "assets/images/block03.png"},
};
map<char, vector<vector<bool>>> Block::getBlockMatrix = {
    {'I', {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}},
    {'J', {{0, 0, 0}, {1, 1, 1}, {0, 0, 1}}},
    {'L', {{0, 0, 0}, {1, 1, 1}, {1, 0, 0}}},
    {'O', {{0,0,0,0},{0,1, 1,0}, {0,1, 1,0},{0,0,0,0}}},
    {'S', {{0, 0, 0}, {0, 1, 1}, {1, 1, 0}}},
    {'T', {{0, 0, 0}, {1, 1, 1}, {0, 1, 0}}},
    {'Z', {{0, 0, 0}, {1, 1, 0}, {0, 1, 1}}}
};

#endif