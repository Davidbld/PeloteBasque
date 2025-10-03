#pragma once
#include <SFML/Graphics.hpp>
#include "../Models/MenuState.hpp"

class MenuView {
public:
    MenuView(sf::RenderWindow& window);
    void draw(const MenuState& state);
    MenuOption getClickedButton(const sf::Vector2i& mousePos) const;
    bool isMouseOverButton(const sf::Vector2i& mousePos) const;
    void updateCursor() const;

private:
    void loadFont();
    void setupButtons();
    bool isPointInButton(const sf::Vector2i& point, const sf::RectangleShape& button) const;

    sf::RenderWindow& window;
    sf::Font pixelFont;
    sf::RectangleShape playButton;
    sf::RectangleShape quitButton;
    sf::Text playText;
    sf::Text quitText;
    static constexpr float BUTTON_WIDTH = 200.0f;
    static constexpr float BUTTON_HEIGHT = 60.0f;
    static constexpr float BUTTON_SPACING = 30.0f;
    static constexpr float CORNER_RADIUS = 8.0f;
};