#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include <stack>
#include <fstream>
#include "GameState.h"
#include "Game.h"
#include "../irrXML/irrXML.h"
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
    std::map<std::string, sf::Keyboard::Key> *controlMapping;


    SoundBuffer moveBuffer;
    Sound moveSound;
    SoundBuffer errorBuffer;
    Sound errorSound;
    SoundBuffer confirmBuffer;
    Sound confirmSound;

public:
    Pause(float width, float height, std::map<std::string, sf::Keyboard::Key>* controlMapping);
    void Draw(RenderWindow &window);
    void MoveUp();
    void MoveDown();
    void SaveGame(Game &game, int slot);
    void LoadGame(Game &game, int slot);

    void PollMenu(RenderWindow &window, GameState &state, Game &game);

};

