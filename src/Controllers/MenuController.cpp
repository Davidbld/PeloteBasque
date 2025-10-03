#include "MenuController.hpp"

MenuController::MenuController(sf::RenderWindow& window)
    : window(window), view(window), startGame(false), quit(false) {}

void MenuController::handleInput() {
    // Handle keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        state.selectNext();
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        if (state.getCurrentSelection() == MenuOption::PLAY) {
            startGame = true;
        } else {
            quit = true;
        }
    }
    
    // Handle mouse input
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    
    // Update selection based on mouse position
    if (view.isMouseOverButton(mousePos)) {
        MenuOption hoveredButton = view.getClickedButton(mousePos);
        if (state.getCurrentSelection() != hoveredButton) {
            state.setSelection(hoveredButton);
        }
    }
    
    // Handle mouse clicks
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (view.isMouseOverButton(mousePos)) {
            MenuOption clickedButton = view.getClickedButton(mousePos);
            if (clickedButton == MenuOption::PLAY) {
                startGame = true;
            } else {
                quit = true;
            }
        }
    }
}

void MenuController::update() {
    window.clear(sf::Color::Black);
    view.draw(state);
    // Supprimer window.display() pour éviter l'affichage prématuré
}

bool MenuController::shouldStartGame() const {
    return startGame;
}

bool MenuController::shouldQuit() const {
    return quit;
}