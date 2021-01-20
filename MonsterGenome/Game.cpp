#include "Game.h"

Game::Game(RenderWindow &window) {
    state = true;
}

bool Game::GetState() const {
    return state;
}

void Game::SetState(bool NewState) {
    state = NewState;
}