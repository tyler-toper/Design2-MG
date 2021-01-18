#include "Menu.h"

Menu::Menu(float width, float height){
    font.loadFromFile(pixelFont);
    selected = 0;

    for(int i = 0; i < options; i++){
        text[i].setFont(font);
        text[i].setFillColor(Color::Blue);
        text[i].setPosition(width / 2, height / (options + 1) * (i + 1));
        text[i].setCharacterSize(100);
    }

    text[0].setString("Play");
    text[1].setString("Settings");
    text[2].setString("Quit");

    text[selected].setFillColor(Color::Red);
    text[selected].setStyle(Text::Underlined);
}

void Menu::Draw(RenderWindow &window){
    for(int i = 0; i < options; i++){
        window.draw(text[i]);
    }
}

void Menu::MoveDown(){
    if(selected + 1 < options){
        text[selected].setFillColor(Color::Blue);
        text[selected].setStyle(Text::Regular);
        selected++;
        text[selected].setFillColor(Color::Red);
        text[selected].setStyle(Text::Underlined);
    }
}

void Menu::MoveUp(){
    if(selected - 1 >= 0){
        text[selected].setFillColor(Color::Blue);
        text[selected].setStyle(Text::Regular);
        selected--;
        text[selected].setFillColor(Color::Red);
        text[selected].setStyle(Text::Underlined);
    }
}

int Menu::GetSelected(){
    return selected;
}