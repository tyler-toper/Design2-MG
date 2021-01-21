#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Projectile.h"

class Hero{
private:
    string name;
    int level;
    int vitality;
    int health;
    int strength;
    bool jumping;
    float jumpvel;
    float horizontalvel;
    Texture text;
    Sprite sprite;

    //should be in weapons firerate
    float weapontimer;

public:
    int experience;

    Hero();

    bool checkCollison(vector<Platforms*>& borders);
    void updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj, Time& time, RenderWindow& window);
    void attack(vector<Projectile*>& borders, Vector2i loc);
    Sprite& getSprite();
};