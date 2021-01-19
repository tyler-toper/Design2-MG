#include "Menu.h"

Menu::Menu(float width, float height){
    state = true;

    font.loadFromFile(pixelFont);
    selected = 0;

    text[0].setString("Play");
    text[1].setString("Settings");
    text[2].setString("Quit");

    for(int i = 0; i < options; i++){
        text[i].setFont(font);
        text[i].setFillColor(Color::Yellow);
        text[i].setCharacterSize(100);

        FloatRect box = text[i].getGlobalBounds();
        float offset = box.width / 2;
        text[i].setPosition((width / 2) - offset, (height / (options + 1) * (i + 1)));

    }

    text[selected].setFillColor(Color::Red);
    text[selected].setStyle(Text::Underlined);
}

void Menu::PollMenu(Event &event, RenderWindow &window) {

}

void Menu::Draw(RenderWindow &window){
    for(int i = 0; i < options; i++){
        window.draw(text[i]);
    }
}

void Menu::MoveDown(){
    if(selected + 1 < options){
        text[selected].setFillColor(Color::Yellow);
        text[selected].setStyle(Text::Regular);
        selected++;
        text[selected].setFillColor(Color::Red);
        text[selected].setStyle(Text::Underlined);
    }
}

void Menu::MoveUp(){
    if(selected - 1 >= 0){
        text[selected].setFillColor(Color::Yellow);
        text[selected].setStyle(Text::Regular);
        selected--;
        text[selected].setFillColor(Color::Red);
        text[selected].setStyle(Text::Underlined);
    }
}

bool Menu::GetState() const{
    return state;
}

int Menu::GetSelected() const{
    return selected;
}