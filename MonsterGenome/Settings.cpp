#include "Settings.h"

// TODO: Make controls changeable and savable

Settings::Settings(float width, float height){
    font.loadFromFile(pixelFont);
    selected = 0;

    LoadControls();

    title.setString("SETTINGS");
    title.setFont(font);
    title.setFillColor(Color::Yellow);
    title.setCharacterSize(100);
    FloatRect titleBox = title.getGlobalBounds();
    float titleOffset = titleBox.width / 2;
    title.setPosition((width / 2) - titleOffset, 0);


    for(int i = 0; i < SettingsOptions; i++){
        options[i].setString(function[i]);
        options[i].setFont(font);
        options[i].setFillColor(Color::Yellow);
        options[i].setCharacterSize(50);

        FloatRect optionBox = options[i].getGlobalBounds();
        float optionOffset = optionBox.width / 2;
        float optionWidth = width / 2;
        options[i].setPosition((optionWidth / 2) - optionOffset, (height / (SettingsOptions + 1) * (i + 1)));


        UserControls[i].setString(control[i]);
        UserControls[i].setFont(font);
        UserControls[i].setFillColor(Color::Yellow);
        UserControls[i].setCharacterSize(50);

        FloatRect controlBox = UserControls[i].getGlobalBounds();
        float controlOffset = controlBox.width / 2;
        float controlWidth = width * 1.5;
        UserControls[i].setPosition((controlWidth / 2) - controlOffset, (height / (SettingsOptions + 1) * (i + 1)));
    }

    UserControls[selected].setFillColor(Color::Red);
    UserControls[selected].setStyle(Text::Underlined);
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
                UserControls[selected].setFillColor(Color::Blue);
                UserControls[selected].setStyle(Text::Underlined);
                if(event.type == Event::TextEntered && event.text.unicode < 128){

                }
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
        window.draw(options[i]);
        window.draw(UserControls[i]);
    }
}

void Settings::MoveDown(){
    if(selected + 1 < SettingsOptions){
        UserControls[selected].setFillColor(Color::Yellow);
        UserControls[selected].setStyle(Text::Regular);
        selected++;
        UserControls[selected].setFillColor(Color::Red);
        UserControls[selected].setStyle(Text::Underlined);
    }
}

void Settings::MoveUp(){
    if(selected - 1 >= 0){
        UserControls[selected].setFillColor(Color::Yellow);
        UserControls[selected].setStyle(Text::Regular);
        selected--;
        UserControls[selected].setFillColor(Color::Red);
        UserControls[selected].setStyle(Text::Underlined);
    }
}

void Settings::LoadControls() {
    inFS.open(controls);
    if(inFS.is_open()){
        while(getline(inFS, line)){
            stringstream ss(line);
            string word;

            vector<string> temp;
            while(getline(ss, word, ',')){
                temp.push_back(word);
            }

            function.push_back(temp[0]);
            defaults.push_back(temp[1]);
            control.push_back(temp[2]);
        }
    }
    else{
        cout << "Unable to load controls" << endl;
    }
}

void Settings::ResetControls() {
    for(int i = 0; i < SettingsOptions; i++){
        control[i] = defaults[i];
    }
}