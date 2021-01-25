#include "Settings.h"

// TODO: Make controls changeable and savable

Settings::Settings(float width, float height){
    font.loadFromFile(pixelFont);
    selected = 0;

    title.setString("SETTINGS");
    title.setFont(font);
    title.setFillColor(Color::Yellow);
    title.setCharacterSize(100);
    FloatRect titleBox = title.getGlobalBounds();
    float titleOffset = titleBox.width / 2;
    title.setPosition((width / 2) - titleOffset, 0);
    title.setStyle(Text::Underlined);

    text[0].setString("Move Right");
    text[1].setString("Move Left");
    text[2].setString("Jump");
    text[3].setString("Crouch");
    text[4].setString("Attack");
    text[5].setString("Reload");
    text[6].setString("Pause");

    for(int i = 0; i < SettingsOptions; i++){
        text[i].setFont(font);
        text[i].setFillColor(Color::Yellow);
        text[i].setCharacterSize(50);

        FloatRect box = text[i].getGlobalBounds();

        float offset = box.width / 2;
        text[i].setPosition((width / 2) - offset, (height / (SettingsOptions + 1) * (i + 1)));

    }

    text[selected].setFillColor(Color::Red);
    text[selected].setStyle(Text::Underlined);
}

void Settings::PollMenu(RenderWindow &window, GameState &state){
    Event event;
    while(window.pollEvent(event)) {
        if(event.type == Event::Closed){
            window.close();
        }
        if (event.type == Event::KeyPressed) {
            auto pressed = event.key.code;
            if(pressed == Keyboard::Escape && state.IsPlaying()){
                state.SetState(GameState::PAUSE);
            }
            if(pressed == Keyboard::Escape && !state.IsPlaying()){
                state.SetState(GameState::MENU);
            }
            if (pressed == Keyboard::Up) {
                MoveUp();
            }
            if (pressed == Keyboard::Down) {
                MoveDown();
            }
            if (pressed == Keyboard::Return) {

            }
        }
    }
}

void Settings::Draw(RenderWindow &window){
    Texture texture;
    texture.loadFromFile("../../Assets/Backgrounds/Temp Background.png");
    Sprite background(texture);
    background.setPosition(0, 0);
    window.draw(background);

    window.draw(title);

    for(int i = 0; i < SettingsOptions; i++){
        window.draw(text[i]);
    }
}

void Settings::MoveDown(){
    if(selected + 1 < SettingsOptions){
        text[selected].setFillColor(Color::Yellow);
        text[selected].setStyle(Text::Regular);
        selected++;
        text[selected].setFillColor(Color::Red);
        text[selected].setStyle(Text::Underlined);
    }
}

void Settings::MoveUp(){
    if(selected - 1 >= 0){
        text[selected].setFillColor(Color::Yellow);
        text[selected].setStyle(Text::Regular);
        selected--;
        text[selected].setFillColor(Color::Red);
        text[selected].setStyle(Text::Underlined);
    }
}

int Settings::GetSelected() const{
    return selected;
}