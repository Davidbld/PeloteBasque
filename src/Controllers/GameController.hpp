#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include "../Models/Ball.hpp"
#include "../Models/Player.hpp"
#include "../Models/GameState.hpp"
#include "../Views/GameView.hpp"

// GRASP: Controller pattern - Coordinates game logic
class GameController {
private:
    Ball ball;
    Player player;
    GameState gameState;
    GameView& view;
    sf::Clock clock;
    
    // GRASP: Protected Variations - Timer handling
    sf::Vector2f windowSize;
    bool ballActive;
    bool gamePaused;
    sf::Clock resetClock;
    float resetTimer;
    const float RESET_DELAY = 0.5f;

public:
    bool isPaused() const { return gamePaused; }
    void togglePause() { gamePaused = !gamePaused; }
    GameController(GameView& view, const sf::Vector2f& windowSize);
    void initialize();
    void update();
    void handleInput();
    void checkCollisions();
    
private:
    void resetBall();
    void updateScore(bool scored);
};

#endif // GAME_CONTROLLER_HPP