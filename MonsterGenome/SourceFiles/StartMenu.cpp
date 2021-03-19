#include "../HeaderFiles/StartMenu.h"


StartMenu::StartMenu(float width, float height, std::map<std::string, sf::Keyboard::Key>* controlMapping){
    this->controlMapping = controlMapping;
    selected = 0;

    menu.loadFromFile("../../Assets/Backgrounds/StartScreen/StartMenu.png");
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

void StartMenu::PollMenu(RenderWindow &window, GameState &state){
    Event event;
    while(window.pollEvent(event)){
        if(event.type == Event::Closed){
            window.close();
        }
        if(event.type == Event::KeyPressed){
            auto pressed = event.key.code;
            std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;

            if(pressed == controls["Pause"]){
                state.SetState(GameState::MENU);
            }
            // FIXME: Connect to load functionality
            else if(pressed == Keyboard::Return){
                state.SetState(GameState::LVL1);
                //state.SetPlaying(true);
            }
        }
    }
}

void StartMenu::Draw(RenderWindow &window){
    window.draw(backgroundSprite);
    window.draw(menuSprite);
}

void StartMenu::MoveUp(){

}

void StartMenu::MoveDown(){

}
