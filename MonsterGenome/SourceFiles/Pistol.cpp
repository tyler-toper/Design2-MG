#include "../HeaderFiles/Pistol.h"
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;

Pistol::Pistol(unsigned level, string textureFile):RangedWeapon(level, textureFile){
    this->weapSprite.setOrigin(this->weapSprite.getGlobalBounds().width/2.f,
                               this->weapSprite.getGlobalBounds().height);
}

Pistol::~Pistol(){

}

Pistol* Pistol::clone() {
    return new Pistol(*this);
}


void Pistol::renderRight(RenderWindow& window, View &playerView){
    Vector2f sw = playerView.getCenter();
    weapSprite.setPosition(sw.x + 20.f, sw.y + 48.f);
    if(flipped && first!=0){
        weapSprite.scale(-1.f, 1.f);
        flipped = false;
    }
    if(first==0){
        first++;
    }

    window.draw(weapSprite);

}

void Pistol::renderLeft(RenderWindow& window, View &playerView){
    Vector2f sw = playerView.getCenter();
    weapSprite.setPosition(sw.x + -20.f, sw.y + 48.f);
    if(!flipped){
        weapSprite.scale(-1.f, 1.f);
    }
    flipped = true;

    window.draw(weapSprite);
}


void Pistol::update(RenderWindow& window, View &playerView){

}
