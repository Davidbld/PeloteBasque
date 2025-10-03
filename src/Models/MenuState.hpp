#pragma once

enum class MenuOption {
    PLAY,
    QUIT
};

class MenuState {
public:
    MenuState();
    void selectNext();
    void selectPrevious();
    void setSelection(MenuOption option);
    MenuOption getCurrentSelection() const;

private:
    MenuOption currentSelection;
};