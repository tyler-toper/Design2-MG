#include "../HeaderFiles/StartMenu.h"


StartMenu::StartMenu(float width, float height, std::map<std::string, sf::Keyboard::Key>* controlMapping){
    this->controlMapping = controlMapping;
    selected = 0;
    entered = -1;

    font.loadFromFile("../../Assets/Fonts/PixelFont.ttf");
    error.setString("Error: No save slot selected!");
    error.setFont(font);
    error.setFillColor(Color::Red);
    error.setCharacterSize(45);
    FloatRect errorBox = error.getGlobalBounds();
    float errorOffset = errorBox.width / 2;
    error.setPosition((1024 / 2) - errorOffset, 668);
    errorFlag = false;

    xValue = 465;
    yValue[0] = 185;
    yValue[1] = 261;
    yValue[2] = 337;
    yValue[3] = 413;

    menu.loadFromFile("../../Assets/Backgrounds/StartScreen/StartMenu.png");
    menuSprite.setTexture(menu);

    newButton.loadFromFile("../../Assets/Backgrounds/StartScreen/NewGameButtonSelected.png");
    newButtonSprite.setTexture(newButton);
    newButtonSprite.setPosition(254, 542);

    startButton.loadFromFile("../../Assets/Backgrounds/StartScreen/StartButtonSelected.png");
    startButtonSprite.setTexture(startButton);
    startButtonSprite.setPosition(585, 542);

    enteredBox.loadFromFile("../../Assets/Backgrounds/SaveBoxEntered.png");
    enteredBoxSprite.setTexture(enteredBox);
    enteredBoxSprite.setPosition(2000, 2000);

    selectedBox.loadFromFile("../../Assets/Backgrounds/SaveBoxSelected.png");
    selectedBoxSprite.setTexture(selectedBox);
    selectedBoxSprite.setPosition(xValue, yValue[0]);

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

void StartMenu::PollMenu(RenderWindow &window, GameState &state, Game &game){
    Event event;
    while(window.pollEvent(event)){
        if(event.type == Event::Closed){
            window.close();
        }
        if(event.type == Event::KeyPressed){
            auto pressed = event.key.code;
            std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;

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
            if(pressed == controls["Pause"]){
                state.SetState(GameState::MENU);
                Reset();
            }
            else if(pressed == Keyboard::Return){
                if(selected == 4){
                    LoadGame(game, selected);
                    state.SetState(GameState::LVL1);
                    Reset();
                }
                else if(selected == 5){
                    if(entered != -1){
                        LoadGame(game, entered);
                        state.SetState(GameState::LVL1);
                        state.SetPlaying(true);
                        Reset();
                    }
                    else{
                        errorFlag = true;
                    }
                }

                else{
                    enteredBoxSprite.setPosition(xValue, yValue[selected]);
                    entered = selected;
                    errorFlag = false;
                }
            }
        }
    }
}

void StartMenu::Draw(RenderWindow &window){
    window.draw(backgroundSprite);
    window.draw(menuSprite);

    if(selected == 4){
        window.draw(newButtonSprite);
    }
    else if(selected == 5){
        window.draw(startButtonSprite);
    }
    else{
        window.draw(selectedBoxSprite);
        selectedBoxSprite.setPosition(xValue, yValue[selected]);
    }
    window.draw(enteredBoxSprite);

    if(errorFlag){
        window.draw(error);
    }
}

void StartMenu::MoveUp(){
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

void StartMenu::MoveDown(){
    if(selected + 1 <= 4){
        moveSound.play();
        selected++;
    }
    else{
        errorSound.play();
    }
}

void StartMenu::MoveLeft() {
    if(selected == 5){
        moveSound.play();
        selected--;
    }
    else{
        errorSound.play();
    }
}

void StartMenu::MoveRight() {
    if(selected == 4){
        moveSound.play();
        selected++;
    }
    else{
        errorSound.play();
    }
}

void StartMenu::Reset() {
    selected = 0;
    entered = -1;
    enteredBoxSprite.setPosition(2000, 2000);
}

void StartMenu::LoadGame(Game &game, int slot) {
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
        std::cerr << "Can't read save file " << saveSlot << std::endl;
    }
    delete saveFile;
    saveFile = NULL;
    game.LFS = true;

    game.LoadLevel(level);
}