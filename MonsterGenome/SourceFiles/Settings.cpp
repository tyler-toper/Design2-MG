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

std::map<std::string, sf::Keyboard::Key>* Settings::GetControlMapping() {
    return &controlMapping;
}

std::string Settings::ConvertControls(sf::Keyboard::Key key) {

    // TODO FINISH ALL KEY MAPPINGS
    // Using the char values plus the key values to find keys
    // Alphabet
    if (key < 26) {
        return std::string(1,key + 65);
    }
    // Numbers
    else if (key < 36) {
        return std::to_string(key - 26);
    }
    // Special Keys
    else if (key == 36) {
        return "Escape";
    }
    else if (key == 37) {
        return "Left Control";
    }
    else if (key == 38) {
        return "Left Shift";
    }
    else if (key == 39) {
        return "Left Alt";
    }
    else if (key == 40) {
        return "Left System";
    }
    else if (key == 41) {
        return "Right Control";
    }
    else if (key == 42) {
        return "Right Shift";
    }
    else if (key == 43) {
        return "Right Alt";
    }
    else if (key == 44) {
        return "Right System";
    }
    else if (key == 45) {
        return "Menu";
    }
    // Special Characters
    else if (key == 46) {
        return "[";
    }
    else if (key == 47) {
        return "]";
    }
    else if (key == 48) {
        return ";";
    }
    else if (key == 49) {
        return ",";
    }
    else if (key == 50) {
        return ".";
    }
    else if (key == 51) {
        return "'";
    }
    else if (key == 52) {
        return "/";
    }
    else if (key == 53) {
        return "\\";
    }
    else if (key == 54) {
        return "~";
    }
    else if (key == 55) {
        return "=";
    }
    else if (key == 56) {
        return "-";
    }
    else if (key == 57) {
        return "Space";
    }
    else if (key == 58) {
        return "Enter";
    }
    else if (key == 59) {
        return "Backspace";
    }
    else if (key == 60) {
        return "Tab";
    }
    else if (key == 61) {
        return "Page Up";
    }
    else if (key == 62) {
        return "Page Down";
    }
    else if (key == 63) {
        return "End";
    }
    else if (key == 64) {
        return "Home";
    }
    else if (key == 65) {
        return "Insert";
    }
    else if (key == 66) {
        return "Delete";
    }
    else if (key == 67) {
        return "+";
    }
    else if (key == 68) {
        return "-";
    }
    else if (key == 69) {
        return "*";
    }
    else if (key == 70) {
        return "/";
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
    // Numpad
    else if (key < 85) {
        return "Numpad " + std::to_string(key - 75);
    }
    // F Keys
    else if(key < 100) {
        return "F" + std::to_string(key - 84);
    }
    else if(key == 100) {
        return "Pause";
    }
    // All else fails, return the key number
    return std::to_string(key);
}

// Override existing controls with new controls
void Settings::UpdateControls() {
    for (int i = 0; i < control.size(); i++) {
        controlMapping[function[i]] = control[i];
    }
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
                // Print the corresponding key for the enum
                UserControls[selected].setString(ConvertControls(pressed));
                UserControls[selected].setFillColor(Color::Red);
                selectPressed = false;
                confirmSound.play();
            }
        }

        // When navigating menu
        else {
            if (event.type == Event::KeyPressed) {
                auto pressed = event.key.code;
                if (pressed == controlMapping["Pause"] && state.IsPlaying()) {
                    UpdateControls();
                    Save();
                    state.SetState(GameState::PAUSE);
                    Reset();
                }
                if (pressed == controlMapping["Pause"] && !state.IsPlaying()) {
                    UpdateControls();
                    Save();
                    state.SetState(GameState::MENU);
                    Reset();
                }
                if (pressed == controlMapping["Jump"]) { MoveUp(); }
                if (pressed == controlMapping["Crouch"]) { MoveDown(); }
                // TODO: Determine what the relative controls for these two are
                if (pressed == Keyboard::Q){ ResetControls(); }
                if (pressed == Keyboard::Return) {
                    confirmSound.play();
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
    if(selected + 1 < SettingsOptions){
        moveSound.play();
        UserControls[selected].setFillColor(Color::Yellow);
        UserControls[selected].setStyle(Text::Regular);
        selected++;
        UserControls[selected].setFillColor(Color::Red);
        UserControls[selected].setStyle(Text::Underlined);
    }
    else{
        errorSound.play();
    }
}

void Settings::MoveUp(){
    if(selected - 1 >= 0){
        moveSound.play();
        UserControls[selected].setFillColor(Color::Yellow);
        UserControls[selected].setStyle(Text::Regular);
        selected--;
        UserControls[selected].setFillColor(Color::Red);
        UserControls[selected].setStyle(Text::Underlined);
    }
    else{
        errorSound.play();
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
        UserControls[i].setString(ConvertControls(control[i]));
    }
}

void Settings::Reset() {
    UserControls[selected].setFillColor(Color::Yellow);
    UserControls[selected].setStyle(Text::Regular);
    selected = 0;
    UserControls[selected].setFillColor(Color::Red);
    UserControls[selected].setStyle(Text::Underlined);
}