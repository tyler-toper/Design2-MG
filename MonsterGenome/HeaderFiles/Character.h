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

const float GRAV = 1100.f;

class Character{
protected:
    string name;
    int level;
    int health;
    int maxHealth;
    int armor;
    int strength;
    int vitality;
    bool punch = false;
    bool atk = false;
    bool checkpoint = false;
    bool faceright = true;
    float jumpvel;
    float vertadd = 0.f;
    float horizadd = 0.f;

    float vertaddKnock = 0.f;
    float horzaddKnock = 0.f;
    float horzAcel = 1100.f;
    int knockFrames = 5;

    Texture text;
    Sprite sprite;
    int experience;
    vector<Platforms*>* borders;
    vector<Projectile*>* proj;
    vector<Character*>* actors;
    Vector2f resetPoint;
    friend class StartMenu;
    friend class SaveLoadMenu;

public:
    float timepass = .5f;
    //make enemy
    bool ene;

    // Damage Invulerablity
    float invultimer = 0;
    float maxInvulTime = 1.0f;

    /// Movement
    // Walking and Running
    float horizontalvel;
    float baseHorizontalvel;
    float maxHorizontalvel;
    float horizontalAcc;

    // Jumping
    float baseJumpHeight = 0.f;
    float jumpHeight = 0.f;
    int jumpCount;
    int jumpCountMax;
    const int jumpCountAbsMax = 5;

    // Weapons
    Inventory* inventory;
    Sword* sword;
    Pistol* pistol;
    float weapontimer = 0.f;
    // Weapon Reload Time
    float reloadTime;
    // Character Reload Modifier
    float minCharReloadMod;
    float maxCharReloadMod;
    float charReloadMod;
    int charDamageMod;

    bool equipSw = false;
    int swToggle = 0;
    bool equipPis = false;
    int pisToggle = 0;

    // Private Functions
    int rightLeft(Sprite& first, Sprite& second);
    bool isAnyKeyPressed(std::map<std::string, sf::Keyboard::Key>* controlMapping);

public:
    // Constructors
    Character(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, bool ene);
    // Getters
    Sprite& getSprite();
    bool getAttack();
    bool getEnemy();
    bool getCheckPoint();
    int getHealth();
    int getMaxHealth();
    vector<Platforms*>* getBorders();
    Vector2f getReset();
    int aboveBelow(Sprite& first, Sprite& second);
    float getHorizontalVel();
    bool isFaceright();
    float getJumpVel();

    // Setters
    void setFaceright(bool newFaceright);
    void setHealth(int newHealth);
    void setMaxHealth(int newMaxHealth);
    void resetCheck();

    // Mutators
    void checkCollision();
    void removeCollision(Platforms* borders, FloatRect& intersection);
    void checkProjectile();
    virtual void checkMelee() = 0;
    virtual void updatePosition(Time& time, RenderWindow& window, View &playerView) = 0;
    void attack(vector<Projectile*>* borders);
    virtual void setAnimation(string animation) = 0;
    void flip(Sprite& sprite);
    void hAnimation();
    void mAnimation();
    void setAdditions(float v, float h);
    void setAdditionsKnock(float v, float h);
    void setKnockFrame();
    string getName();
    virtual void jump();
    void damageCharacter(int damageTaken);
    void healCharacter(int damageHealed);
};

class Hero : public Character {
private:
    // States
    class HeroState {
    public:
        virtual ~HeroState() {};
        virtual void handleInput(Hero &hero, Time &timein, RenderWindow &window, View &playerView) {};
        virtual void update(Hero &Hero) {};
    };

    class StandingState : public HeroState {
    public:
        void handleInput(Hero &hero, Time &timein, RenderWindow &window, View &playerView);
        void update(Hero &hero);
    };

    class JumpingState : public HeroState {
    public:
        void handleInput(Hero &hero, Time &timein, RenderWindow &window, View &playerView);
        void update(Hero &hero);
    };

    // Variables
    std::map<std::string, sf::Keyboard::Key> *controlMapping;
    HeroState *state_;

    // Jumping
    bool jumpingHeld;

public:
    // Constructor
    Hero(std::map<std::string, sf::Keyboard::Key> *controlMapping, vector<Platforms *> *borders,
         vector<Projectile *> *proj, vector<Character *> *actors, float spawnX, float spawnY);

    // Setters
    void setAnimation(string animation);
    void setJumpingHeld(bool state);
    // Getters
    int getJumpCount() const;
    bool isJumpingHeld() const;
    // Mutators
    void updatePosition(Time &timein, RenderWindow &window, View &playerView);
    void run(bool isRunning);
    void jump();
    void refreshJumps();
    void checkMelee();
    void weaponToggles(string key);
    void equipWeapon(RenderWindow& window, View &playerView);
    void animWeapon(RenderWindow& window, View& playerView);

    bool improveJumpCount();
    void modifyCharReloadMod(float change);
    void modifyCharDamageMod(int change);
    void modifyMoveSpeed(float change);
    void modifyJumpHeight(float change);
};