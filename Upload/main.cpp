#include "Game.cpp"
#include "Menu.cpp"

void run(){
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tetris Clone");
    window.setFramerateLimit(30);
    int userChoice = -1;
    Menu menu;
    while (window.isOpen()){
        if (userChoice = -1){
            userChoice = menu.showMenu(window);
        }
        if (userChoice == 0){
            Game game(0);
            game.classicRun(window);
            userChoice = -1;
        }
        if (userChoice == 1){
            Game game(1);
            game.classicRun(window);
            userChoice = -1;
        }
    }
}

int main()
{
    
    run();
    return 0;
}