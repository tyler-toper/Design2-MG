#include "../HeaderFiles/Pause.h"


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
    text[1].setString("Save / Load");
    text[2].setString("Settings");
    text[3].setString("Quit to Main Menu");

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


void Pause::PollMenu(RenderWindow &window, GameState &state) {
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
                }
                else if(selected == 1){
                    state.SetState(GameState::SAVELOAD);
                }
                else if(selected == 2){
                    state.SetState(GameState::SETTINGS);
                }
                else if(selected == 3){
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

void Pause::Reset(){
    text[selected].setFillColor(Color::Yellow);
    text[selected].setStyle(Text::Regular);
    selected = 0;
    text[selected].setFillColor(Color::Red);
    text[selected].setStyle(Text::Underlined);
}