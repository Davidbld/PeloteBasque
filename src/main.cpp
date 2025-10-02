#include <SFML/Graphics.hpp>
#include "Controllers/GameController.hpp"
#include "Views/GameView.hpp"

int main() {
    // Create window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pelote Basque");
    window.setVerticalSyncEnabled(true);

    // Initialize MVC components
    GameView view(window);
    GameController controller(view, sf::Vector2f(800.0f, 600.0f));
    
    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    controller.togglePause();
                }
            }
        }

        controller.handleInput();
        controller.update();
        
        window.clear(sf::Color::Black);
        window.display();
    }

    return 0;
}