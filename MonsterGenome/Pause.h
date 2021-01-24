#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include <iostream>
#include <stack>
#include "GameState.h"
using namespace std;
using namespace sf;

#define pixelFont "../../Assets/Fonts/PixelFont.ttf"
#define PauseOptions 5

class Pause {
private:
    int selected;
    Font font;
    Text text[PauseOptions];

public:
    Pause(float width, float height);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetSelected() const;

    void PollMenu(Event &event, RenderWindow &window, GameState &state);

};

