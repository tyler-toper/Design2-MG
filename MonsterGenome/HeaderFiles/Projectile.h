#pragma once
#include <math.h>
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../HeaderFiles/Platforms.h"
using namespace std;
using namespace sf;

class Projectile {
private:
    string name;
    bool ene;
    Texture text;
    Sprite sprite;

    float xvel;
    float yvel;

public:
    Projectile(String path, float col, float row, float colend, float rowend, bool ene);
    Sprite& getSprite();
    bool getEnemy();
    bool update(vector<Platforms*>& borders, Time& timein);
    bool checkCollision(vector<Platforms*>& borders);
};