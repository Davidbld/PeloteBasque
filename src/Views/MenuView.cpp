#include "MenuView.hpp"

MenuView::MenuView(sf::RenderWindow& window) : window(window) {
    loadFont();
    setupButtons();
}

void MenuView::loadFont() {
    // Note: You'll need to add a pixel font file to your assets
    if (!pixelFont.loadFromFile("assets/fonts/pixel.ttf")) {
        // Fallback to default font if pixel font is not available
        pixelFont.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    }
}

void MenuView::setupButtons() {
    // Setup common button properties
    sf::Vector2f buttonSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    
    // Center positions
    sf::Vector2f windowSize = static_cast<sf::Vector2f>(window.getSize());
    float centerX = windowSize.x / 2.0f;
    float centerY = windowSize.y / 2.0f;
    
    // Play button
    playButton.setSize(buttonSize);
    playButton.setOrigin(BUTTON_WIDTH / 2.0f, BUTTON_HEIGHT / 2.0f);
    playButton.setPosition(centerX, centerY - BUTTON_SPACING);
    playButton.setFillColor(sf::Color::Black);
    playButton.setOutlineColor(sf::Color::White);
    playButton.setOutlineThickness(2.0f);
    
    // Quit button
    quitButton.setSize(buttonSize);
    quitButton.setOrigin(BUTTON_WIDTH / 2.0f, BUTTON_HEIGHT / 2.0f);
    quitButton.setPosition(centerX, centerY + BUTTON_SPACING);
    quitButton.setFillColor(sf::Color::Black);
    quitButton.setOutlineColor(sf::Color::White);
    quitButton.setOutlineThickness(2.0f);
    
    // Setup text
    playText.setFont(pixelFont);
    playText.setString("JOUER");
    playText.setCharacterSize(24);
    playText.setFillColor(sf::Color::White);
    playText.setOrigin(playText.getLocalBounds().width / 2.0f, 
                       playText.getLocalBounds().height / 2.0f);
    playText.setPosition(playButton.getPosition());
    
    quitText.setFont(pixelFont);
    quitText.setString("QUITTER");
    quitText.setCharacterSize(24);
    quitText.setFillColor(sf::Color::White);
    quitText.setOrigin(quitText.getLocalBounds().width / 2.0f, 
                       quitText.getLocalBounds().height / 2.0f);
    quitText.setPosition(quitButton.getPosition());
}

void MenuView::updateCursor() const {
    static sf::Cursor handCursor;
    static sf::Cursor arrowCursor;
    static bool cursorsLoaded = false;
    
    if (!cursorsLoaded) {
        handCursor.loadFromSystem(sf::Cursor::Hand);
        arrowCursor.loadFromSystem(sf::Cursor::Arrow);
        cursorsLoaded = true;
    }
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (isMouseOverButton(mousePos)) {
        window.setMouseCursor(handCursor);
    } else {
        window.setMouseCursor(arrowCursor);
    }
}

void MenuView::draw(const MenuState& state) {
    // Update cursor based on mouse position
    updateCursor();
    
    // Update button colors based on selection
    MenuOption currentSelection = state.getCurrentSelection();
    
    // Get mouse position for hover effect
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool mouseOverPlay = isPointInButton(mousePos, playButton);
    bool mouseOverQuit = isPointInButton(mousePos, quitButton);
    
    // Set colors based on selection and hover
    if (currentSelection == MenuOption::PLAY || mouseOverPlay) {
        playButton.setFillColor(sf::Color(50, 50, 50));
    } else {
        playButton.setFillColor(sf::Color::Black);
    }
    
    if (currentSelection == MenuOption::QUIT || mouseOverQuit) {
        quitButton.setFillColor(sf::Color(50, 50, 50));
    } else {
        quitButton.setFillColor(sf::Color::Black);
    }
    
    window.draw(playButton);
    window.draw(quitButton);
    window.draw(playText);
    window.draw(quitText);
}

bool MenuView::isPointInButton(const sf::Vector2i& point, const sf::RectangleShape& button) const {
    sf::FloatRect bounds = button.getGlobalBounds();
    return bounds.contains(static_cast<float>(point.x), static_cast<float>(point.y));
}

MenuOption MenuView::getClickedButton(const sf::Vector2i& mousePos) const {
    if (isPointInButton(mousePos, playButton)) {
        return MenuOption::PLAY;
    }
    if (isPointInButton(mousePos, quitButton)) {
        return MenuOption::QUIT;
    }
    return MenuOption::PLAY; // Default to PLAY if clicked outside buttons
}

bool MenuView::isMouseOverButton(const sf::Vector2i& mousePos) const {
    return isPointInButton(mousePos, playButton) || isPointInButton(mousePos, quitButton);
}