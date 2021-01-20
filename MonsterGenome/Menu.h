#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include <iostream>
#include "Game.h"
using namespace std;
using namespace sf;

#define pixelFont "../../Assets/Fonts/PixelFont.ttf"
#define options 3

class Menu{
private:
    int selected;
    Font font;
    Text text[options];
    bool state;

public:
    Menu(float width, float height);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetSelected() const;

    bool GetState() const;
    void SetState(bool NewState);
    void PollMenu(Event &event, RenderWindow &window, Game &game);
};
