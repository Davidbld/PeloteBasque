#include "PauseMenuView.hpp"

PauseMenuView::PauseMenuView(sf::RenderWindow& window) : window(window) {
    loadFont();
    setupButtons();
}

void PauseMenuView::loadFont() {
    if (!pixelFont.loadFromFile("assets/fonts/pixel.ttf")) {
        pixelFont.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    }
}

void PauseMenuView::setupButtons() {
    // Setup overlay
    sf::Vector2f windowSize = static_cast<sf::Vector2f>(window.getSize());
    pauseOverlay.setSize(windowSize);
    pauseOverlay.setFillColor(sf::Color(0, 0, 0, 100)); // Plus transparent pour ressembler à la page d'accueil

    // Setup common button properties
    sf::Vector2f buttonSize(BUTTON_WIDTH, BUTTON_HEIGHT);
    
    // Center positions
    float centerX = windowSize.x / 2.0f;
    float centerY = windowSize.y / 2.0f;
    
    // Continue button
    continueButton.setSize(buttonSize);
    continueButton.setOrigin(BUTTON_WIDTH / 2.0f, BUTTON_HEIGHT / 2.0f);
    continueButton.setPosition(centerX, centerY - BUTTON_SPACING);
    continueButton.setFillColor(sf::Color::Black);
    continueButton.setOutlineColor(sf::Color::White);
    continueButton.setOutlineThickness(2.0f);
    
    // Quit button
    quitButton.setSize(buttonSize);
    quitButton.setOrigin(BUTTON_WIDTH / 2.0f, BUTTON_HEIGHT / 2.0f);
    quitButton.setPosition(centerX, centerY + BUTTON_SPACING);
    quitButton.setFillColor(sf::Color::Black);
    quitButton.setOutlineColor(sf::Color::White);
    quitButton.setOutlineThickness(2.0f);
    
    // Setup text
    continueText.setFont(pixelFont);
    continueText.setString("CONTINUER");
    continueText.setCharacterSize(24);
    continueText.setFillColor(sf::Color::White);
    continueText.setOrigin(continueText.getLocalBounds().width / 2.0f, 
                          continueText.getLocalBounds().height / 2.0f);
    continueText.setPosition(continueButton.getPosition());
    
    quitText.setFont(pixelFont);
    quitText.setString("QUITTER");
    quitText.setCharacterSize(24);
    quitText.setFillColor(sf::Color::White);
    quitText.setOrigin(quitText.getLocalBounds().width / 2.0f, 
                       quitText.getLocalBounds().height / 2.0f);
    quitText.setPosition(quitButton.getPosition());
}

void PauseMenuView::updateCursor() const {
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

void PauseMenuView::draw() {
    updateCursor();
    
    // Get mouse position for hover effect
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool mouseOverContinue = isPointInButton(mousePos, continueButton);
    bool mouseOverQuit = isPointInButton(mousePos, quitButton);
    
    // Set colors based on hover
    continueButton.setFillColor(mouseOverContinue ? sf::Color(50, 50, 50) : sf::Color::Black);
    quitButton.setFillColor(mouseOverQuit ? sf::Color(50, 50, 50) : sf::Color::Black);
    
    window.draw(pauseOverlay);
    window.draw(continueButton);
    window.draw(quitButton);
    window.draw(continueText);
    window.draw(quitText);
}

bool PauseMenuView::isPointInButton(const sf::Vector2i& point, const sf::RectangleShape& button) const {
    sf::FloatRect bounds = button.getGlobalBounds();
    return bounds.contains(static_cast<float>(point.x), static_cast<float>(point.y));
}

PauseOption PauseMenuView::getClickedButton(const sf::Vector2i& mousePos) const {
    if (isPointInButton(mousePos, continueButton)) {
        return PauseOption::CONTINUE;
    }
    if (isPointInButton(mousePos, quitButton)) {
        return PauseOption::QUIT;
    }
    return PauseOption::CONTINUE;
}

bool PauseMenuView::isMouseOverButton(const sf::Vector2i& mousePos) const {
    return isPointInButton(mousePos, continueButton) || isPointInButton(mousePos, quitButton);
}