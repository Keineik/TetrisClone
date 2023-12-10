#ifndef BLOCK_H
#define BLOCK_H
#include "headers.h"

class Block{
private:
    vector<vector<int>> block;
public:
    Block(int type = 0);
    void rotation();
    void display();
    int getSize();
    int getValue(int x, int y);
};

#endif