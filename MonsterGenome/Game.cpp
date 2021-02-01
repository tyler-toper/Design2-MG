#include "Game.h"

Game::Game() {
    //Invisible Borders
    Platforms* plat = new Platforms(1, 600, 800, 0);
    Platforms* plat1 = new Platforms(1, 600, 0, 0);
    //The ground
    Platforms* plat2 = new Platforms("../Images/platform.png", 0, 500);
    //Platforms in air
    Platforms* plat3 = new Platforms("../Images/platform2.png", 0, 350);
    Platforms* plat4 = new Platforms("../Images/platform2.png", 500, 450);
    Platforms* plat5 = new Platforms("../Images/platform2.png", 270, 200);
    Character* play = new Hero();
    Character* play2 = new Enemy();
    players.push_back(play);
    players.push_back(play2);
    borders.push_back(plat);
    borders.push_back(plat1);
    borders.push_back(plat2);
    borders.push_back(plat3);
    borders.push_back(plat4);
    borders.push_back(plat5);
    
}

void Game::PollGame(RenderWindow &window, Time& time) {
    for(int i = 0; i < players.size(); i++){
        players[i]->updatePosition(borders, projs, time, window);
    }
}

void Game::Draw(RenderWindow &window, Time& time){
    for(int i=0; i < projs.size(); i++){
        if(!projs[i]->update(borders, time)){
            window.draw(projs[i]->getSprite());
        }
        else{
            delete projs[i]; 
            projs.erase(projs.begin() + i--);
        }
    }

    for(int i = 0; i < borders.size(); i++){
        window.draw(borders[i]->getSprite());
    }
    for(int i = 0; i < players.size(); i++){
        window.draw(players[i]->getSprite());
    }
   
}
