#include "../HeaderFiles/Menu.h"

Menu::Menu(float width, float height){
    font.loadFromFile(pixelFont);
    selected = 0;

    // TODO: Make game logo
    title.setString("The Monster Genome");
    title.setFont(font);
    title.setFillColor(Color::Blue);
    title.setCharacterSize(100);
    FloatRect titleBox = title.getGlobalBounds();
    float titleOffset = titleBox.width / 2;
    title.setPosition((width / 2) - titleOffset, 0);
    title.setStyle(Text::Underlined);

    text[0].setString("Play");
    text[1].setString("Settings");
    text[2].setString("Quit");


    for(int i = 0; i < MenuOptions; i++){
        text[i].setFont(font);
        text[i].setFillColor(Color::Yellow);
        text[i].setCharacterSize(75);

        FloatRect box = text[i].getGlobalBounds();
        float offset = box.width / 2;
        text[i].setPosition((width / 2) - offset, (height / (MenuOptions + 1) * (i + 1)));

    }

    text[selected].setFillColor(Color::Red);
    text[selected].setStyle(Text::Underlined);
}

void Menu::PollMenu(RenderWindow &window, GameState &state) {
    Event event;
    while(window.pollEvent(event)) {
        if(event.type == Event::Closed){
            window.close();
        }
        if (event.type == Event::KeyPressed) {
            auto pressed = event.key.code;
            if (pressed == Keyboard::Up) {
                MoveUp();
            }
            if (pressed == Keyboard::Down) {
                MoveDown();
            }
            if (pressed == Keyboard::Return) {
                if (selected == 0) {
                    state.SetState(GameState::PLAY);
                    state.SetPlaying(true);
                }
                else if (selected == 1) {
                    state.SetState(GameState::SETTINGS);
                }
                else if (selected == 2) {
                    window.close();
                }
            }
        }
    }
}

void Menu::Draw(RenderWindow &window){
    Texture texture;
    texture.loadFromFile("../../Assets/Backgrounds/Temp Background.png");
    Sprite background(texture);
    background.setPosition(0, 0);
    window.draw(background);

    window.draw(title);

    for(int i = 0; i < MenuOptions; i++){
        window.draw(text[i]);
    }
}

void Menu::MoveDown(){
    if(selected + 1 < MenuOptions){
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