#ifndef MENU_H
#define MENU_H
#include "headers.h"
class Menu{
    private:
        pair<int,int> buttonSize;
        int choice;
        vector<bool> choiceStatus;
        vector<sf::Texture> choiceOn;
        vector<sf::Texture> choiceOff;
    public:
        Menu(pair<int, int> size = {65*3, 10*3});
        ~Menu();
        int getUserInput();
        void drawButton(sf::RenderWindow &window);
        void drawH2P(sf::RenderWindow &window);
        void drawCredit(sf::RenderWindow &window);
        int showMenu(sf::RenderWindow &window);
};

#endif