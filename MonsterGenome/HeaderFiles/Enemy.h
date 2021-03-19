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

    struct EnemyState {
        virtual ~EnemyState() {};
        virtual void handleInput(Enemy& ene, Time& timein, RenderWindow& window) = 0;
        virtual void update(Enemy& ene) = 0;
    };

    struct StandingState : public EnemyState {
        virtual void handleInput(Enemy& ene, Time& timein, RenderWindow& window) = 0;
        virtual void update(Enemy& ene) = 0;
    };

    struct JumpingState : public EnemyState {
        virtual void handleInput(Enemy& ene, Time& timein, RenderWindow& window) = 0;
        virtual void update(Enemy& ene) = 0;
    };
    EnemyState* state_;
public:
    // Constructors
    Enemy(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY);
    // Getters
    EnemyState* getState();
    vector<int> getActions();
    // Setters
    void setState(EnemyState* newState);
    virtual void setAnimation(string animation) = 0;
    virtual void setActions(float time) = 0;
    // Mutators
    void checkMeleeHit();
    void updatePosition(Time& time, RenderWindow& window, View &playerView);
};

/// Fighter
class Fighter : public Enemy {
public:
    Fighter(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY);
    void setAnimation(string animation);
    void setActions(float time);
    struct StandingState : public Enemy::StandingState {
        void handleInput(Enemy& ene, Time& timein, RenderWindow& window);
        void update(Enemy& ene);
    };

    struct JumpingState : public Enemy::JumpingState {
        void handleInput(Enemy& ene, Time& timein, RenderWindow& window);
        void update(Enemy& ene);
    };

};