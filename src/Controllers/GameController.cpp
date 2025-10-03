#include "GameController.hpp"
#include "../GameConstants.hpp"
#include <memory>

GameController::GameController(GameView& gameView, const sf::Vector2f& windowSize)
    : view(gameView),
      ball(windowSize),
      player(sf::Vector2f(50.f, windowSize.y / 2.f), 100.f),
      windowSize(windowSize),
      ballActive(true),
      gamePaused(false),
      quitGame(false),
      resetTimer(0.f) {
    initialize();
}

void GameController::initialize() {
    ball.reset(sf::Vector2f(800.f, 600.f));
}

void GameController::togglePause() {
    gamePaused = !gamePaused;
    if (gamePaused && !pauseMenu) {
        pauseMenu = std::make_unique<PauseMenuView>(view.getWindow());
    }
    mouseWasPressed = false; // Reset mouse press state when toggling pause
}

void GameController::update() {
    float deltaTime = clock.restart().asSeconds();
    
    if (!gamePaused) {
        // Mise à jour des entités
        player.update(deltaTime, windowSize.y);
        
        if (!ballActive) {
            resetTimer -= deltaTime;
            if (resetTimer <= 0.f) {
                ballActive = true;
                ball.reset(windowSize);
            }
        } else {
            ball.update(deltaTime);
            // Vérification des collisions
            checkCollisions();
        }
        
        // Rendu du jeu
        view.render(player, ball, gameState, false);
    } else {
        // En pause, on affiche d'abord le jeu puis le menu de pause par-dessus
        view.render(player, ball, gameState, false);
        if (pauseMenu) {
            pauseMenu->draw();
        }
    }
}

void GameController::handleInput() {
    if (!gamePaused) {
        // Contrôles du jeu normal
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.moveUp(clock.getElapsedTime().asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player.moveDown(clock.getElapsedTime().asSeconds());
        }
    } else if (pauseMenu) {
        // Gestion des entrées du menu pause
        sf::Vector2i mousePos = sf::Mouse::getPosition(view.getWindow());
        
        bool mousePressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (mousePressed && !mouseWasPressed && pauseMenu->isMouseOverButton(mousePos)) {
            PauseOption option = pauseMenu->getClickedButton(mousePos);
            if (option == PauseOption::CONTINUE) {
                gamePaused = false;
                pauseMenu.reset();
            } else if (option == PauseOption::QUIT) {
                quitGame = true;
            }
        }
        mouseWasPressed = mousePressed;
    }
}

void GameController::checkCollisions() {
    // Collision avec les murs (haut et bas)
    float effectiveWindowHeight = windowSize.y - 2 * MARGIN_Y;
    if (ball.getPosition().y <= 0 || ball.getPosition().y >= effectiveWindowHeight) {
        sf::Vector2f currentDir = ball.getDirection();
        currentDir.y = -currentDir.y; // Inverse la direction verticale
        ball.setDirection(currentDir);
    }
    
    // Collision avec le mur de droite
    float effectiveWindowWidth = windowSize.x - 2 * MARGIN_X;
    if (ball.getPosition().x >= effectiveWindowWidth) {
        sf::Vector2f currentDir = ball.getDirection();
        currentDir.x = -currentDir.x; // Inverse la direction horizontale
        ball.setDirection(currentDir);
        ball.accelerate(true); // Accélération plus faible pour le rebond mural
        // Augmente le score car la balle a atteint le mur de droite
        updateScore(true);
    }
    
    // Collision avec la raquette
    sf::FloatRect paddleBounds(
        player.getPosition().x - 10,
        player.getPosition().y - 50,
        20,
        100
    );
    if (ball.handleCollision(paddleBounds)) {
        // On n'augmente plus le score ici car il est augmenté quand la balle touche le mur de droite
    }
    
    // Balle sort de l'écran à gauche (game over)
    if (ball.getPosition().x < 0) {
        gameState.resetScore();
        resetBall();
    }
}

void GameController::resetBall() {
    ballActive = false;
    resetTimer = RESET_DELAY;
}

void GameController::updateScore(bool scored) {
    if (scored) {
        gameState.incrementScore();
    }
}