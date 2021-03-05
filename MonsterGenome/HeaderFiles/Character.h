#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../HeaderFiles/Projectile.h"
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

        float timepass = .5f;
        //make enemy
        bool ene;
        //should be in weapons firerate
        float weapontimer = 0.f;
    public:
    

    Character(bool ene);
    void checkCollison(vector<Platforms*>& borders);
    void removeCollision(Platforms* borders, FloatRect& intersection);
    void checkProjectile(vector<Projectile*>& proj);
    virtual void checkMeleeHit(vector<Character*>& players);
    virtual void updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj,vector<Character*>& players, Time& time, RenderWindow& window) = 0;
    void attack(vector<Projectile*>* borders, Vector2i loc);
    virtual void setAnimation() = 0;
    void flip(Sprite& sprite);
    void hAnimation();
    void mAnimation();
    void setAdditions(float v, float h);
    Sprite& getSprite();
    bool getAttack();
    bool getEnemy();
    int getHealth();
};

class Hero : public Character {
private:

    class HeroState {
    public:
        virtual ~HeroState() {};
        virtual void handleInput(Hero& hero, Time& timein, RenderWindow& window) {};
        virtual void update(Hero& Hero) {};
        // TODO: In order to do static classes, we need to declare them here
        // However the code fails because it hasn't seen the states yet
//        static StandingState standing;
//        static JumpingState jumping;
    };

    class StandingState : public HeroState {
    public:
        void handleInput(Hero& hero, Time& timein, RenderWindow& window);
        void update(Hero& hero);
    };

    class JumpingState : public HeroState {
    public:
        void handleInput(Hero& hero, Time& timein, RenderWindow& window);
        void update(Hero& hero);
    };
    vector<Platforms*>* borders; 
    vector<Projectile*>* proj;
    vector<Character*>* players;
    std::map<std::string, sf::Keyboard::Key>* controlMapping;
    HeroState* state_;
public:
    Hero(std::map<std::string, sf::Keyboard::Key>* controlMapping, vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* players);
    void setAnimation();
    void updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj,vector<Character*>& players,Time& timein, RenderWindow& window);
};

class Enemy : public Character{
private:
    int ID;
    int xpDrop;
    float actionstime = 0;
    vector<int> actions{0,0,0,0,0,0};
    public:

    Enemy();
    void updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj, vector<Character*>& players, Time& time, RenderWindow& window);
    void setAnimation();
    void checkMeleeHit(vector<Character*>& players);
};