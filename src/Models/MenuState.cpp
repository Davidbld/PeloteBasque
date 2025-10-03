#include "MenuState.hpp"

MenuState::MenuState() : currentSelection(MenuOption::PLAY) {}

void MenuState::selectNext() {
    currentSelection = (currentSelection == MenuOption::PLAY) ? MenuOption::QUIT : MenuOption::PLAY;
}

void MenuState::selectPrevious() {
    selectNext(); // Same as next since we only have two options
}

MenuOption MenuState::getCurrentSelection() const {
    return currentSelection;
}

void MenuState::setSelection(MenuOption option) {
    currentSelection = option;
}