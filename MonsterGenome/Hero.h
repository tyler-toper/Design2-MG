#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Projectile.h"

class Hero{
    enum State
    {
        STATE_STANDING,
        STATE_JUMPING
    };

private:
    string name;
    int level;
    int vitality;
    int health;
    int strength;
    int experience;
    State state_ = STATE_STANDING;
    bool jumping;
    float jumpvel;
    float horizontalvel;
    Texture text;
    Sprite sprite;
    std::map<std::string, Keyboard::Key> controls;

    //should be in weapons fire rate
    float weapontimer;

public:
    /// Constructors
    Hero();

    /// Getters
    Sprite& getSprite();
    string getName();
    int getExperience();
    bool checkCollision(vector<Platforms*>& borders);

    /// Setters
    // Could use a different structure than map, but need to settle on how controls are saved.
    void setControls(std::map<std::string, Keyboard::Key> newControls);

    /// Mutators
    void updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj, Time& time, RenderWindow& window);
    void updateState();
    void attack(vector<Projectile*>& borders, Vector2i loc);
};