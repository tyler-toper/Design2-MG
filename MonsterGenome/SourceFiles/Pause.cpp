#include "../HeaderFiles/Pause.h"
#include "../HeaderFiles/Character.h"
#include <fstream>


Pause::Pause(float width, float height,  std::map<std::string, sf::Keyboard::Key>* controlMapping) {
    this->controlMapping = controlMapping;

    font.loadFromFile(pixelFont);
    selected = 0;

    title.setString("PAUSED");
    title.setFont(font);
    title.setFillColor(Color::Yellow);
    title.setCharacterSize(100);
    FloatRect titleBox = title.getGlobalBounds();
    float titleOffset = titleBox.width / 2;
    title.setPosition((width / 2) - titleOffset, 0);

    text[0].setString("Resume");
    text[1].setString("Save");
    text[2].setString("Load");
    text[3].setString("Settings");
    text[4].setString("Quit to Main Menu");

    for(int i = 0; i < PauseOptions; i++){
        text[i].setFont(font);
        text[i].setFillColor(Color::Yellow);
        text[i].setCharacterSize(50);

        FloatRect box = text[i].getGlobalBounds();
        float offset = box.width / 2;
        text[i].setPosition((width / 2) - offset, (height / (PauseOptions + 1) * (i + 1)));
    }

    text[selected].setFillColor(Color::Red);
    text[selected].setStyle(Text::Underlined);

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


void Pause::PollMenu(RenderWindow &window, GameState &state, Game &game) {
    Event event;
    while(window.pollEvent(event)){
        if(event.type == Event::Closed){
            window.close();
        }
        if (event.type == Event::KeyPressed){
            auto pressed = event.key.code;
            // Needs to dereference controlMapping in order to read map
            std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;

            if(pressed == controls["Pause"]){
                state.SetState(GameState::PLAY);
                state.Resume();
            }
            if (pressed == controls["Jump"]) {
                MoveUp();
            }
            if(pressed == controls["Crouch"]){
                MoveDown();
            }
            if(pressed == Keyboard::Return){
                confirmSound.play();
                if(selected == 0){
                    state.SetState(GameState::PLAY);
                    state.Resume();
                }
                else if(selected == 1){
                    // TODO: Connect save system
                    SaveGame(game, 1);
                }
                else if(selected == 2){
                    // TODO: Connect load system
                    LoadGame(game, 1);
                }
                else if(selected == 3){
                    state.SetState(GameState::SETTINGS);
                }
                else if(selected == 4){
                    state.SetPlaying(false);
                    state.SetState(GameState::MENU);
                }
            }
        }
    }
}

void Pause::Draw(RenderWindow &window){
    Texture texture;
    texture.loadFromFile("../../Assets/Backgrounds/Temp Background.png");
    Sprite background(texture);
    background.setPosition(0, 0);
    window.draw(background);

    window.draw(title);

    for(int i = 0; i < PauseOptions; i++){
        window.draw(text[i]);
    }
}

void Pause::MoveDown(){
    if(selected + 1 < PauseOptions){
        moveSound.play();
        text[selected].setFillColor(Color::Yellow);
        text[selected].setStyle(Text::Regular);
        selected++;
        text[selected].setFillColor(Color::Red);
        text[selected].setStyle(Text::Underlined);
    }
    else{
        errorSound.play();
    }
}

void Pause::MoveUp(){
    if(selected - 1 >= 0){
        moveSound.play();
        text[selected].setFillColor(Color::Yellow);
        text[selected].setStyle(Text::Regular);
        selected--;
        text[selected].setFillColor(Color::Red);
        text[selected].setStyle(Text::Underlined);
    }
    else{
        errorSound.play();
    }
}

void Pause::SaveGame(Game &game, int slot){
    int temp1, temp2;
    float temp3, temp4;
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

void Pause::LoadGame(Game &game, int slot){
    irr::io::IrrXMLReader *saveFile;
    bool fileNotEmpty = false;
    std::string saveSlot = "../../Saves/Slot " + to_string(slot) + "/save.xml";
    saveFile = irr::io::createIrrXMLReader(saveSlot.c_str());
    std::string name;
    float col, row, col2, row2, speed, xCoord, yCoord;
    int level;
    game.mod = new HeroMod(game.controlMapping);

    game.projs.clear();
    game.players.clear();
    game.borders.clear();

    while (saveFile && saveFile->read()){
        fileNotEmpty = true;
        switch (saveFile->getNodeType()){
            case irr::io::EXN_ELEMENT:
                if (!strcmp("save", saveFile->getNodeName())){
                    level = saveFile->getAttributeValueAsInt("level");
                }
                if (!strcmp("coords", saveFile->getNodeName())){
                    Character* hero = new Hero(controlMapping, &game.borders, &game.projs, &game.players, saveFile->getAttributeValueAsFloat("x"), saveFile->getAttributeValueAsFloat("y"));
                    game.players.push_back(hero);
                }
                if (!strcmp("attrs", saveFile->getNodeName())) {
                    game.players[0]->name =  saveFile->getAttributeValue("name");
                    game.players[0]->health = saveFile->getAttributeValueAsInt("health");
                    game.players[0]->level =  saveFile->getAttributeValueAsInt("level");
                    game.players[0]->armor =  saveFile->getAttributeValueAsInt("armor");
                    game.players[0]->strength = saveFile->getAttributeValueAsInt("strength");
                    game.players[0]->vitality = saveFile->getAttributeValueAsInt("vitality");
                    game.players[0]->experience = saveFile->getAttributeValueAsInt("exp");
                }
                break;
            default:
                break;
        }
    }
    if (!fileNotEmpty){
        std::cerr << "Can't read level file " << saveSlot << std::endl;
    }
    delete saveFile;
    saveFile = NULL;
    game.LFS = true;

    game.LoadLevel(level);
}