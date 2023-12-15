#include <SFML/Graphics.hpp>
#include "Board.cpp"
#define BACKGROUND "assets/images/basic-field-empty-black.png"
#define IMAGE "assets/images/"
#define FONT "assets/fonts/tetris-2-bombliss-credits-font.ttf"
using namespace std;

class Game{
    private:
        // SFML type variable
        map<char, sf::Texture> textures;
        sf::Font font;
        sf::Text message;
        // Pre-made class type variable
        Board board;
        // Standard type variable
        int boardW, boardH;
        int WIDTH, HEIGHT; //Size of the game screen;   
        int blockSize; // width and height of the block
        pair<int, int> boardOffset;   // Offset of the board from the top left corner (0,0)
      

    public: 
        Game(int width = 255*3, int height = 225*3);
        ~Game();
        void drawCurBlock(sf::RenderWindow &window); // draw Cur block;
        void drawNextBlock(sf::RenderWindow &window); // draw Next block;
        void drawFixedFloor(sf::RenderWindow &window); // draw row of block that 
        void drawHUD(sf::RenderWindow &window);
        void printText(string text, pair<int,int> pos, sf::RenderWindow &window);
        bool updateBoardToTime(double elapsed);
        void updateScreen(sf::RenderWindow &window); //Update block position, clear row, etc.. before draw it
        void getPlayerMove();  //  Get keyboard input from player      
        void run();
};


Game::Game(int width, int height){
    WIDTH = width; HEIGHT = height;
    blockSize = 8*3;
    boardW = 10; boardH = 20;
    boardOffset = {40*3, 95*3};
    board.getNewBlock(true);

    font.loadFromFile(FONT);
    message.setFont(font);
    message.setFillColor(sf::Color::White);
    textures['I'].loadFromFile("assets/images/block01.png");
    textures['O'].loadFromFile("assets/images/block01.png");
    textures['T'].loadFromFile("assets/images/block01.png");
    textures['J'].loadFromFile("assets/images/block02.png");
    textures['S'].loadFromFile("assets/images/block02.png");
    textures['L'].loadFromFile("assets/images/block03.png");
    textures['Z'].loadFromFile("assets/images/block03.png");
    textures['B'].loadFromFile("assets/images/basic-field-empty-black.png");
    textures['C'].loadFromFile("assets/images/counts.png");    
    
}
Game::~Game(){

}

bool Game::updateBoardToTime(double elapsed){
    if (elapsed < board.getDropSpeed())
        return false;
    board.updateBoard();
}
void Game::getPlayerMove(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        board.moveBlock('a');
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        board.moveBlock('s');
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        board.moveBlock('d');
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)){
        board.moveBlock('j');
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)){
        board.moveBlock('k');
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        board.moveBlock(' ');
        return;
    }

}
void Game::drawCurBlock(sf::RenderWindow &window){
    sf::RectangleShape blockText(sf::Vector2f(blockSize,blockSize));
    Block &block = board.getCurBlock();
    //Load texture from file;
    blockText.setTexture(&textures[block.getBlockName()]);
    
    //Get corresponding CurBlock coord on the board and draw;
    pair<int, int> pos = board.getCurBlockCoord(); // the coordinate of block on the matrix
    sf::Texture texture;

    const vector<vector<bool>> &blockInfo = block.getBlock();
    for (int  i = 0;  i < blockInfo.size(); i ++){
        for (int  j = 0; j < blockInfo[i].size(); j++){
            if (blockInfo[i][j]){
                blockText.setPosition(boardOffset.second + (pos.second + j) * blockSize, boardOffset.first + (pos.first + i) * blockSize);
                window.draw(blockText);
            }
        }
    }
}

void Game::drawNextBlock(sf::RenderWindow &window){
    sf::RectangleShape blockText(sf::Vector2f(blockSize,blockSize));
    Block &block = board.getNextBlock();
    //Load texture from file;
    blockText.setTexture(&textures[block.getBlockName()]);
    
    //Get corresponding CurBlock coord on the board and draw;
    pair<int, int> pos = {0,0}; // the coordinate of block on the matrix
    const vector<vector<bool>> &blockInfo = block.getBlock();
    pos.first = 105*3; 
    pos.second = 191*3 - blockInfo[0].size()/2 + 2; // the coordinate of the graphic block
    sf::Texture texture;

    
    for (int  i = 0;  i < blockInfo.size(); i ++){
        for (int  j = 0; j < blockInfo[i].size(); j++){
            if (blockInfo[i][j]){
                blockText.setPosition(pos.second + j * blockSize, pos.first + i * blockSize);
                window.draw(blockText);
            }
        }
    }
}

void Game::drawFixedFloor( sf::RenderWindow &window){
    sf::RectangleShape block(sf::Vector2f(blockSize, blockSize));
    const vector<vector<char>> &boardInfo = board.getBoard();
    for (int i = 0; i < boardInfo.size(); i++){
        for (int j = 0; j < boardInfo[i].size(); j++){
            if (boardInfo[i][j] != '.'){
                block.setTexture(&textures[boardInfo[i][j]]);
                block.setPosition( boardOffset.second + j*blockSize, boardOffset.first + i*blockSize);
                window.draw(block);
            }
        }
    }
}
void Game::printText(string text, pair<int,int> pos, sf::RenderWindow &window){
    message.setString(text);
    message.setPosition(pos.first, pos.second);
    window.draw(message);
}
void Game::drawHUD(sf::RenderWindow &window){
    sf::RectangleShape gameFrame;
    gameFrame.setSize(sf::Vector2f(WIDTH, HEIGHT));
    gameFrame.setTexture(&textures['B']);
    gameFrame.setPosition(0,0);
    window.draw(gameFrame);

    //Load count;
    sf::RectangleShape stateFrame;
    stateFrame.setSize(sf::Vector2f(textures['C'].getSize()));
    stateFrame.setTexture(&textures['C']);
    stateFrame.scale(3,3);
    stateFrame.setPosition(13*3,61*3);
    window.draw(stateFrame);

    //Print statistic

    
    printText(to_string(blockStatistic['T']), {50*3,85*3}, window);
    printText(to_string(blockStatistic['J']), {50*3,100*3}, window);
    printText(to_string(blockStatistic['Z']), {50*3,115*3}, window);
    printText(to_string(blockStatistic['O']), {50*3,130*3}, window);
    printText(to_string(blockStatistic['S']), {50*3,145*3}, window);
    printText(to_string(blockStatistic['L']), {50*3,160*3}, window);
    printText(to_string(blockStatistic['I']), {50*3,175*3}, window);

    //print level 
    printText(to_string(board.getLevel()), {200*3, 160*3}, window);

    //print score and top score;
    printText(to_string(board.getScore()), {203*3, 33*3}, window);
    printText(to_string(board.getScore()), {203*3, 57*3}, window);


}
void Game::updateScreen(sf::RenderWindow &window){
    window.clear();
    drawHUD(window);
    drawFixedFloor(window);
    drawCurBlock(window);
    drawNextBlock(window);
}

void Game::run(){
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tetris Clone");
    window.setFramerateLimit(30);
    sf::Event flag;
    sf::Clock clock;
    while (window.isOpen()){
        while (window.pollEvent(flag)){
            switch (flag.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                getPlayerMove();
                break;
            default:
                break;
            }
        }
        if (updateBoardToTime(clock.getElapsedTime().asSeconds())){
            clock.restart(); 
        }
        updateScreen(window);
        window.display();
        if (board.checkGameOver()) window.close();
        sf::sleep(sf::milliseconds(50));
    }
}

int main()
{
 
    Game game;
    game.run();
    return 0;
}