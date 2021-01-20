#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include <iostream>
#include <stack>
#include "StateManager.h"
using namespace std;
using namespace sf;

#define pixelFont "../../Assets/Fonts/PixelFont.ttf"
#define options 3

class Menu{
private:
    int selected;
    Font font;
    Text text[options];

public:
    Menu(float width, float height);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetSelected() const;

    void PollMenu(Event &event, RenderWindow &window, StateManager &state);
};
