#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "GameState.h"
using namespace std;
using namespace sf;

#define pixelFont "../../Assets/Fonts/PixelFont.ttf"
#define MenuOptions 3

class Menu{
private:
    int selected;
    Font font;
    Text text[MenuOptions];
    Text title;

public:
    Menu(float width, float height);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetSelected() const;

    void PollMenu(RenderWindow &window, GameState &state);
};
