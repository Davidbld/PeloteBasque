#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

class GameState {
private:
    int currentScore;
    int maxScore;

public:
    GameState() : currentScore(0), maxScore(0) {}
    
    // SOLID: Open/Closed Principle - Easy to extend scoring behavior
    virtual void incrementScore();
    void resetScore();
    
    // Getters
    int getCurrentScore() const { return currentScore; }
    int getMaxScore() const { return maxScore; }
};

#endif // GAME_STATE_HPP