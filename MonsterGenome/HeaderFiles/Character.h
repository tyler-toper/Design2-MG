#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../HeaderFiles/Projectile.h"
using namespace sf;

const float GRAV = 1100.f;

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
    float vertadd = 0.f;
    float horizadd = 0.f;
    Texture text;
    Sprite sprite;
    int experience;
    vector<Platforms*>* borders;
    vector<Projectile*>* proj;
    vector<Character*>* actors;

    float timepass = .5f;
    //make enemy
    bool ene;
    //should be in weapons firerate
    float weapontimer = 0.f;
    /// Movement
    // Walking and Running
    float horizontalvel;
    float baseHorizontalvel;
    float maxHorizontalvel;
    float horizontalAcc;
    // Jumping
    float baseJumpHeight = 0.f;
    float jumpHeight = 0.f;

    // Private Functions
    int aboveBelow(Sprite& first, Sprite& second);
    int rightLeft(Sprite& first, Sprite& second);
public:
    // Constructors
    Character(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, bool ene);
    // Getters
    Sprite& getSprite();
    bool getAttack();
    bool getEnemy();
    int getHealth();
    // Setters
    // Mutators
    void checkCollison();
    void removeCollision(Platforms* borders, FloatRect& intersection);
    void checkProjectile();
    virtual void checkMeleeHit();
    virtual void updatePosition(Time& time, RenderWindow& window, View &playerView) = 0;
    void attack(vector<Projectile*>* borders, Vector2f loc);
    virtual void setAnimation() = 0;
    void flip(Sprite& sprite);
    void hAnimation();
    void mAnimation();
    void setAdditions(float v, float h);
    virtual void jump();
};

class Hero : public Character {
private:
    class HeroState {
    public:
        virtual ~HeroState() {};
        virtual void handleInput(Hero& hero, Time& timein, RenderWindow& window, View &playerView) {};
        virtual void update(Hero& Hero) {};
    };

    class StandingState : public HeroState {
    public:
        void handleInput(Hero& hero, Time& timein, RenderWindow& window, View &playerView);
        void update(Hero& hero);
    };

    class JumpingState : public HeroState {
    public:
        void handleInput(Hero& hero, Time& timein, RenderWindow& window, View &playerView);
        void update(Hero& hero);
    };
    std::map<std::string, sf::Keyboard::Key>* controlMapping;
    HeroState* state_;

public:
    // Constructor
    Hero(std::map<std::string, sf::Keyboard::Key>* controlMapping, vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY);
    // Setters
    void setAnimation();
    // Getters
    // Mutators
    void updatePosition(Time& timein, RenderWindow& window, View &playerView);
    void run(bool isRunning);
};