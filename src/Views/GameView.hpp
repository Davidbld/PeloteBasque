#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/Graphics.hpp>
#include "../Models/Ball.hpp"
#include "../Models/Player.hpp"
#include "../Models/GameState.hpp"

// SOLID: Single Responsibility - Handles only rendering
class GameView {
private:
    sf::RenderWindow& window;
    sf::RectangleShape paddleShape;
    sf::CircleShape ballShape;
    sf::Font font;
    sf::Text scoreText;
    sf::Text maxScoreText;

public:
    GameView(sf::RenderWindow& window);
    void initialize();
    
    // Render methods
    void render(const Player& player, const Ball& ball, const GameState& state, bool isPaused);
    void updateScoreDisplay(const GameState& state);
    
private:
    void setupText();
};

#endif // GAME_VIEW_HPP