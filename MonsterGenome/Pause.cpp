#include "Pause.h"


Pause::Pause(float width, float height) {
    font.loadFromFile(pixelFont);
    selected = 0;

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
}


void Pause::PollMenu(RenderWindow &window, GameState &state) {
    Event event;
    while(window.pollEvent(event)){
        if(event.type == Event::Closed){
            window.close();
        }
        if (event.type == Event::KeyPressed){
            auto pressed = event.key.code;

            if(pressed == Keyboard::Escape){
                state.SetState(GameState::PLAY);
                state.Resume();
            }
            if (pressed == Keyboard::Up) {
                MoveUp();
            }
            if(pressed == Keyboard::Down){
                MoveDown();
            }
            if(pressed == Keyboard::Return){
                if(GetSelected() == 0){
                    state.SetState(GameState::PLAY);
                    state.Resume();
                }
                else if(GetSelected() == 1){
                    // TODO: Connect save system
                }
                else if(GetSelected() == 2){
                    // TODO: Connect load system
                }
                else if(GetSelected() == 3){
                    state.SetState(GameState::SETTINGS);
                }
                else if(GetSelected() == 4){
                    state.SetPlaying(false);
                    state.SetState(GameState::MENU);
                }
            }
        }
    }
}

void Pause::Draw(RenderWindow &window){
    for(int i = 0; i < PauseOptions; i++){
        window.draw(text[i]);
    }
}

void Pause::MoveDown(){
    if(selected + 1 < PauseOptions){
        text[selected].setFillColor(Color::Yellow);
        text[selected].setStyle(Text::Regular);
        selected++;
        text[selected].setFillColor(Color::Red);
        text[selected].setStyle(Text::Underlined);
    }
}

void Pause::MoveUp(){
    if(selected - 1 >= 0){
        text[selected].setFillColor(Color::Yellow);
        text[selected].setStyle(Text::Regular);
        selected--;
        text[selected].setFillColor(Color::Red);
        text[selected].setStyle(Text::Underlined);
    }
}


int Pause::GetSelected() const{
    return selected;
}