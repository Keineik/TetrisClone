#include "block.h"

Block::Block(int type){
    if (type == 0){
        vector<vector<int>> temp{{1, 1}, 
                                 {1, 1}};
        block = temp;
    }
    else if (type == 1){
        vector<vector<int>> temp{{0, 1, 0}, 
                                 {1, 1, 1}, 
                                 {0, 0, 0}};
        block = temp;
    }
    else if (type == 2){
        vector<vector<int>> temp{{1, 0, 0}, 
                                 {1, 1, 1}, 
                                 {0, 0, 0}};
        block = temp;
    }
    else if (type == 3){
        vector<vector<int>> temp{{0, 0, 1}, 
                                 {1, 1, 1}, 
                                 {0, 0, 0}};
        block = temp;
    }
    else if (type == 4){
        vector<vector<int>> temp{{1, 1, 0}, 
                                 {0, 1, 1}, 
                                 {0, 0, 0}};
        block = temp;
    }
    else if (type == 5){
        vector<vector<int>> temp{{0, 1, 1}, 
                                 {1, 1, 0}, 
                                 {0, 0, 0}};
        block = temp;
    }   
    else {
        vector<vector<int>> temp{{0, 0, 0, 0}, 
                                 {1, 1, 1, 1}, 
                                 {0, 0, 0, 0},
                                 {0, 0, 0, 0}};
        block = temp;
    }
}

void Block::display(){

}

void Block::rotation(){
    vector<vector<int>> temp = block;
    int n = block.size();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            block[i][j] = temp[j][n - i + 1];
        }
    }
}

int Block::getSize(){
    return block.size();
}

int Block::getValue(int x, int y){
    return block[x][y];
}