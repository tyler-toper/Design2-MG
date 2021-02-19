#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "../HeaderFiles/Character.h"
#include "../HeaderFiles/Platforms.h"
#include "../HeaderFiles/GameState.h"
using namespace std;
using namespace sf;


class Game {
private:
    vector<Character*> players;
    vector<Platforms*> borders;
    vector<Projectile*> projs;
    std::map<std::string, sf::Keyboard::Key> *controlMapping;

public:
    explicit Game(std::map<std::string, sf::Keyboard::Key>* controlMapping);

    void PollGame(RenderWindow &window, Time& time, GameState &state);
    void Draw(RenderWindow &window, Time& time, View &playerView, View &mapView);

};