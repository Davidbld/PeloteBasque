#ifndef GAME_VIEW_HPP
#define GAME_VIEW_HPP

#include <SFML/Graphics.hpp>
#include "../Models/Ball.hpp"
#include "../Models/Player.hpp"
#include "../Models/GameState.hpp"
#include "../GameConstants.hpp"

// SOLID: Single Responsibility - Handles only rendering
class GameView {
private:
    sf::RenderWindow& window;
    sf::RectangleShape paddleShape;
    sf::CircleShape ballShape;
    sf::RectangleShape gameArea;
    sf::Font font;
    sf::Text scoreText;
    sf::Text maxScoreText;
    sf::Text versionText;

public:
    GameView(sf::RenderWindow& window);
    void render(const Player& player, const Ball& ball, const GameState& state, bool paused);
    sf::RenderWindow& getWindow() { return window; }
    void updateScoreDisplay(const GameState& state);
    
private:
    void initialize();
    void setupText();
};

#endif // GAME_VIEW_HPP