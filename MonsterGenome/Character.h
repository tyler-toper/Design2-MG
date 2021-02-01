#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Projectile.h"
using namespace sf;

class Character{
    protected:
        string name;
        int level;
        int health;
        int armor;
        int strength;
        int vitality;
        bool jumping;
        bool faceright = true;
        float jumpvel;
        float horizontalvel;
        Texture text;
        Sprite sprite;
        int experience; 

        float timepass;
        //make enemy
        bool ene;
        //should be in weapons firerate
        float weapontimer = 0.f;
    
    public:
    

    Character(bool ene);
    void checkCollison(vector<Platforms*>& borders);
    void removeCollision(Platforms* borders, FloatRect& intersection);
    void checkProjectile(vector<Projectile*>& proj);
    virtual void updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj, Time& time, RenderWindow& window);
    void attack(vector<Projectile*>& borders, Vector2i loc);
    void setAnimation();
    void flip(Sprite& sprite);
    void hAnimation();
    Sprite& getSprite();
};

class Hero : public Character {
private:

public:
    Hero();
};

class Enemy : public Character{
private:
    int ID;
    int xpDrop;
    float actionstime = 0;
    vector<int> actions{0,0,0,0,0};
    public:

    Enemy();
    void updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj, Time& time, RenderWindow& window);
    void setAnimation(vector<int>& actions);
};