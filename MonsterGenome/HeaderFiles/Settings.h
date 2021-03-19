#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "../HeaderFiles/GameState.h"
using namespace std;
using namespace sf;

#define pixelFont "../../Assets/Fonts/PixelFont.ttf"
#define SettingsOptions 7
#define controls "../../Settings/Controls.csv"

class Settings {
private:
    int selected;
    Font font;
    // Name of action. Corresponds to the function vector, but is a Text object to draw to screen
    Text options[SettingsOptions];
    // User selected keys. Corresponds to the control vector, but is a Text object to draw to screen
    Text UserControls[SettingsOptions];
    Text title;
    Text directions;

    bool selectPressed;
    float width;
    float height;

    // For reading and writing to csv files to store controls
    string line;
    ifstream inFS;
    ofstream outFS;
    // Name of action
    vector<string> function;
    // Default keys
    std::vector<sf::Keyboard::Key> defaults;
    // User selected keys
    std::vector<sf::Keyboard::Key> control;
    // The key mapping
    std::map<std::string, sf::Keyboard::Key> controlMapping;

    void LoadControls();
    void Save();
    void ResetControls();
    std::string ConvertControls(sf::Keyboard::Key key);
    void UpdateControls();

    SoundBuffer moveBuffer;
    Sound moveSound;
    SoundBuffer errorBuffer;
    Sound errorSound;
    SoundBuffer confirmBuffer;
    Sound confirmSound;

public:
    Settings(float width, float height);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();

    std::map<std::string, sf::Keyboard::Key>* GetControlMapping();

    // HandleInput
    // Takes in the raw keyboard input and converts it to relevant game text, like jump or left
    void PollMenu(RenderWindow &window, GameState &state);
};

