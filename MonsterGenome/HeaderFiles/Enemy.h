#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../HeaderFiles/Projectile.h"
#include "Character.h"
using namespace sf;

class Enemy : public Character{
protected:
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
        virtual void handleInput(Enemy& ene, Time& timein, RenderWindow& window);
        virtual void update(Enemy& ene);
    };

    class JumpingState : public EnemyState {
    public:
        virtual void handleInput(Enemy& ene, Time& timein, RenderWindow& window);
        virtual void update(Enemy& ene);
    };
    EnemyState* state_;
public:

    Enemy(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY);
    void checkMeleeHit();
    virtual void setAnimation() = 0;
    virtual void updatePosition(Time& time, RenderWindow& window, View &playerView);
};

/// Fighter
class Fighter : public Enemy {
public:

    Fighter(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY);
    void setAnimation();
};