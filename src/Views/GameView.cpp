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
    
    // Création du rectangle de la zone de jeu
    gameArea.setSize(sf::Vector2f(
        window.getSize().x - 2 * MARGIN_X,
        window.getSize().y - 2 * MARGIN_Y
    ));
    gameArea.setPosition(MARGIN_X, MARGIN_Y);
    gameArea.setFillColor(sf::Color::Transparent);
    gameArea.setOutlineColor(sf::Color(50, 50, 50));
    gameArea.setOutlineThickness(2.f);
    
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
    scoreText.setPosition(window.getSize().x / 2.f, MARGIN_Y / 2.f);  // Centré en haut
    scoreText.setStyle(sf::Text::Bold);  // Gras
    
    // Meilleur score
    maxScoreText.setFont(font);
    maxScoreText.setCharacterSize(24);
    maxScoreText.setFillColor(sf::Color(200, 200, 200));  // Légèrement plus discret
    maxScoreText.setPosition(
        window.getSize().x - 150.f - MARGIN_X, 
        MARGIN_TEXT
    );  // En haut à droite

    // Version
    versionText.setFont(font);
    versionText.setCharacterSize(16);  // Petit texte
    versionText.setFillColor(sf::Color(128, 128, 128));  // Gris
    versionText.setString(GAME_VERSION);
    versionText.setPosition(
        MARGIN_X + MARGIN_TEXT, 
        window.getSize().y - MARGIN_Y + MARGIN_TEXT
    );  // En bas à gauche
}

void GameView::render(const Player& player, const Ball& ball, const GameState& state, bool isPaused) {
    window.clear(sf::Color::Black);
    
    // Dessiner la zone de jeu
    window.draw(gameArea);
    
    // Mise à jour et rendu de la raquette
    paddleShape.setPosition(
        MARGIN_X + player.getPosition().x,
        MARGIN_Y + player.getPosition().y
    );
    window.draw(paddleShape);
    
    // Mise à jour et rendu de la balle
    ballShape.setPosition(
        MARGIN_X + ball.getPosition().x - ballShape.getRadius(),
        MARGIN_Y + ball.getPosition().y - ballShape.getRadius()
    );
    window.draw(ballShape);
    
    // Mise à jour des scores
    updateScoreDisplay(state);
    
    // Affichage des textes
    window.draw(scoreText);
    window.draw(maxScoreText);
    window.draw(versionText);
    
    // Ne pas afficher le menu pause ici, ce sera fait dans GameController
    // Supprimer window.display() pour éviter l'affichage prématuré
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