#ifndef GAME_CONTROLLER_HPP
#define GAME_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "../Models/Ball.hpp"
#include "../Models/Player.hpp"
#include "../Models/GameState.hpp"
#include "../Views/GameView.hpp"
#include "../Views/PauseMenuView.hpp"

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
    bool quitGame;
    std::unique_ptr<PauseMenuView> pauseMenu;
    sf::Clock resetClock;
    float resetTimer;
    bool mouseWasPressed;
    static constexpr float RESET_DELAY = 0.5f;

public:
    // Delete copy constructor and assignment operator
    GameController(const GameController&) = delete;
    GameController& operator=(const GameController&) = delete;
    // Allow move constructor and assignment
    GameController(GameController&&) = default;
    GameController& operator=(GameController&&) = default;

public:
    bool isPaused() const { return gamePaused; }
    void togglePause();
    bool shouldQuit() const { return quitGame; }
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