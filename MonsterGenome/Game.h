#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Hero.h"
#include "Platforms.h"
#include "GameState.h"
using namespace std;
using namespace sf;


class Game {
private:
    Hero hero;
    vector<Platforms*> borders;
    vector<Projectile*> projs;

public:
    explicit Game();

    void PollGame(RenderWindow &window, Time& time, GameState &state);
    void Draw(RenderWindow &window, Time& time, View &playerView, View &mapView);

};