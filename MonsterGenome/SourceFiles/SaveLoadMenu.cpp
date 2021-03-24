#include "../HeaderFiles/SaveLoadMenu.h"

SaveLoadMenu::SaveLoadMenu(float width, float height, std::map<std::string, sf::Keyboard::Key>* controlMapping){
    this->controlMapping = controlMapping;
    selected = 0;
    entered = -1;

    xValue = 465;
    yValue[0] = 185;
    yValue[1] = 261;
    yValue[2] = 337;
    yValue[3] = 413;

    menu.loadFromFile("../../Assets/Backgrounds/SaveLoad/LoadMenu.png");
    menuSprite.setTexture(menu);

    saveButton.loadFromFile("../../Assets/Backgrounds/SaveLoad/SaveButtonSelected.png");
    saveButtonSprite.setTexture(saveButton);
    saveButtonSprite.setPosition(266, 543);

    loadButton.loadFromFile("../../Assets/Backgrounds/SaveLoad/LoadButtonSelected.png");
    loadButtonSprite.setTexture(loadButton);
    loadButtonSprite.setPosition(593, 543);

    enteredBox.loadFromFile("../../Assets/Backgrounds/SaveBoxEntered.png");
    enteredBoxSprite.setTexture(enteredBox);
    enteredBoxSprite.setPosition(2000, 2000);

    selectedBox.loadFromFile("../../Assets/Backgrounds/SaveBoxSelected.png");
    selectedBoxSprite.setTexture(selectedBox);

    background.loadFromFile("../../Assets/Backgrounds/Temp Background.png");
    backgroundSprite.setTexture(background);

    moveBuffer.loadFromFile("../../Assets/Audio/SFX/Interface Sounds/Audio/bong_001.ogg");
    moveSound.setBuffer(moveBuffer);
    moveSound.setVolume(35);

    errorBuffer.loadFromFile("../../Assets/Audio/SFX/Interface Sounds/Audio/error_008.ogg");
    errorSound.setBuffer(errorBuffer);
    errorSound.setVolume(40);

    confirmBuffer.loadFromFile("../../Assets/Audio/SFX/UI Audio/Audio/click2.ogg");
    confirmSound.setBuffer(confirmBuffer);
    confirmSound.setVolume(70);

}

void SaveLoadMenu::PollMenu(RenderWindow &window, GameState &state, Game &game){
    Event event;
    while(window.pollEvent(event)){
        if(event.type == Event::Closed){
            window.close();
        }
        if(event.type == Event::KeyPressed){
            auto pressed = event.key.code;
            std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;

            if(pressed == controls["Pause"]){
                if(GameState::GetPrev() == GameState::MENU){
                    state.SetState(GameState::MENU);
                }
                else{
                    state.SetState(GameState::PAUSE);
                }
                Reset();
            }
            if(pressed == controls["Jump"]){
                MoveUp();
            }
            if(pressed == controls["Crouch"]){
                MoveDown();
            }
            if(pressed == controls["Move Right"]){
                MoveRight();
            }
            if(pressed == controls["Move Left"]){
                MoveLeft();
            }
            // TODO: Create error pop up for invalid stuff
            else if(pressed == Keyboard::Return){
                if(selected == 4){
                    if(entered != -1){
                        SaveGame(game, entered);
                        state.SetState(GameState::PAUSE);
                        Reset();
                    }
                    else{
                        cout << "No save slot selected" << endl;
                    }

                }
                else if(selected == 5){
                    if(entered != -1){
                        LoadGame(game, entered);
                        state.SetState(GameState::LVL1);
                        Reset();
                    }
                    else{
                        cout << "No save slot selected" << endl;
                    }

                }
                else{
                    enteredBoxSprite.setPosition(xValue, yValue[selected]);
                    entered = selected;
                }
            }
        }
    }
}

void SaveLoadMenu::Draw(RenderWindow &window){
    window.draw(backgroundSprite);
    window.draw(menuSprite);

    if(selected == 4){
        window.draw(saveButtonSprite);
    }
    else if(selected == 5){
        window.draw(loadButtonSprite);
    }
    else{
        selectedBoxSprite.setPosition(xValue, yValue[selected]);
        window.draw(selectedBoxSprite);
    }

    window.draw(enteredBoxSprite);

}

void SaveLoadMenu::MoveUp(){
    if(selected == 5){
        moveSound.play();
        selected = 3;
    }
    else if(selected - 1 >= 0){
        moveSound.play();
        selected--;
    }
    else{
        errorSound.play();
    }
}

void SaveLoadMenu::MoveDown(){
    if(selected + 1 <= 4){
        moveSound.play();
        selected++;
    }
    else{
        errorSound.play();
    }
}

void SaveLoadMenu::MoveRight() {
    if(selected == 4){
        moveSound.play();
        selected++;
    }
    else{
        errorSound.play();
    }
}

void SaveLoadMenu::MoveLeft() {
    if(selected == 5){
        moveSound.play();
        selected--;
    }
    else{
        errorSound.play();
    }
}

void SaveLoadMenu::Reset() {
    selected = 0;
    entered = -1;
    enteredBoxSprite.setPosition(2000, 2000);
}

void SaveLoadMenu::SaveGame(Game &game, int slot){
    string saveSlot = "../../Saves/Slot " + to_string(slot) + "/save.xml";
    std::ofstream saveFile;
    saveFile.open(saveSlot);
    saveFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
    saveFile << "<save level=\"" + to_string(game.lvl) + "\">" << std::endl;

    saveFile << "\t<coords x=\"" + to_string(game.players[0]->sprite.getPosition().x) + "\" y=\"" + to_string(game.players[0]->sprite.getPosition().y) + "\"/>" << std::endl;
    saveFile << "\t<attrs name=\"" + game.players[0]->name + "\" health=\"" + to_string(game.players[0]->getHealth()) + "\" level=\"" + to_string(game.players[0]->level) + "\" armor=\"" + to_string(game.players[0]->armor) + "\" strength=\"" + to_string(game.players[0]->strength) + "\" vitality=\"" + to_string(game.players[0]->vitality) + "\" exp=\"" + to_string(game.players[0]->experience) + "\"/>" << std::endl;

    saveFile << "</save>" << std::endl;
    saveFile.close();
}

void SaveLoadMenu::LoadGame(Game &game, int slot) {
    irr::io::IrrXMLReader *saveFile;
    bool fileNotEmpty = false;
    std::string saveSlot = "../../Saves/Slot " + to_string(slot) + "/save.xml";
    saveFile = irr::io::createIrrXMLReader(saveSlot.c_str());
    std::string name;
    int level;
    game.mod = new HeroMod(game.controlMapping);

    game.projs.clear();
    game.players.clear();
    game.borders.clear();

    while (saveFile && saveFile->read()) {
        fileNotEmpty = true;
        switch (saveFile->getNodeType()) {
            case irr::io::EXN_ELEMENT:
                if (!strcmp("save", saveFile->getNodeName())) {
                    level = saveFile->getAttributeValueAsInt("level");
                }
                if (!strcmp("coords", saveFile->getNodeName())) {
                    Character *hero = new Hero(controlMapping, &game.borders, &game.projs, &game.players,
                                               saveFile->getAttributeValueAsFloat("x"),
                                               saveFile->getAttributeValueAsFloat("y"));
                    game.players.push_back(hero);
                }
                if (!strcmp("attrs", saveFile->getNodeName())) {
                    game.players[0]->name = saveFile->getAttributeValue("name");
                    game.players[0]->health = saveFile->getAttributeValueAsInt("health");
                    game.players[0]->level = saveFile->getAttributeValueAsInt("level");
                    game.players[0]->armor = saveFile->getAttributeValueAsInt("armor");
                    game.players[0]->strength = saveFile->getAttributeValueAsInt("strength");
                    game.players[0]->vitality = saveFile->getAttributeValueAsInt("vitality");
                    game.players[0]->experience = saveFile->getAttributeValueAsInt("exp");
                }
                break;
            default:
                break;
        }
    }
    if (!fileNotEmpty) {
        std::cerr << "Can't read level file " << saveSlot << std::endl;
    }
    delete saveFile;
    saveFile = NULL;
    game.LFS = true;

    game.LoadLevel(level);
}