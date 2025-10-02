#include "Player.hpp"
#include <algorithm>

Player::Player(const sf::Vector2f& startPos, float paddleHeight) 
    : position(startPos), height(paddleHeight) {
}

void Player::update(float deltaTime, float windowHeight) {
    // Limite le mouvement de la raquette dans la fenêtre
    position.y = std::clamp(position.y, height / 2, windowHeight - height / 2);
}

void Player::moveUp(float deltaTime) {
    position.y -= PADDLE_SPEED * deltaTime;
}

void Player::moveDown(float deltaTime) {
    position.y += PADDLE_SPEED * deltaTime;
}