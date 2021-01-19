#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Platforms.h"

class Hero{
private:
    string name;
    int level;
    int vitality;
    int health;
    int strength;
    bool jumping;
    float jumpvel;
    Texture text;
    Sprite sprite;


public:
    int experience;

    Hero();

    bool checkCollison(vector<Platforms>& borders);
    void updatePostion(vector<Platforms>& borders);
    Sprite& getSprite();
};