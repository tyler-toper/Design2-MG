#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
using namespace std;
using namespace sf;


class Game {
private:
    bool state;

public:
    Game(RenderWindow &window);

    bool GetState() const;
    void SetState(bool NewState);

};


