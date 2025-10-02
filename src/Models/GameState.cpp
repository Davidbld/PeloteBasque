#include "GameState.hpp"
#include <algorithm>

void GameState::incrementScore() {
    currentScore++;
    maxScore = std::max(maxScore, currentScore);
}

void GameState::resetScore() {
    currentScore = 0;
}