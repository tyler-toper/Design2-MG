#include <SFML/Graphics.hpp>
#include "../HeaderFiles/Weapons.h"

using namespace std;
using namespace sf;

void Weapons::initValues() {

    this->level = 0;
    this->attackTimer.restart();
    this->attackTimerMax =  500;

}

Weapons::~Weapons() {

}
Weapons::Weapons(unsigned level, string textureFile) : Items(level) {
    this->initValues();
    this->weapTexture.loadFromFile(textureFile);
    this->weapSprite.setTexture(this->weapTexture);

}

/*Weapons::Weapons(unsigned level, unsigned damage, string textureFile) : Items(level) {
    this->initValues();
    this->damage = damage;
    //this->weapSprite.setTexture(this->weapTexture);
    this->weapTexture.loadFromFile(textureFile);
    this->weapSprite.setTexture(this->weapTexture);

}*/


const bool Weapons::getAttackTimer() {
    if(this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax){
        this->attackTimer.restart();
        return true;
    }
    return false;
}