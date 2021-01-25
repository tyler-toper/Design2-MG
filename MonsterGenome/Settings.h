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

class Settings {
private:
    int selected;
    Font font;
    Text text[SettingsOptions];
    Text title;

    // TODO: For reading and writing to csv files to store controls
    ifstream inFS;
    ofstream outFS;
    stringstream ss;
    vector<string> function;
    vector<string> control;
    vector<string> defaults;

public:
    Settings(float width, float height);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetSelected() const;

    void PollMenu(RenderWindow &window, GameState &state);


};

