#include <SFML/Graphics.hpp>
#include <memory>
#include "Controllers/GameController.hpp"
#include "Controllers/MenuController.hpp"
#include "Views/GameView.hpp"

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pelote Basque");
    window.setVerticalSyncEnabled(true);

    // Initialize menu
    MenuController menuController(window);
    bool inGame = false;
    
    // Initialize game components
    GameView gameView(window);
    std::unique_ptr<GameController> gameController;
    
    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (inGame && event.key.code == sf::Keyboard::Escape) {
                    gameController->togglePause();
                }
            }
        }

        if (!inGame) {
            menuController.handleInput();
            menuController.update();
            
            if (menuController.shouldStartGame()) {
                inGame = true;
                // Create a new game controller
                gameController = std::make_unique<GameController>(gameView, sf::Vector2f(800.0f, 600.0f));
            }
            if (menuController.shouldQuit()) {
                window.close();
            }
        } else {
            gameController->handleInput();
            gameController->update();
            
            if (gameController->shouldQuit()) {
                inGame = false; // Retour au menu principal
            }
        }
        window.display(); // Afficher la fenêtre après mise à jour
    }

    return 0;
}