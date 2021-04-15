#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../HeaderFiles/Projectile.h"
#include "Character.h"
using namespace sf;

class Enemy : public Character {
protected:
    int ID;
    int xpDrop;
    float actionstime = 0;
    vector<int> actions{0,0,0,0,0,0};

    struct EnemyState {
        virtual ~EnemyState() {};
        virtual void handleInput(Enemy& ene, Time& timein, RenderWindow& window, View &playerView) = 0;
        virtual void update(Enemy& ene) = 0;
    };

    struct StandingState : public EnemyState {
        virtual void handleInput(Enemy& ene, Time& timein, RenderWindow& window, View &playerView) = 0;
        virtual void update(Enemy& ene) = 0;
    };

    struct JumpingState : public EnemyState {
        virtual void handleInput(Enemy& ene, Time& timein, RenderWindow& window, View &playerView) = 0;
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
    void checkMelee();
    void updatePosition(Time& time, RenderWindow& window, View &playerView);
};

/// Fighter
// Shoots at player and runs around
class Fighter : public Enemy {
protected:
    int rectWidthDef;
    int rectHeightDef;
    int rectLeftA;
    int rectLeftW;
    int rectLeftI;
    static int kb;

    Clock clock;
    int offset;
    Time animTime;
    int frameTime;

public:
    // Constructors
    Fighter(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY);
    // Setters
    void setAnimation(string animation);
    void setAttackAnim();
    void setResumeAttack();
    void setWalkAnim();
    void setIdleAnim();
    // Mutators
    void setActions(float time);

    // States
    struct StandingState : public Enemy::StandingState {
        void handleInput(Enemy& ene, Time& timein, RenderWindow& window, View &playerView);
        void update(Enemy& ene);
    };
/*    struct JumpingState : public Enemy::JumpingState {
        void handleInput(Enemy& ene, Time& timein, RenderWindow& window, View &playerView);
        void update(Enemy& ene);
    };*/

};

/// Wanderer
// Wanders back and forth like a goomba
class Wanderer : public Enemy {
public:
    // Constructors
    Wanderer(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY);
    // Setters
    void setAnimation(string animation);
    // Mutators
    void setActions(float time);
    //Special Functions
    void updateFaceright();
    // States
    struct StandingState : public Enemy::StandingState {
        void handleInput(Enemy& ene, Time& timein, RenderWindow& window, View &playerView);
        void update(Enemy& ene);
    };
    struct JumpingState : public Enemy::JumpingState {
        void handleInput(Enemy& ene, Time& timein, RenderWindow& window, View &playerView);
        void update(Enemy& ene);
    };


};
