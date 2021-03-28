#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>
#include "GameState.h"
#include "Game.h"
#include "../irrXML/irrXML.h"
using namespace std;
using namespace sf;

#define pixelFont "../../Assets/Fonts/PixelFont.ttf"
#define SaveLoadOptions 3


class SaveLoadMenu{
private:
    int selected;
    int entered;
    std::map<std::string, sf::Keyboard::Key> *controlMapping;

    int xValue;
    int yValue[4];

    bool errorFlag;
    Font font;
    Text error;
    Text text[4];

    Texture menu;
    Sprite menuSprite;
    Texture background;
    Sprite backgroundSprite;
    Texture saveButton;
    Sprite saveButtonSprite;
    Texture loadButton;
    Sprite loadButtonSprite;
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
    SoundBuffer backBuffer;
    Sound backSound;

public:

    SaveLoadMenu(float width, float height, std::map<std::string, sf::Keyboard::Key>* controlMapping);
    void SaveGame(Game &game, int slot);
    void LoadGame(Game &game, int slot);
    void PollMenu(RenderWindow &window, GameState &state, Game &game);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();
    void MoveRight();
    void MoveLeft();
    void Reset();
    void GetSaveTimes();
};