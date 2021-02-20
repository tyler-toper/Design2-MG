#include "../HeaderFiles/Settings.h"

Settings::Settings(float width, float height){
    // Initialize variables
    font.loadFromFile(pixelFont);
    selected = 0;
    selectPressed = false;
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

    // Configure directions on bottom of screen
    // TODO: Change string to reflect new controls
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

        UserControls[i].setString(ConvertControls(control[i]));
        UserControls[i].setFont(font);
        UserControls[i].setFillColor(Color::Yellow);
        UserControls[i].setCharacterSize(50);

    }

    // Configure selected text
    UserControls[selected].setFillColor(Color::Red);
    UserControls[selected].setStyle(Text::Underlined);

    // Load controlMapping
    for(int i = 0; i < SettingsOptions; i++) {
        controlMapping[function[i]] = control[i];
    }

    if(!buffer.loadFromFile("../../Assets/Audio/SFX/UI Audio/Audio/click2.ogg")){
        cout << "Failed to load sound in menu" << endl;
    }
    else{
        sound.setBuffer(buffer);
        sound.setVolume(20);
    }
}

std::map<std::string, sf::Keyboard::Key>* Settings::GetControlMapping() {
    return &controlMapping;
}

std::string Settings::ConvertControls(sf::Keyboard::Key key) {

    // TODO FINISH ALL KEY MAPPINGS
    // Using the char values plus the key values to find keys
    // Alphabet
    if (key < 26) {
        return std::string(1, key + 65);
    }
    // Numbers
    else if (key < 36) {
        return std::string(1, key - 26 + 48);
    }
    // Special Keys
    else if (key == 37) {
        return "Escape";
    }
    else if (key == 38) {
        return "Left Control";
    }
    else if (key == 39) {
        return "Left Shift";
    }
    else if (key == 40) {
        return "Left Alt";
    }

    // Arrow Keys
    else if (key == 71) {
        return "Left Arrow";
    }
    else if (key == 72) {
        return "Right Arrow";
    }
    else if (key == 73) {
        return "Up Arrow";
    }
    else if (key == 74) {
        return "Down Arrow";
    }


    return std::to_string(key);
}


void Settings::PollMenu(RenderWindow &window, GameState &state){
    Event event;
    while(window.pollEvent(event)) {
        // Happens regardless of state
        if(event.type == Event::Closed) { window.close(); }

        // When editing keys
        if(selectPressed) {
            // TODO: Check for duplicate controls, pop up menu, ask to save, connect with controls
            // The TextEntered must be here. It won't work inside other if statements
            if(event.type == Event::KeyPressed) {
                // Read the input
                auto pressed = event.key.code;
                // Saves the enum value
                control[selected] = pressed;
                controlMapping[function[selected]] = pressed;
                // Print the corresponding key for the enum
                UserControls[selected].setString(ConvertControls(pressed));
                UserControls[selected].setFillColor(Color::Red);
                selectPressed = false;
            }
        }

        // When navigating menu
        else {
            if (event.type == Event::KeyPressed) {
                auto pressed = event.key.code;
                if (pressed == controlMapping["Pause"] && state.IsPlaying()) {
                    Save();
                    state.SetState(GameState::PAUSE);
                }
                if (pressed == controlMapping["Pause"] && !state.IsPlaying()) {
                    Save();
                    state.SetState(GameState::MENU);
                }
                if (pressed == controlMapping["Jump"]) { MoveUp(); }
                if (pressed == controlMapping["Crouch"]) { MoveDown(); }
                // TODO: Determine what the relative controls for these two are
                if (pressed == Keyboard::Q){ ResetControls(); }
                if (pressed == Keyboard::Return) {
                    UserControls[selected].setFillColor(Color::Blue);
                    UserControls[selected].setStyle(Text::Underlined);
                    selectPressed = true;
                }
            }
        }
    }
}

void Settings::Draw(RenderWindow &window){
    // Load background
    Texture texture;
    texture.loadFromFile("../../Assets/Backgrounds/Temp Background.png");
    Sprite background(texture);
    background.setPosition(0, 0);
    window.draw(background);

    // Draw
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
    sound.play();
    if(selected + 1 < SettingsOptions){
        UserControls[selected].setFillColor(Color::Yellow);
        UserControls[selected].setStyle(Text::Regular);
        selected++;
        UserControls[selected].setFillColor(Color::Red);
        UserControls[selected].setStyle(Text::Underlined);
    }
}

void Settings::MoveUp(){
    sound.play();
    if(selected - 1 >= 0){
        UserControls[selected].setFillColor(Color::Yellow);
        UserControls[selected].setStyle(Text::Regular);
        selected--;
        UserControls[selected].setFillColor(Color::Red);
        UserControls[selected].setStyle(Text::Underlined);
    }
}

void Settings::LoadControls() {
    // CSV file is in format of: Name of action, default controls, current controls
    inFS.open(controls);
    if(inFS.is_open()){
        while(getline(inFS, line)){
            stringstream ss(line);
            string word;
            int hold = 0;

            // Get the name
            getline(ss, word, ',');
            function.push_back(word);
            // Get the default controls
            getline(ss, word, ',');
            stringstream num1(word);
            num1 >> hold;
            defaults.push_back(static_cast<Keyboard::Key>(hold));
            // Get the actual controls
            getline(ss, word, ',');
            stringstream num2(word);
            num2 >> hold;
            control.push_back(static_cast<Keyboard::Key>(hold));
        }
    }
    else{
        cout << "Unable to load controls" << endl;
    }
}

// Saves the controls by writing vectors into CSV
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

// Resets controls back to defaults and sets the on screen text
void Settings::ResetControls() {
    for(int i = 0; i < SettingsOptions; i++){
        // TODO: FIX THIS TO WORK WITH ENUM
        control[i] = defaults[i];
        //UserControls[i].setString(control[i]);
    }
}