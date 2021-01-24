#include "Pause.h"


Pause::Pause(float width, float height) {
    font.loadFromFile(pixelFont);
    selected = 0;

    text[0].setString("Resume");
    text[1].setString("Save");
    text[2].setString("Load");
    text[3].setString("Settings");
    text[4].setString("Quit to Main Menu");

    for(int i = 0; i < options; i++){
        text[i].setFont(font);
        text[i].setFillColor(Color::Yellow);
        text[i].setCharacterSize(50);

        FloatRect box = text[i].getGlobalBounds();
        float offset = box.width / 2;
        text[i].setPosition((width / 2) - offset, (height / (options + 1) * (i + 1)));

    }

    text[selected].setFillColor(Color::Red);
    text[selected].setStyle(Text::Underlined);
}


void Pause::PollMenu(Event &event, RenderWindow &window, GameState &state) {
    // TODO: See which one is better. Both have a little bit of delay

    if(Keyboard::isKeyPressed(Keyboard::Up)){
        MoveUp();
    }
    if(Keyboard::isKeyPressed(Keyboard::Down)){
        MoveDown();
    }
    if(Keyboard::isKeyPressed(Keyboard::Return)){
        if(GetSelected() == 0){

        }
        else if(GetSelected() == 1){

        }
        else if(GetSelected() == 2){

        }
        else if(GetSelected() == 3){
            state.SetState(GameState::SETTINGS)
        }
        else if(GetSelected() == 4){
            state.SetPlaying(false);
            state.SetPlaying(GameState::MENU);
        }
    }
}

void Pause::Draw(RenderWindow &window){
    for(int i = 0; i < options; i++){
        window.draw(text[i]);
    }
}

void Pause::MoveDown(){
    if(selected + 1 < options){
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