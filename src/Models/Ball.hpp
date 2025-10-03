#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;
    static constexpr float START_SPEED = 500.0f;
    static constexpr float ACCELERATION = 50.0f;
    static constexpr float WALL_ACCELERATION = 25.0f;  // Accélération plus faible pour le rebond mural
    static constexpr float MAX_Y_VECTOR = 0.6f;

public:
    Ball(const sf::Vector2f& windowSize);
    void update(float deltaTime);
    void reset(const sf::Vector2f& windowSize);
    bool handleCollision(const sf::FloatRect& paddleBounds);
    
    // Getters
    const sf::Vector2f& getPosition() const { return position; }
    const sf::Vector2f& getDirection() const { return direction; }
    float getSpeed() const { return speed; }
    
    // Setters
    void setDirection(const sf::Vector2f& newDir) { direction = newDir; }
    void accelerate(bool isWall = false) { speed += (isWall ? WALL_ACCELERATION : ACCELERATION); }
    
    // SOLID: Single Responsibility - Ball only handles its physics and state
    sf::Vector2f calculateNewDirection(const sf::FloatRect& paddleBounds);
    sf::Vector2f generateRandomDirection() const;
};

#endif // BALL_HPP