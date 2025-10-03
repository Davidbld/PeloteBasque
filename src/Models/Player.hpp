#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Vector2f position;
    float speed;
    float height;
    static constexpr float PADDLE_SPEED = 600.0f;

public:
    Player(const sf::Vector2f& startPos, float paddleHeight);
    void update(float deltaTime, float windowHeight);
    
    // Getters
    const sf::Vector2f& getPosition() const { return position; }
    float getHeight() const { return height; }
    
    // SOLID: Interface Segregation - Only expose what's needed
    void moveUp(float deltaTime);
    void moveDown(float deltaTime);
};

#endif // PLAYER_HPP