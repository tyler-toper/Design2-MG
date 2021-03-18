#include "../HeaderFiles/SaveMenu.h"


SaveMenu::SaveMenu(float width, float height, std::map<std::string, sf::Keyboard::Key>* controlMapping){
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

void SaveMenu::PollMenu(RenderWindow &window, GameState &state){
    Event event;
    while(window.pollEvent(event)){
        if(event.type == Event::Closed){
            window.close();
        }
        if(event.type == Event::KeyPressed){
            auto pressed = event.key.code;
            std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;

            if(pressed == controls["Pause"]){
                state.SetState(GameState::PAUSE);
            }
            // FIXME: Connect to save functionality. Stay on screen or return to pause screen?
            else if(pressed == Keyboard::Return){
                cout << "Save" << endl;
            }
        }
    }
}

void SaveMenu::Draw(RenderWindow &window){
    window.draw(backgroundSprite);
    window.draw(menuSprite);
    // TODO: Get rid of below when implementing save screen
    Font font;
    font.loadFromFile("../../Assets/Fonts/PixelFont.ttf");
    Text text;
    text.setString("THIS IS SAVING!!!");
    text.setFont(font);
    text.setFillColor(Color::Blue);
    text.setCharacterSize(100);
    text.setPosition(0, 0);
    window.draw(text);
}

void SaveMenu::MoveUp(){

}

void SaveMenu::MoveDown(){

}
