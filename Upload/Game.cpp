#include "Game.h"
Game::Game(int mode){
    blockSize = 8*3;
    boardW = 10; boardH = 20;
    boardOffset = {40*3, 95*3};
    playMode = mode;
    quitGame = false;
    highscore = 0;
    if (mode == 0){
        board  = new Board();
        board->getNewBlock(true);
    }
    if (mode == 1){
        board = new CheeseBoard();
        board->getNewBlock(true);
    }
    ifstream ifs(HIGHSCORE_FILENAME);
    if (ifs) {
        string inData; ifs >> inData;
        highscore = stoi(decodeString(inData));
        ifs.close();
    }
    elapsed = sf::milliseconds(0);
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
    textures['x'].loadFromFile("assets/images/block05.png");
    textures['0'].loadFromFile("assets/images/basic-field-empty-black.png");
    textures['1'].loadFromFile("assets/images/basic-field-flash.png");
    textures['C'].loadFromFile("assets/images/counts.png");    
    
}
Game::~Game(){
    if (board != NULL)
        delete board;
}

bool Game::updateBoardToTime(double elapsed){
    if (elapsed < board->getDropSpeed())
        return false;
    board->updateBoard();
}
void Game::getPlayerMove(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
        board->moveBlock('a');
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
        board->moveBlock('s');
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
        board->moveBlock('d');
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)){
        board->moveBlock('j');
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)){
        board->moveBlock('k');
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)){
        reset();
        clock.restart();
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)){
        quitGame = true;
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        board->moveBlock(' ');
        return;
    }

}
void Game::drawCurBlock(sf::RenderWindow &window){
    sf::RectangleShape blockText(sf::Vector2f(blockSize,blockSize));
    Block &block = board->getCurBlock();
    //Load texture from file;
    blockText.setTexture(&textures[block.getBlockName()]);
    
    //Get corresponding CurBlock coord on the board and draw;
    pair<int, int> pos = board->getCurBlockCoord(); // the coordinate of block on the matrix
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

void Game::drawNextBlock(pair<int,int> pos, sf::RenderWindow &window){
    sf::RectangleShape blockText(sf::Vector2f(blockSize,blockSize));
    Block &block = board->getNextBlock();
    //Load texture from file;
    blockText.setTexture(&textures[block.getBlockName()]);
    
    //Get corresponding CurBlock coord on the board and draw;
    const vector<vector<bool>> &blockInfo = block.getBlock();
    pos.second -= blockInfo[0].size()/2 - 2; // the coordinate of the graphic block
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
    const vector<vector<char>> &boardInfo = board->getBoard();
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

bool Game::drawLoseWin(sf::RenderWindow &window, pair<int, int> pos, bool isWin){
    sf::RectangleShape cover(sf::Vector2f(WIDTH, HEIGHT));
    cover.setFillColor(sf::Color(0,0,0,230));
    cover.setPosition(0,0);
    window.draw(cover);
    if (!isWin){
        sf::Texture texture;
        texture.loadFromFile("assets/images/lose.png");
    
        sf::RectangleShape lose;
        lose.setSize(sf::Vector2f(texture.getSize().x * 3, texture.getSize().y*3));
        lose.setTexture(&texture);

        pos.first = (WIDTH - lose.getSize().x) / 2;
        pos.second = (HEIGHT - lose.getSize().y) / 2;
        lose.setPosition(pos.first, pos.second);
        window.draw(lose);
        window.display();

        while (true){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
                return true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                return false;
        }
    }
    if (isWin){
        sf::Texture texture;
        texture.loadFromFile("assets/images/win.png");
        sf::RectangleShape win;
        win.setSize(sf::Vector2f(texture.getSize().x * 3, texture.getSize().y*3));
        win.setTexture(&texture);

        pos.first = (WIDTH - win.getSize().x) / 2;
        pos.second = (HEIGHT - win.getSize().y) / 2;
        win.setPosition(pos.first, pos.second);
        window.draw(win);
        window.display();

        while (true){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
                return true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                return false;
        }
    }

}
void Game::printText(string text, pair<int,int> pos, sf::RenderWindow &window){
    message.setString(text);
    message.setPosition(pos.first, pos.second);
    window.draw(message);
}
void Game::drawHUD(sf::RenderWindow &window, double elapsed){
    sf::RectangleShape gameFrame;
    gameFrame.setSize(sf::Vector2f(WIDTH, HEIGHT));
    gameFrame.setTexture(&textures[char(playMode + '0')]);
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

    map<char, int> &blockStatistic = board->getStatistics();
    printText(to_string(blockStatistic['T']), {50*3,85*3}, window);
    printText(to_string(blockStatistic['J']), {50*3,100*3}, window);
    printText(to_string(blockStatistic['Z']), {50*3,115*3}, window);
    printText(to_string(blockStatistic['O']), {50*3,130*3}, window);
    printText(to_string(blockStatistic['S']), {50*3,145*3}, window);
    printText(to_string(blockStatistic['L']), {50*3,160*3}, window);
    printText(to_string(blockStatistic['I']), {50*3,175*3}, window);

    //print level 
    printText(to_string(board->getLevel()), {200*3, 160*3}, window);

    //print score and top score;
    printText(to_string(max(highscore, board->getScore())), {203*3, 33*3}, window);
    printText(to_string(board->getScore()), {203*3, 57*3}, window);
    //Draw remaining time
    if (playMode == 1) 
        printText(to_string(int(TIME_LIMIT - elapsed)), {130*3, 10*4}, window);

}
void Game::reset(){
    if (board->getScore() > highscore)
        highscore = board->getScore();
    elapsed = sf::seconds(0);
    clock.restart();
    long long recentScore = board->getScore();
    int recentLevel = board->getLevel();
    if (board != NULL){
        delete board;
        board = NULL;
    }
    if (playMode == 0){
        board = new Board();
    } else{
        // long long recentScore = board->getScore();
        // int recentLevel = board->getLevel();
        board = new CheeseBoard(10, 20, 10, recentLevel, recentScore);
    }
    board->getNewBlock(true);
}
void Game::updateScreen(sf::RenderWindow &window, double elapsed){
    window.clear();
    drawHUD(window,elapsed);
    drawFixedFloor(window);
    drawCurBlock(window);
    drawNextBlock({105*3, 191*3},window);
}

void Game::classicRun(sf::RenderWindow &window){
    
    sf::Event flag;
    
    while (window.isOpen() && !quitGame){
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
        if (updateBoardToTime(clock.getElapsedTime().asSeconds() - elapsed.asSeconds())){
            elapsed = clock.getElapsedTime();
        }
        updateScreen(window, clock.getElapsedTime().asSeconds());
        window.display();
        if (board->checkGameOver(elapsed.asSeconds())){
            if (board->isWon(elapsed.asSeconds())){
                if (drawLoseWin(window,{0,0},true))
                    reset();   
                else return;
            }
            else{
                if(drawLoseWin(window, {0,0}, false))
                    reset();
                else return;
            } 
        }
        sf::sleep(sf::milliseconds(50));
    }
}