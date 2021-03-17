#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "GameState.h"
using namespace std;
using namespace sf;

#define pixelFont "../../Assets/Fonts/PixelFont.ttf"
#define MenuOptions 3

class SaveMenu{
private:
    int selected;
    std::map<std::string, sf::Keyboard::Key> *controlMapping;

    Texture menu;
    Sprite menuSprite;

    SoundBuffer moveBuffer;
    Sound moveSound;
    SoundBuffer errorBuffer;
    Sound errorSound;
    SoundBuffer confirmBuffer;
    Sound confirmSound;

public:

    SaveMenu(float width, float height, std::map<std::string, sf::Keyboard::Key>* controlMapping);
    void PollMenu(RenderWindow &window, GameState &state);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();


};