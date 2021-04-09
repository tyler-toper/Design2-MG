#include "../HeaderFiles/Pause.h"
#include "../HeaderFiles/Character.h"
#include <fstream>


Pause::Pause(float width, float height,  std::map<std::string, sf::Keyboard::Key>* controlMapping, Game &game) {
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
    text[1].setString("Save / Load");
    text[2].setString("Settings");
    text[3].setString("Quit to Main Menu");


    for(int i = 0; i < PauseOptions; i++){
        text[i].setFont(font);
        text[i].setFillColor(Color::Yellow);
        text[i].setCharacterSize(50);

        FloatRect box = text[i].getGlobalBounds();
        float offset = box.width / 2;
        text[i].setPosition(100, (height / (PauseOptions + 1) * (i + 1)));
    }

    text[selected].setFillColor(Color::Red);
    text[selected].setStyle(Text::Underlined);


    statTitle.setString("Player Stats");
    statTitle.setFont(font);
    statTitle.setFillColor(Color::Yellow);
    statTitle.setCharacterSize(40);
    statTitle.setStyle(Text::Underlined);
    statTitle.setPosition(650, 200);

    GetStats(game);
    for(int i = 0; i < 6; i++){
        stats[i].setFont(font);
        stats[i].setFillColor(Color::Yellow);
        stats[i].setCharacterSize(30);
        stats[i].setPosition(600, (height / 15) * (i+5));
    }

    moveBuffer.loadFromFile("../../Assets/Audio/SFX/Interface Sounds/Audio/bong_001.ogg");
    moveSound.setBuffer(moveBuffer);
    moveSound.setVolume(40);

    errorBuffer.loadFromFile("../../Assets/Audio/SFX/Interface Sounds/Audio/error_008.ogg");
    errorSound.setBuffer(errorBuffer);
    errorSound.setVolume(45);

    confirmBuffer.loadFromFile("../../Assets/Audio/SFX/UI Audio/Audio/click2.ogg");
    confirmSound.setBuffer(confirmBuffer);
    confirmSound.setVolume(70);

    backBuffer.loadFromFile("../../Assets/Audio/SFX/Interface Sounds/Audio/close_001.ogg");
    backSound.setBuffer(backBuffer);
    backSound.setVolume(25);
}


void Pause::PollMenu(RenderWindow &window, GameState &state, Game &game) {
    Event event;
    GetStats(game);
    while(window.pollEvent(event)){
        if(event.type == Event::Closed){
            window.close();
        }
        if (event.type == Event::KeyPressed){
            auto pressed = event.key.code;
            // Needs to dereference controlMapping in order to read map
            std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;

            if(pressed == controls["Pause"]){
                backSound.play();
                state.SetState(GameState::LVL1);
                state.Resume();
                Reset();
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
                    state.SetState(GameState::LVL1);
                    state.Resume();
                    Reset();
                }
                else if(selected == 1){
                    state.SetState(GameState::SAVELOAD);
                }
                else if(selected == 2){
                    state.SetState(GameState::SETTINGS);
                }
                else if(selected == 3){
                    state.SetState(GameState::MENU);
                    Reset();
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

    for(int i = 0; i < 6; i++){
        window.draw(stats[i]);
    }

    window.draw(statTitle);
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

void Pause::Reset(){
    text[selected].setFillColor(Color::Yellow);
    text[selected].setStyle(Text::Regular);
    selected = 0;
    text[selected].setFillColor(Color::Red);
    text[selected].setStyle(Text::Underlined);
}

void Pause::GetStats(Game &game) {
    stats[0].setString("Max Health: " + to_string(game.getPlayer()->getMaxHealth()));
    stats[1].setString("Damage: " + to_string(game.getPlayer()->getDamageMod()));
    stats[2].setString("Fire Rate: " + to_string(game.getPlayer()->getCharReloadMod()));
    stats[3].setString("Movement Speed: " + to_string(game.getPlayer()->getMoveSpeed()));
    stats[4].setString("Number of Jumps: " + to_string(game.getPlayer()->getJumpCountMax()));
    stats[5].setString("Jump Height: " + to_string(game.getPlayer()->getJumpHeight()));
}