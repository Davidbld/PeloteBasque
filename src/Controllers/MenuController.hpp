#pragma once
#include <SFML/Graphics.hpp>
#include "../Models/MenuState.hpp"
#include "../Views/MenuView.hpp"

class MenuController {
public:
    MenuController(sf::RenderWindow& window);
    void handleInput();
    void update();
    bool shouldStartGame() const;
    bool shouldQuit() const;

private:
    MenuState state;
    MenuView view;
    sf::RenderWindow& window;
    bool startGame;
    bool quit;
};