#include "GameView.hpp"
#include <sstream>

GameView::GameView(sf::RenderWindow& win) : window(win) {
    initialize();
}

void GameView::initialize() {
    // Configuration de la raquette
    paddleShape.setSize(sf::Vector2f(20, 100));
    paddleShape.setFillColor(sf::Color::White);
    paddleShape.setOrigin(10, 50); // Centre l'origine de la raquette
    
    // Configuration de la balle
    ballShape.setRadius(5);
    ballShape.setFillColor(sf::Color::White);
    
    // Chargement de la police et configuration du texte
    if (!font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf")) {
        // Si la police Liberation n'est pas trouvée, essayons d'autres polices système
        if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            if (!font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf")) {
                throw std::runtime_error("Impossible de charger une police système");
            }
        }
    }
    setupText();
}

void GameView::setupText() {
    // Score actuel
    scoreText.setFont(font);
    scoreText.setCharacterSize(48);  // Plus grand
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(window.getSize().x / 2.f, 20.f);  // Centré en haut
    scoreText.setStyle(sf::Text::Bold);  // Gras
    
    // Meilleur score
    maxScoreText.setFont(font);
    maxScoreText.setCharacterSize(24);
    maxScoreText.setFillColor(sf::Color(200, 200, 200));  // Légèrement plus discret
    maxScoreText.setPosition(window.getSize().x - 150.f, 10.f);  // En haut à droite
}

void GameView::render(const Player& player, const Ball& ball, const GameState& state, bool isPaused) {
    window.clear(sf::Color::Black);
    
    // Mise à jour et rendu de la raquette
    paddleShape.setPosition(player.getPosition());
    window.draw(paddleShape);
    
    // Mise à jour et rendu de la balle
    ballShape.setPosition(ball.getPosition().x - ballShape.getRadius(),
                         ball.getPosition().y - ballShape.getRadius());
    window.draw(ballShape);
    
    // Mise à jour des scores
    updateScoreDisplay(state);
    
    // Affichage des textes
    window.draw(scoreText);
    window.draw(maxScoreText);
    
    // Affichage du menu pause si le jeu est en pause
    if (isPaused) {
        sf::Text pauseText;
        pauseText.setFont(font);
        pauseText.setCharacterSize(40);
        pauseText.setFillColor(sf::Color::White);
        pauseText.setString("PAUSE");
        
        // Centrer le texte
        sf::FloatRect textRect = pauseText.getLocalBounds();
        pauseText.setOrigin(textRect.width/2, textRect.height/2);
        pauseText.setPosition(window.getSize().x/2.f, window.getSize().y/2.f);
        
        // Fond semi-transparent
        sf::RectangleShape overlay(sf::Vector2f(window.getSize()));
        overlay.setFillColor(sf::Color(0, 0, 0, 128));
        
        window.draw(overlay);
        window.draw(pauseText);
    }
    
    window.display();
}

void GameView::updateScoreDisplay(const GameState& state) {
    std::stringstream ss;
    ss << state.getCurrentScore();  // Juste le nombre
    scoreText.setString(ss.str());
    
    // Centre le score
    sf::FloatRect textRect = scoreText.getLocalBounds();
    scoreText.setOrigin(textRect.width / 2.f, textRect.height / 2.f);
    
    ss.str("");
    ss << "Meilleur: " << state.getMaxScore();
    maxScoreText.setString(ss.str());
}