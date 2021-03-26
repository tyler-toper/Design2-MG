#include "../HeaderFiles/Sword.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
using namespace sf;
using namespace std;

Sword::Sword(unsigned level, string textureFile):MeleeWeapon(level, textureFile){
    this->weapSprite.setTextureRect(IntRect (0,0,recWidth,recHeight));
    this->weapSprite.setOrigin(this->weapSprite.getGlobalBounds().width/2.f,
                               this->weapSprite.getGlobalBounds().height);
}

Sword::~Sword(){

}

Sword* Sword::clone() {
    return new Sword(*this);
}


void Sword::renderRight(RenderWindow& window, View &playerView){

    Vector2f sw = playerView.getCenter();
    weapSprite.setPosition(sw.x + 20.f, sw.y + 48.f);
    if(flipped && first!=0){
        weapSprite.scale(-1.f, 1.f);
        flipped = false;
    }
    if(first==0){
        first++;
    }
    window.setView(playerView);
    window.draw(weapSprite);
}

void Sword::renderLeft(RenderWindow& window, View &playerView){
    Vector2f sw = playerView.getCenter();
    weapSprite.setPosition(sw.x + -20.f, sw.y + 48.f);
    if(!flipped){
        weapSprite.scale(-1.f, 1.f);
    }
    flipped = true;
    
    window.setView(playerView);
    window.draw(weapSprite);
}

void Sword::attackAnim(RenderWindow &window, View &playerView) {
    if(rectLeft < 288){
        rectLeft += 48;
        this->weapSprite.setTextureRect(IntRect(rectLeft,0,recWidth, recHeight));
    }
    else if(rectLeft >= 288){
        rectLeft = 48;
        this->weapSprite.setTextureRect(IntRect(rectLeft,0,recWidth, recHeight));
    }
}

void Sword::resetAnim(RenderWindow &window, View &playerView) {
    this->weapSprite.setTextureRect(IntRect (0,0,recWidth,recHeight));
}


void Sword::update(RenderWindow& window, View &playerView){

}

