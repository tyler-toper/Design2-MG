#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
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
    Text title;

    SoundBuffer buffer;
    Sound sound;

public:
    Pause(float width, float height);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();

    void PollMenu(RenderWindow &window, GameState &state);

};

