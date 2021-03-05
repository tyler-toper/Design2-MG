#include "../HeaderFiles/Game.h"

Game::Game(std::map<std::string, sf::Keyboard::Key>* controlMapping) {
    this->controlMapping = controlMapping;

    // Invisible Borders
    Platforms* plat = new Platforms(1, 600, 800, 0);
    Platforms* plat1 = new Platforms(1, 600, 0, 0);
    // The ground
    Platforms* plat2 = new Platforms("../Images/platform.png", 0, 500);
    // Platforms in air
    Platforms* plat3 = new Platforms("../Images/platform2.png", 250, 375);
    //Moving
    Platforms* plat6 = new MovePlatform("../Images/platform2.png", 400, 100, 500, 500, 100);
    Platforms* plat7 = new MovePlatform("../Images/platform2.png", 0, 500, 0, 100, 100);

    Character* play2 = new Enemy();
    Character* play = new Hero(controlMapping);

    HUD = new Interface("HUD");

    players.push_back(play);
    players.push_back(play2);

    borders.push_back(plat);
    borders.push_back(plat1);
    borders.push_back(plat2);
    borders.push_back(plat3);
    borders.push_back(plat6);
    borders.push_back(plat7);
}

void Game::PollGame(RenderWindow &window, Time& time, GameState &state) {
    window.setKeyRepeatEnabled(false);
    Event event;
    while(window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if(event.type == Event::KeyPressed){
            // Needs to dereference controlMapping in order to read map
            std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;
            // Pass event into settings and compare its output
            if(event.key.code == controls["Pause"]){
                state.Pause();
                state.SetState(GameState::PAUSE);
            }
        }
    }
    for(int i = 0; i < borders.size(); i++){
        borders[i]->update(time);
    }
    for(int i = 0; i < players.size(); i++){
        players[i]->updatePosition(borders, projs, players, time, window);
    }
}


void Game::Draw(RenderWindow &window, Time& time, View &playerView, View &mapView){
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

    Sprite resized = HUD->getSprite();          //This block of code draws the HUD for the player
    resized.setPosition(players[0]->getSprite().getPosition().x-(window.getSize().x/2), players[0]->getSprite().getPosition().y-(window.getSize().y/2));        //More flexible for resizing
    window.draw(resized);

    playerView.setCenter(players[0]->getSprite().getPosition());
    playerView.setSize(window.getSize().x, window.getSize().y);
    window.setView(playerView);
}