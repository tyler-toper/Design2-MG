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

void SaveLoadMenu::PollMenu(RenderWindow &window, GameState &state){
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
            // FIXME: Connect to load functionality. Stay on screen or return to pause screen?
            else if(pressed == Keyboard::Return){
                if(selected == 4 && entered != -1){
                    cout << "Save" << endl;
                }
                else if(selected == 5 && entered != -1){
                    cout << "Load" << endl;
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