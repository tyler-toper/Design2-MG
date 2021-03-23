#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../HeaderFiles/Projectile.h"
#include "../HeaderFiles/Items.h"
#include "../HeaderFiles/Inventory.h"
#include "../HeaderFiles/Sword.h"
#include "../HeaderFiles/Pistol.h"
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
        bool punch = false;
        bool atk = false;
        bool faceright = true;
        float jumpvel;
        float horizontalvel;
        float vertadd = 0.f;
        float horizadd = 0.f;
        Texture text;
        Sprite sprite;
        int experience;

        bool equipSw = false;
        int swToggle = 0;
        bool equipPis = false;
        int pisToggle = 0;


        Inventory* inventory;
        Sword* sword;
        Pistol* pistol;
        float timepass = .5f;
        //make enemy
        bool ene;
        //should be in weapons firerate
        float weapontimer = 0.f;
        //Sword sword;

    
    public:
    

    Character(bool ene);
    void checkCollison(vector<Platforms*>& borders);
    void removeCollision(Platforms* borders, FloatRect& intersection);
    void checkProjectile(vector<Projectile*>& proj);
    virtual void checkMeleeHit(vector<Character*>& players);
    virtual void updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj,vector<Character*>& players, Time& time, RenderWindow& window) = 0;
    void attack(vector<Projectile*>& borders, Vector2i loc);
    virtual void setAnimation() = 0;
    void flip(Sprite& sprite);
    void hAnimation();
    void mAnimation();
    void setAdditions(float v, float h);
    Sprite& getSprite();
    bool getAttack();
    bool getEnemy();
    int getHealth();
    void equipWeapon(RenderWindow& window, View &playerView);
    void animWeapon(RenderWindow& window, View& playerView);
};

class Hero : public Character {
private:
    std::map<std::string, sf::Keyboard::Key>* controlMapping;
public:
    Hero(std::map<std::string, sf::Keyboard::Key>* controlMapping, float spawnX, float spawnY);

    void setAnimation();
    void updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj, vector<Character*>& players, Time& timein, RenderWindow& window);

};

class Enemy : public Character{
private:
    int ID;
    int xpDrop;
    float actionstime = 0;
    vector<int> actions{0,0,0,0,0,0};
    public:

    Enemy(float spawnX, float spawnY);
    void updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj, vector<Character*>& players, Time& time, RenderWindow& window);
    void setAnimation();
    void checkMeleeHit(vector<Character*>& players);
};