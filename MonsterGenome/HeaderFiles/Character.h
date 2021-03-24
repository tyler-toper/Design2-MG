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
        vector<Platforms*>* borders; 
        vector<Projectile*>* proj;
        vector<Character*>* players; 

        float timepass = .5f;
        //make enemy
        bool ene;
        //should be in weapons firerate
        float weapontimer = 0.f;

        friend class Pause;
    public:
    

    Character(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* players, bool ene);
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
    Sprite& getSprite();
    bool getAttack();
    bool getEnemy();
    int getHealth();
    string getName();
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
    Hero(std::map<std::string, sf::Keyboard::Key>* controlMapping, vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* players, float spawnX, float spawnY);
    void setAnimation();
    void updatePosition(Time& timein, RenderWindow& window, View &playerView);
};

class Enemy : public Character{
private:
    int ID;
    int xpDrop;
    float actionstime = 0;
    vector<int> actions{0,0,0,0,0,0};

    class EnemyState {
    public:
        virtual ~EnemyState() {};
        virtual void handleInput(Enemy& ene, Time& timein, RenderWindow& window) {};
        virtual void update(Enemy& ene) {};
    };

    class StandingState : public EnemyState {
    public:
        void handleInput(Enemy& ene, Time& timein, RenderWindow& window);
        void update(Enemy& ene);
    };

    class JumpingState : public EnemyState {
    public:
        void handleInput(Enemy& ene, Time& timein, RenderWindow& window);
        void update(Enemy& ene);
    };
    EnemyState* state_;
    public:

    Enemy(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* players, float spawnX, float spawnY);
    void updatePosition(Time& time, RenderWindow& window, View &playerView);
    void setAnimation();
    void checkMeleeHit();
};