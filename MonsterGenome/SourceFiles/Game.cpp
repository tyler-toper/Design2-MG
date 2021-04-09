#include "../HeaderFiles/Game.h"
#include "../irrXML/irrXML.h"

Game::Game(std::map<std::string, sf::Keyboard::Key>* controlMapping, int lvl) {
    this->controlMapping = controlMapping;
    this->lvl = lvl;
    mod = new HeroMod(controlMapping);
    LoadLevel(lvl, 1);



    HUD.loadFromFile("../../Assets/Backgrounds/HUD.png");
    HUDSprite.setTexture(HUD);

    healthBar.setPosition(95, 735);
    healthBar.setFillColor(Color::Red);
}

void Game::PollGame(RenderWindow &window, Time& time, GameState &state, View &playerView) {
    if(this->modify){
        /// TODO: Check which condition was meet
        // All enemies are dead
        if(players[0]->getCheckPoint()){
            if(mod->PollMenu(window, state, modify, players[0])){
                players[0]->resetCheck();
                this->modify = false;
            }
        }
        else{
            players[0]->setHealth(players[0]->getMaxHealth());
            players[0]->getSprite().setPosition(players[0]->getReset());
            this->modify = false;
        }
    }
    else{
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

        // Update Platform Positions
        for(int i = 0; i < borders.size(); i++){
            borders[i]->update(time);
        }

        // Update Players and Enemies
        for(int i = 0; i < players.size(); i++){
            players[i]->updatePosition(time, window, playerView);
        }

        // Delete Enemies if dead
        for(int i = 1; i < players.size(); i++){
            if(players[i]->getHealth() <= 0){
                delete players[i];
                players.erase(players.begin() + i--);
            }
        }

        // Update player health bar
        // Health bar's max size is 218 pixels
        int maxHealth = players[0]->getMaxHealth();
        int currentHealth = players[0]->getHealth();
        healthBar.setSize(Vector2f((218.0 / maxHealth) * currentHealth, 11));
    }
}


void Game::Draw(RenderWindow &window, Time& time, View &playerView, View &mapView){
    if(this->modify){
        mod->Draw(window);
    }
    else {
        playerView.setCenter(players[0]->getSprite().getPosition());
        playerView.setSize(window.getSize().x, window.getSize().y);
        playerView.zoom(0.5);
        window.setView(playerView);
        window.draw(this->backgroundS);
        for (int i = 0; i < projs.size(); i++) {
            if (!projs[i]->update(borders, time)) {
                window.draw(projs[i]->getSprite());
            } else {
                delete projs[i];
                projs.erase(projs.begin() + i--);
            }
        }
        for (int i = 0; i < borders.size(); i++) {
            window.draw(borders[i]->getSprite());
        }
        for (int i = 0; i < players.size(); i++) {
            window.draw(players[i]->getSprite());
        }

        mapView.setCenter(players[0]->getSprite().getPosition().x, players[0]->getSprite().getPosition().y);
        mapView.setSize(window.getSize().x * .4f, window.getSize().y * 0.25f);
        mapView.zoom(2);
        mapView.setViewport(sf::FloatRect(0.01f, 0.01f, 0.4f, 0.2f));
        window.setView(mapView);
        window.draw(this->backgroundS);
        for (int i = 0; i < projs.size(); i++) {
            if (!projs[i]->update(borders, time)) {
                window.draw(projs[i]->getSprite());
            } else {
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

        if (players[0]->getHealth() <= 0 || players[0]->getCheckPoint()) {
            modify = true;
            if(players[0]->getCheckPoint()){
                mod->randomize();
                window.setView(window.getDefaultView());
            }
            else if(players[0]->getHealth() <= 0) {
                dynamic_cast<Hero *>(players[0])->setRespawnTimer(2.f);
            }
        }
        dynamic_cast<Hero *>(players[0])->equipWeapon(window, playerView);
        dynamic_cast<Hero *>(players[0])->animWeapon(window, playerView);

        window.setView(window.getDefaultView());
        window.draw(HUDSprite);
        window.draw(healthBar);

        if(dynamic_cast<Hero *>(players[0])->isRespawning()) {
            Font font;
            font.loadFromFile("../../Assets/Fonts/PixelFont.ttf");
            Text message;
            message.setString("You Died!");
            message.setFont(font);
            message.setFillColor(Color::Red);
            message.setCharacterSize(90);
            message.setPosition(350, 300);
            window.draw(message);
        }
    }


}

void Game::LoadLevel(int lvl, int LoadCase){
    /*
     * For LoadCase
     * 1: Brand new game. New hero at level file coordinates.
     * 2: Load from save. Load hero from save at save file coordinates.
     * 3: Player death. Reset player health and set position to checkpoint.
     * 4: Different level. Don't touch player attributes, load other level and place hero at level file coordinates or level checkpoint coordinates.
    */
    irr::io::IrrXMLReader *lvlFile;
    bool fileNotEmpty = false;
    std::string lvlFullName = "../../Assets/Levels/lvl" + std::to_string(lvl) + ".xml";
    lvlFile = irr::io::createIrrXMLReader(lvlFullName.c_str());
    std::string textPath;
    float col, row, col2, row2, speed;
    Character* tempChar;
    Platforms* tempPlat;
    this->mod = new HeroMod(controlMapping);

    if(LoadCase > 1){
        this->players.erase(players.begin()+1, players.end());
    }
    this->borders.clear();
    this->projs.clear();

    while (lvlFile && lvlFile->read()){
        fileNotEmpty = true;
        switch (lvlFile->getNodeType()){
            case irr::io::EXN_ELEMENT:
                if (!strcmp("level", lvlFile->getNodeName())){
                    std::string background = lvlFile->getAttributeValue("background");
                    background = "../../Assets/" + background;
                    this->backgroundT.loadFromFile(background);
                    this->backgroundS.setTexture(this->backgroundT);
                }
                if (!strcmp("hero", lvlFile->getNodeName())){
                    switch(LoadCase){
                        case 1:
                            tempChar = new Hero(controlMapping, &borders, &projs, &players, lvlFile->getAttributeValueAsFloat("x"), lvlFile->getAttributeValueAsFloat("y") - 10);
                            this->players.push_back(tempChar);
                            break;
                        case 2:
                            //Everything for hero is done in the save/load and start menus.
                            break;
                        case 3:
                            /// Reset player health and set position to checkpoint coordinates.
                            break;
                        case 4:
                            this->players[0]->getSprite().setPosition(lvlFile->getAttributeValueAsFloat("x"), lvlFile->getAttributeValueAsFloat("y"));
                            break;
                        default:
                            std::cout << "You messed up somewhere." << std::endl;
                    }
                }
                if (!strcmp("enemy", lvlFile->getNodeName())) {
                    string type = lvlFile->getAttributeValue("type");
                    if(type == "Fighter") {
                        tempChar = new Fighter(&borders, &projs, &players, lvlFile->getAttributeValueAsFloat("x"),
                                               lvlFile->getAttributeValueAsFloat("y"));
                    }
                    if(type == "Wanderer") {
                        tempChar = new Wanderer(&borders, &projs, &players, lvlFile->getAttributeValueAsFloat("x"),
                                               lvlFile->getAttributeValueAsFloat("y"));
                    }

                    this->players.push_back(tempChar);
                }
                if (!strcmp("hBoundary", lvlFile->getNodeName())){
                    col = lvlFile->getAttributeValueAsFloat("x1");
                    col2 = lvlFile->getAttributeValueAsFloat("x2");
                    row = lvlFile->getAttributeValueAsFloat("y1");
                    row2 = lvlFile->getAttributeValueAsFloat("y2");
                    tempPlat = new Platforms(col, row, col2, row2, true);
                    this->borders.push_back(tempPlat);
                }
                if (!strcmp("vBoundary", lvlFile->getNodeName())){
                    col = lvlFile->getAttributeValueAsFloat("x1");
                    col2 = lvlFile->getAttributeValueAsFloat("x2");
                    row = lvlFile->getAttributeValueAsFloat("y1");
                    row2 = lvlFile->getAttributeValueAsFloat("y2");
                    tempPlat = new Platforms(col, row, col2, row2, false);
                    this->borders.push_back(tempPlat);
                }
                if (!strcmp("platform", lvlFile->getNodeName())){
                    textPath = lvlFile->getAttributeValue("sprite");
                    col = lvlFile->getAttributeValueAsFloat("x");
                    row = lvlFile->getAttributeValueAsFloat("y");
                    tempPlat = new Platforms(textPath, col, row);
                    this->borders.push_back(tempPlat);
                }
                if (!strcmp("moveplatform", lvlFile->getNodeName())){
                    col = lvlFile->getAttributeValueAsFloat("x1");
                    col2 = lvlFile->getAttributeValueAsFloat("x2");
                    row = lvlFile->getAttributeValueAsFloat("y1");
                    row2 = lvlFile->getAttributeValueAsFloat("y2");
                    speed = lvlFile->getAttributeValueAsFloat("speed");
                    textPath = lvlFile->getAttributeValue("sprite");
                    tempPlat = new MovePlatform(textPath, col, row, col2, row2, speed);
                    this->borders.push_back(tempPlat);
                }
                if (!strcmp("checkpoint", lvlFile->getNodeName())){
                    col = lvlFile->getAttributeValueAsFloat("x");
                    row = lvlFile->getAttributeValueAsFloat("y");
                    textPath = lvlFile->getAttributeValue("path");
                    tempPlat = new Checkpoint(textPath, col, row);
                    this->borders.push_back(tempPlat);
                }
                break;
            default:
                break;
        }
    }
    if (!fileNotEmpty){
        std::cerr << "Can't read level file " << lvlFullName << std::endl;
    }
    delete lvlFile;
    lvlFile = NULL;
}

