#include "../HeaderFiles/StartMenu.h"


StartMenu::StartMenu(float width, float height, std::map<std::string, sf::Keyboard::Key>* controlMapping){
    this->controlMapping = controlMapping;
    selected = 0;
    entered = 0;

    xValue = 465;
    yValue[0] = 185;
    yValue[1] = 261;
    yValue[2] = 337;
    yValue[3] = 413;

    menu.loadFromFile("../../Assets/Backgrounds/StartScreen/StartMenu.png");
    menuSprite.setTexture(menu);

    startButton.loadFromFile("../../Assets/Backgrounds/StartScreen/StartButtonSelected.png");
    startButtonSprite.setTexture(startButton);
    startButtonSprite.setPosition(414, 586);

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

void StartMenu::PollMenu(RenderWindow &window, GameState &state){
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

            if(pressed == controls["Pause"]){
                state.SetState(GameState::MENU);
            }
            // FIXME: Connect to load functionality
            else if(pressed == Keyboard::Return){
                // TODO: Check "selected" variable and set position for entered box
                if(selected == 4){
                    state.SetState(GameState::LVL1);
                    state.SetPlaying(true);
                }
                else{
                    enteredBoxSprite.setPosition(xValue, yValue[selected]);
                }
            }
        }
    }
}

void StartMenu::Draw(RenderWindow &window){
    window.draw(backgroundSprite);
    window.draw(menuSprite);
    window.draw(selectedBoxSprite);

    if(selected == 4){
        window.draw(startButtonSprite);
        // Draws off screen. The else condition can't prevent it from still drawing at selected = 3
        selectedBoxSprite.setPosition(2000, 2000);
    }
    else{
        selectedBoxSprite.setPosition(xValue, yValue[selected]);
    }
    window.draw(enteredBoxSprite);
}

void StartMenu::MoveUp(){
    if(selected - 1 >= 0){
        moveSound.play();
        selected--;
    }
    else{
        errorSound.play();
    }
}

void StartMenu::MoveDown(){
    if(selected + 1 < StartMenuOptions){
        moveSound.play();
        selected++;
    }
    else{
        errorSound.play();
    }
}
