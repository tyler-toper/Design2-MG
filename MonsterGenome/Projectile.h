#include <math.h>
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Platforms.h"
using namespace std;
using namespace sf;

class Projectile {
private:
    string name;
    Texture text;
    Sprite sprite;

    float xvel;
    float yvel;

public:
    Projectile(String path, float col, float row, float colend, float rowend, float dir);
    Sprite& getSprite();
    bool update(vector<Platforms*>& borders, Time& timein);
    bool checkCollision(vector<Platforms*>& borders);
};