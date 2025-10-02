#include "GameController.hpp"

GameController::GameController(GameView& gameView, const sf::Vector2f& windowSize)
    : view(gameView),
      ball(windowSize),
      player(sf::Vector2f(50.f, windowSize.y / 2.f), 100.f),
      windowSize(windowSize),
      ballActive(true),
      gamePaused(false),
      resetTimer(0.f) {
    initialize();
}

void GameController::initialize() {
    ball.reset(sf::Vector2f(800.f, 600.f));
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
    }
    
    // Rendu (même en pause)
    view.render(player, ball, gameState, gamePaused);
}

void GameController::handleInput() {
    // Les mouvements ne sont possibles que si le jeu n'est pas en pause
    if (!gamePaused) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player.moveUp(clock.getElapsedTime().asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player.moveDown(clock.getElapsedTime().asSeconds());
        }
    }
}

void GameController::checkCollisions() {
    // Collision avec les murs (haut et bas)
    if (ball.getPosition().y <= 0 || ball.getPosition().y >= windowSize.y) {
        sf::Vector2f currentDir = ball.getDirection();
        currentDir.y = -currentDir.y; // Inverse la direction verticale
        ball.setDirection(currentDir);
    }
    
    // Collision avec le mur de droite
    if (ball.getPosition().x >= windowSize.x) {
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