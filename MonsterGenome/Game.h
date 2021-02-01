#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Character.h"
#include "Platforms.h"
#include "StateManager.h"
using namespace std;
using namespace sf;


class Game {
private:
    vector<Character*> players;
    vector<Platforms*> borders;
    vector<Projectile*> projs;

public:
    explicit Game();

    void PollGame(RenderWindow &window, Time& time);
    void Draw(RenderWindow &window, Time& time);

};