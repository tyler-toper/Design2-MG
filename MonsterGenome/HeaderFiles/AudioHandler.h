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
    bool playing;
    bool changedState;
public:
    AudioHandler();
    void setState(GameState::State newState);
    void playMusic();
};