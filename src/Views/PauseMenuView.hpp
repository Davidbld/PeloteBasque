#pragma once
#include <SFML/Graphics.hpp>

enum class PauseOption {
    CONTINUE,
    QUIT
};

class PauseMenuView {
public:
    PauseMenuView(sf::RenderWindow& window);
    void draw();
    PauseOption getClickedButton(const sf::Vector2i& mousePos) const;
    bool isMouseOverButton(const sf::Vector2i& mousePos) const;
    void updateCursor() const;

private:
    void loadFont();
    void setupButtons();
    bool isPointInButton(const sf::Vector2i& point, const sf::RectangleShape& button) const;

    sf::RenderWindow& window;
    sf::Font pixelFont;
    sf::RectangleShape continueButton;
    sf::RectangleShape quitButton;
    sf::Text continueText;
    sf::Text quitText;
    sf::RectangleShape pauseOverlay;
    
    static constexpr float BUTTON_WIDTH = 200.0f;
    static constexpr float BUTTON_HEIGHT = 60.0f;
    static constexpr float BUTTON_SPACING = 30.0f;
    static constexpr float CORNER_RADIUS = 8.0f;
};