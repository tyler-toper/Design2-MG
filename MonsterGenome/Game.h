#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Hero.h"
#include "Platforms.h"
using namespace std;
using namespace sf;


class Game {
private:
    bool state;
    Hero hero;
    vector<Platforms*> borders;

public:
    explicit Game(RenderWindow &window);

    void PollGame(RenderWindow &window);
    void Draw(RenderWindow &window);
    bool GetState() const;
    void SetState(bool NewState);

};


