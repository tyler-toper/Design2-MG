#include "Game.h"

Game::Game(RenderWindow &window) {
    state = false;

    //Invisible Borders
    Platforms* plat = new Platforms(1, 600, 800, 0);
    Platforms* plat1 = new Platforms(1, 600, 0, 0);
    //The ground
    Platforms* plat2 = new Platforms("../Images/platform.png", 0, 500);
    //Platforms in air
    Platforms* plat3 = new Platforms("../Images/platform2.png", 0, 350);
    Platforms* plat4 = new Platforms("../Images/platform2.png", 500, 400);
    Platforms* plat5 = new Platforms("../Images/platform2.png", 270, 200);
    borders.push_back(plat);
    borders.push_back(plat1);
    borders.push_back(plat2);
    borders.push_back(plat3);
    borders.push_back(plat4);
    borders.push_back(plat5);
}

void Game::PollGame(RenderWindow &window) {
    hero.updatePosition(borders);
}

void Game::Draw(RenderWindow &window){
    for(int i = 0; i < 5; i++){
        window.draw(borders[i]->getSprite());
    }
    window.draw(hero.getSprite());
}

bool Game::GetState() const {
    return state;
}

void Game::SetState(bool NewState) {
    state = NewState;
}