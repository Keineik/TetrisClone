#ifndef GAME_H
#define GAME_H
#include "Board.cpp"
#include "CheeseBoard.cpp"

class Game{
    private:
        // SFML type variable
        map<char, sf::Texture> textures;
        sf::Font font;
        sf::Text message;
        sf::Time elapsed;
        sf::Clock clock;
        // Pre-made class type variable
        long long highscore;
        int playMode;
        bool quitGame;
        Board* board;
        // Standard type variable
        int boardW, boardH; 
        int blockSize; // width and height of the block
        pair<int, int> boardOffset;   // Offset of the board from the top left corner (0,0)
      

    public: 
        Game(int mode = 0);
        ~Game();
        void drawCurBlock(sf::RenderWindow &window); // draw Cur block;
        void drawNextBlock(pair<int,int> pos, sf::RenderWindow &window); // draw Next block;
        void drawFixedFloor(sf::RenderWindow &window); // draw row of block that 
        void drawHUD(sf::RenderWindow &window, double elapsed = 0);
        bool drawLoseWin(sf::RenderWindow &window, pair<int, int> pos, bool isWin);
        void printText(string text, pair<int,int> pos, sf::RenderWindow &window);
        bool updateBoardToTime(double elapsed);
        void updateScreen(sf::RenderWindow &window, double elapsed = 0); //Update block position, clear row, etc.. before draw it
        void getPlayerMove();  //  Get keyboard input from player      
        void classicRun(sf::RenderWindow &window);
        void reset();
};

#endif