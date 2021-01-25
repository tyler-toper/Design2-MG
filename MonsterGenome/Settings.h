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
    Text options[SettingsOptions];
    Text UserControls[SettingsOptions];
    Text title;

    // TODO: For reading and writing to csv files to store controls
    string line;
    ifstream inFS;
    ofstream outFS;
    vector<string> function;
    vector<string> defaults;
    vector<string> control;

    void LoadControls();
    void ResetControls();

public:
    Settings(float width, float height);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();

    void PollMenu(RenderWindow &window, GameState &state);
};

