#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <map> // to map char to array representation of that char
#include <random> // for better random block generator
#include <chrono> // to get seed for random generator
#include <fstream> // to write high score to file

#include <windows.h> 
#include <conio.h>
#include <SFML/Graphics.hpp>

using namespace std;
#define BACKGROUND "assets/images/basic-field-empty-black.png"
#define IMAGE "assets/images/"
#define FONT "assets/fonts/tetris-2-bombliss-credits-font.ttf"
#define WIDTH 765
#define HEIGHT 675
#define BOARD_HEIGHT board.size()
#define BOARD_WIDTH board[0].size()


const string HIGHSCORE_FILENAME = "highscore.txt";
const string KEY = "tetris";

string encodeString(const string& input) {
    std::string encodedData = input;
    for (size_t i = 0; i < input.size(); ++i) {
        encodedData[i] ^= KEY[i % KEY.size()];
    }
    return encodedData;
}

string decodeString(const string& input) {
    return encodeString(input);
}

#endif