#include "../HeaderFiles/SaveMenu.h"


SaveMenu::SaveMenu(float width, float height, std::map<std::string, sf::Keyboard::Key>* controlMapping){
    this->controlMapping = controlMapping;
    selected = 0;

    menu.loadFromFile("../../Assets/Backgrounds/SaveMenu.png");
    menuSprite.setTexture(menu);

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

void SaveMenu::PollMenu(RenderWindow &window, GameState &state){
    Event event;
    while(window.pollEvent(event)){
        if(event.type == Event::Closed){
            window.close();
        }
        if(event.type == Event::KeyPressed){
            auto pressed = event.key.code;
            std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;

            if(pressed == controls["Escape"]){
                state.SetState(GameState::MENU);
            }
        }
    }
}

void SaveMenu::Draw(RenderWindow &window){
    window.draw(menuSprite);
}

void SaveMenu::MoveUp(){

}

void SaveMenu::MoveDown(){

}
