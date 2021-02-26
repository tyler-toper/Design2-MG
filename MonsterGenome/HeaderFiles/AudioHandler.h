#pragma once
#include "GameState.h"
#include <iostream>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;


class AudioHandler{
private:
    GameState::State state;
    Music theme;
    SoundBuffer buffer;
    Sound sound;
    bool stateChanged;

public:
    AudioHandler();
    void setState(GameState::State newState);
    void playMusic();
};