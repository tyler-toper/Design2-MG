#include "../HeaderFiles/Game.h"
#include "../irrXML/irrXML.h"
using namespace irr;
using namespace io;

Game::Game(int lvl) {
    LoadLevel(lvl);
}

void Game::PollGame(RenderWindow &window, Time& time, GameState &state) {
    window.setKeyRepeatEnabled(false);
    Event event;
    while(window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if(event.type == Event::KeyPressed){
            if(event.key.code == Keyboard::Escape){
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
    playerView.setCenter(players[0]->getSprite().getPosition());
    playerView.setSize(window.getSize().x, window.getSize().y);
    window.setView(playerView);

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

    mapView.setCenter(players[0]->getSprite().getPosition().x, players[0]->getSprite().getPosition().y - 200);
    mapView.setSize(window.getSize().x*.25f, window.getSize().y*0.25f);
    mapView.zoom(6);
    mapView.setViewport(sf::FloatRect(0.01f, 0.01f, 0.2f, 0.2f));
    window.setView(mapView);
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

void Game::LoadLevel(int lvl){
    irr::io::IrrXMLReader *lvlFile;
    bool fileNotEmpty = false;
    std::string lvlFullName = "../../Assets/Levels/lvl" + std::to_string(lvl) + ".xml";
    lvlFile = createIrrXMLReader(lvlFullName.c_str());
    std::string textPath;
    float col, row, col2, row2, speed;

    while (lvlFile && lvlFile->read()){
        fileNotEmpty = true;
        switch (lvlFile->getNodeType()){
            case EXN_ELEMENT:
                if (!strcmp("level", lvlFile->getNodeName())){
                    std::string background = lvlFile->getAttributeValue("background");
                }
                if (!strcmp("hero", lvlFile->getNodeName())){
                    Character* tempChar = new Hero(lvlFile->getAttributeValueAsFloat("x"), lvlFile->getAttributeValueAsFloat("y"));
                    players.push_back(tempChar);
                }
                if (!strcmp("enemy", lvlFile->getNodeName())) {
                    Character *tempChar = new Enemy(lvlFile->getAttributeValueAsFloat("x"), lvlFile->getAttributeValueAsFloat("y"));
                    players.push_back(tempChar);
                }
                if (!strcmp("boundary", lvlFile->getNodeName())){
                    col = lvlFile->getAttributeValueAsFloat("x1");
                    col2 = lvlFile->getAttributeValueAsFloat("x2");
                    row = lvlFile->getAttributeValueAsFloat("y1");
                    row2 = lvlFile->getAttributeValueAsFloat("y2");
                    Platforms* tempPlat = new Platforms(col, row, col2, row2);
                    borders.push_back(tempPlat);
                }
                if (!strcmp("platform", lvlFile->getNodeName())){
                    textPath = lvlFile->getAttributeValue("sprite");
                    col = lvlFile->getAttributeValueAsFloat("x");
                    row = lvlFile->getAttributeValueAsFloat("y");
                    Platforms* tempPlat = new Platforms(textPath, col, row);
                    borders.push_back(tempPlat);
                }
                if (!strcmp("moveplatform", lvlFile->getNodeName())){
                    col = lvlFile->getAttributeValueAsFloat("x1");
                    col2 = lvlFile->getAttributeValueAsFloat("x2");
                    row = lvlFile->getAttributeValueAsFloat("y1");
                    row2 = lvlFile->getAttributeValueAsFloat("y2");
                    speed = lvlFile->getAttributeValueAsFloat("speed");
                    textPath = lvlFile->getAttributeValue("sprite");
                    Platforms* tempPlat = new MovePlatform(textPath, col, row, col2, row2, speed);
                    borders.push_back(tempPlat);
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
