#include "../HeaderFiles/SaveLoadMenu.h"

SaveLoadMenu::SaveLoadMenu(float width, float height, std::map<std::string, sf::Keyboard::Key>* controlMapping){
    this->controlMapping = controlMapping;
    selected = 0;

    menu.loadFromFile("../../Assets/Backgrounds/SaveLoad/LoadMenu.png");
    menuSprite.setTexture(menu);

    saveButton.loadFromFile("../../Assets/Backgrounds/SaveLoad/SaveButtonSelected.png");
    saveButtonSprite.setTexture(saveButton);
    saveButtonSprite.setPosition(500, 500);

    loadButton.loadFromFile("../../Assets/Backgrounds/SaveLoad/LoadButtonSelected.png");
    loadButtonSprite.setTexture(loadButton);
    loadButtonSprite.setPosition(400, 400);

    enteredBox.loadFromFile("../../Assets/Backgrounds/SaveBoxEntered.png");
    enteredBoxSprite.setTexture(enteredBox);

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
            // FIXME: Connect to load functionality. Stay on screen or return to pause screen?
            else if(pressed == Keyboard::Return){
                //state.SetState(GameState::LVL1);
                //state.SetPlaying(true);
            }
        }
    }
}

void SaveLoadMenu::Draw(RenderWindow &window){
    window.draw(backgroundSprite);
    window.draw(menuSprite);
}

void SaveLoadMenu::MoveUp(){

}

void SaveLoadMenu::MoveDown(){

}
