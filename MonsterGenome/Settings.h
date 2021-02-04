#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "GameState.h"
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

    bool EnterPressed;
    float width;
    float height;

    // For reading and writing to csv files to store controls
    string line;
    ifstream inFS;
    ofstream outFS;
    // Name of action
    vector<string> function;
    // Default keys
    vector<string> defaults;
    vector<Keyboard::Key> keys;
    // User selected keys
    vector<string> control;

    void LoadControls();
    void Save();
    void ResetControls();

public:
    Settings(float width, float height);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();

    void PollMenu(RenderWindow &window, GameState &state);
};

