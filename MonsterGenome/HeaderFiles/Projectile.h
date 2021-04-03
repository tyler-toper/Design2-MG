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
    int damage;

    float xvel;
    float yvel;

public:
    Projectile(String path, float col, float row, bool faceright, bool ene, int damage);
    Sprite& getSprite();
    bool getEnemy();
    int getDamage();
    bool update(vector<Platforms*>& borders, Time& timein);
    bool checkCollision(vector<Platforms*>& borders);
};