#include "../HeaderFiles/LoadMenu.h"

loadMenu::loadMenu(float width, float height, std::map<std::string, sf::Keyboard::Key>* controlMapping){
    this->controlMapping = controlMapping;
    selected = 0;

    menu.loadFromFile("../../Assets/Backgrounds/SaveMenu.png");
    menuSprite.setTexture(menu);

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

void loadMenu::PollMenu(RenderWindow &window, GameState &state){
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
            // FIXME: Connect to load functionality
            else if(pressed == Keyboard::Return){
                state.SetState(GameState::LVL1);
                state.SetPlaying(true);
            }
        }
    }
}

void loadMenu::Draw(RenderWindow &window){
    window.draw(backgroundSprite);
    window.draw(menuSprite);
}

void loadMenu::MoveUp(){

}

void loadMenu::MoveDown(){

}
