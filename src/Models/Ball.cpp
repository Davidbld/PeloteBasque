#include "Ball.hpp"
#include "../GameConstants.hpp"
#include <random>

Ball::Ball(const sf::Vector2f& windowSize) {
    reset(windowSize);
}

void Ball::reset(const sf::Vector2f& windowSize) {
    // Position initiale près du mur de droite en tenant compte des marges
    float effectiveWidth = windowSize.x - 2 * MARGIN_X;
    float effectiveHeight = windowSize.y - 2 * MARGIN_Y;
    position.x = effectiveWidth * 0.75f; // à 75% de la largeur de la zone de jeu
    position.y = std::rand() % static_cast<int>(effectiveHeight - 400) + 200;
    speed = START_SPEED;
    direction = generateRandomDirection();
}

void Ball::update(float deltaTime) {
    position += direction * speed * deltaTime;
}

sf::Vector2f Ball::generateRandomDirection() const {
    sf::Vector2f newDir;
    newDir.x = -1.0f; // Toujours vers la gauche (vers la raquette)
    newDir.y = (static_cast<float>(std::rand()) / RAND_MAX) * 2.0f - 1.0f; // -1 à 1
    float length = std::sqrt(newDir.x * newDir.x + newDir.y * newDir.y);
    return newDir / length; // Normalisation
}

bool Ball::handleCollision(const sf::FloatRect& paddleBounds) {
    if (paddleBounds.intersects(sf::FloatRect(position.x, position.y, 10, 10))) {
        direction = calculateNewDirection(paddleBounds);
        accelerate();
        return true;
    }
    return false;
}

sf::Vector2f Ball::calculateNewDirection(const sf::FloatRect& paddleBounds) {
    sf::Vector2f newDir;
    
    // Inverse la direction horizontale
    newDir.x = (direction.x > 0) ? -1.0f : 1.0f;
    
    // Calcul de l'angle de rebond basé sur le point d'impact
    float relativeIntersectY = (position.y - paddleBounds.top) / paddleBounds.height;
    newDir.y = (relativeIntersectY - 0.5f) * 2.0f * MAX_Y_VECTOR;
    
    // Normalisation du vecteur
    float length = std::sqrt(newDir.x * newDir.x + newDir.y * newDir.y);
    return newDir / length;
}