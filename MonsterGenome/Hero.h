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
    bool faceright = true;
    float jumpvel;
    float horizontalvel;
    Texture text;
    Sprite sprite;

    float timepass;
    //make enemy
    bool ene;
    //should be in weapons firerate
    float weapontimer = 0.f;

public:
    int experience;

    Hero(bool ene = true);

    bool checkCollison(vector<Platforms*>& borders);
    void checkProjectile(vector<Projectile*>& proj);
    void updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj, Time& time, RenderWindow& window);
    void attack(vector<Projectile*>& borders, Vector2i loc);
    void setAnimation();
    void flip(Sprite& sprite);
    void hAnimation();
    Sprite& getSprite();
};