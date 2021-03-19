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
#define StartMenuOptions 5

class StartMenu{
private:
    int selected;
    int entered;
    std::map<std::string, sf::Keyboard::Key> *controlMapping;

    int xValue;
    int yValue[StartMenuOptions - 1];

    Texture menu;
    Sprite menuSprite;
    Texture background;
    Sprite backgroundSprite;
    Texture startButton;
    Sprite startButtonSprite;
    Texture enteredBox;
    Sprite enteredBoxSprite;
    Texture selectedBox;
    Sprite selectedBoxSprite;

    SoundBuffer moveBuffer;
    Sound moveSound;
    SoundBuffer errorBuffer;
    Sound errorSound;
    SoundBuffer confirmBuffer;
    Sound confirmSound;

public:

    StartMenu(float width, float height, std::map<std::string, sf::Keyboard::Key>* controlMapping);
    void PollMenu(RenderWindow &window, GameState &state);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();


};