#include "Settings.h"

// TODO: Make controls changeable and savable

Settings::Settings(float width, float height){
    font.loadFromFile(pixelFont);
    selected = 0;
    EnterPressed = false;
    this->width = width;
    this->height = 0.8 * height;
    LoadControls();

    // Configure title text
    title.setString("SETTINGS");
    title.setFont(font);
    title.setFillColor(Color::Yellow);
    title.setCharacterSize(100);
    FloatRect titleBox = title.getGlobalBounds();
    float titleOffset = titleBox.width / 2;
    title.setPosition((width / 2) - titleOffset, 0);

    directions.setString("Press Q to set controls back to defaults\nPress Esc to save and quit");
    directions.setFont(font);
    directions.setFillColor(Color::Yellow);
    directions.setCharacterSize(35);
    FloatRect directionBox = directions.getGlobalBounds();
    float directionOffset = directionBox.width / 2;
    directions.setPosition((width / 2) - directionOffset, height * 0.88);

    // Configure control action and user control text
    for(int i = 0; i < SettingsOptions; i++){
        options[i].setString(function[i]);
        options[i].setFont(font);
        options[i].setFillColor(Color::Yellow);
        options[i].setCharacterSize(50);

        FloatRect optionBox = options[i].getGlobalBounds();
        float optionOffset = optionBox.width / 2;
        float optionWidth = width / 2;
        options[i].setPosition((optionWidth / 2) - optionOffset, (this->height / (SettingsOptions + 1) * (i + 1)) + 50);


        UserControls[i].setString(control[i]);
        UserControls[i].setFont(font);
        UserControls[i].setFillColor(Color::Yellow);
        UserControls[i].setCharacterSize(50);
    }

    // Configure selected text
    UserControls[selected].setFillColor(Color::Red);
    UserControls[selected].setStyle(Text::Underlined);
}

void Settings::PollMenu(RenderWindow &window, GameState &state){
    Event event;
    while(window.pollEvent(event)) {
        if(event.type == Event::Closed){
            window.close();
        }
        // TODO: Check for duplicate controls, pop up menu, ask to save, connect with controls
        if(event.type == Event::TextEntered && EnterPressed){
            if(event.text.unicode >= 33 && event.text.unicode <= 127){
                char entered = static_cast<char>(event.text.unicode);
                control[selected] = entered;
                UserControls[selected].setString(entered);
                UserControls[selected].setFillColor(Color::Red);
                EnterPressed = false;
            }
            else if(event.text.unicode == 32){
                control[selected] = "SPACE";
                UserControls[selected].setString("SPACE");
                UserControls[selected].setFillColor(Color::Red);
                EnterPressed = false;
            }
        }
        if (event.type == Event::KeyPressed) {
            auto pressed = event.key.code;
            if(pressed == Keyboard::Escape && state.IsPlaying()){
                Save();
                // Update Player controls
                state.SetState(GameState::PAUSE);
            }
            if(pressed == Keyboard::Escape && !state.IsPlaying()){
                Save();
                // Update Player controls
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
                EnterPressed = true;
            }
            if(pressed == Keyboard::Q){
                ResetControls();
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
    window.draw(directions);

    for(int i = 0; i < SettingsOptions; i++){
        FloatRect controlBox = UserControls[i].getGlobalBounds();
        float controlOffset = controlBox.width / 2;
        float controlWidth = this->width * 1.5;
        UserControls[i].setPosition((controlWidth / 2) - controlOffset, (height / (SettingsOptions + 1) * (i + 1)) + 50);

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

// Handles loading the control into the game
void Settings::LoadControls() {
    // CSV file is in format of: Name of action, default controls, current controls
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
            keys.push_back(Keyboard::Escape);
        }
    }
    else{
        cout << "Unable to load controls" << endl;
    }
}

void Settings::Save() {
    outFS.open(controls, ofstream::trunc);
    if(outFS.is_open()){
        for(int i = 0; i < SettingsOptions; i++){
            outFS << function[i] << "," << defaults[i] << "," << control[i] << "\n";
        }
        outFS.close();
    }
    else{
        cout << "Unable to open controls" << endl;
    }
}

void Settings::ResetControls() {
    for(int i = 0; i < SettingsOptions; i++){
        control[i] = defaults[i];
        UserControls[i].setString(control[i]);
    }
}