#include "Menu.h"
Menu::Menu(pair<int, int> size):choiceStatus({1,0,0,0,0}){
    buttonSize = size;
    choice = 0;
    for (int  i = 0; i < 5; i ++){
        choiceOff.push_back(sf::Texture());
    }
    choiceOff[0].loadFromFile("assets/images/class_off.png");
    choiceOff[1].loadFromFile("assets/images/cheese_off.png");
    choiceOff[2].loadFromFile("assets/images/how_off.png");
    choiceOff[3].loadFromFile("assets/images/credit_off.png");
    choiceOff[4].loadFromFile("assets/images/quit_off.png");
    for (int  i = 0; i < 5; i ++){
        choiceOn.push_back(sf::Texture());
    }
    choiceOn[0].loadFromFile("assets/images/class_on.png");
    choiceOn[1].loadFromFile("assets/images/cheese_on.png");
    choiceOn[2].loadFromFile("assets/images/how_on.png");
    choiceOn[3].loadFromFile("assets/images/credit_on.png");
    choiceOn[4].loadFromFile("assets/images/quit_on.png");
    
}
Menu::~Menu(){

}
int Menu::getUserInput(){
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) && choice > 0){
        choiceStatus[choice--] = 0;
        choiceStatus[choice] = 1;
    }
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) && choice < 4){
        choiceStatus[choice++] = 0;
        choiceStatus[choice] = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
        return choice;
    }
    return -1;
}
void Menu::drawButton(sf::RenderWindow &window){
    sf::RectangleShape button(sf::Vector2f(buttonSize.first, buttonSize.second));
    pair<int, int> buttonOffset = {(WIDTH - buttonSize.first)/2, 15};
    for (int i = 0; i < choiceStatus.size(); i++){
        if (choiceStatus[i])
            button.setTexture(&choiceOn[i]);
        else button.setTexture(&choiceOff[i]);
        button.setPosition(buttonOffset.first, buttonOffset.second + i*(buttonSize.second + 5));
        window.draw(button);
    }
}
void Menu::drawH2P(sf::RenderWindow &window){
    sf::RectangleShape howtoplay(sf::Vector2f(WIDTH, HEIGHT));
    sf::Texture texture;
    texture.loadFromFile("assets/images/howtoplay.png");
    howtoplay.setTexture(&texture);
    window.draw(howtoplay);
    window.display();
    sf::Event hold;
    bool wait = true;
    while (true){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            break;
    }
}
void Menu::drawCredit(sf::RenderWindow &window){
    sf::RectangleShape credit(sf::Vector2f(WIDTH, HEIGHT));
    sf::Texture texture;
    texture.loadFromFile("assets/images/credit.png");
    credit.setTexture(&texture);
    window.draw(credit);
    window.display();
    sf::Event hold;
    bool wait = true;
    while (true){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            break;
    }
}
int Menu::showMenu(sf::RenderWindow &window){
    sf::Event flag;
    choice = 0;
    int userChoice = -1;
    while(window.isOpen()){
        while (window.pollEvent(flag)){
            switch (flag.type)
            {
            case sf::Event::KeyPressed:
                userChoice = getUserInput();
                break;
            case sf::Event::Closed:
                window.close();
            default:
                break;
            }
            
        }
        window.clear();
        drawButton(window);
        if(userChoice == 1 || userChoice == 0)
            return userChoice;
        if (userChoice == 2){
            drawH2P(window);
            userChoice = -1;
        }
        if (userChoice == 3){
            drawCredit(window);
            userChoice = -1;
        }
        if (userChoice == 4){
            window.close();
        }
        window.display();
        
    }
    return userChoice;
}
