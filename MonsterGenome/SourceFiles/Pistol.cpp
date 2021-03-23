#include "../HeaderFiles/Pistol.h"
#include <SFML/Graphics.hpp>
#include <cmath>
using namespace sf;

Pistol::Pistol(unsigned level, string textureFile):RangedWeapon(level, textureFile){
    this->weapSprite.setTextureRect(IntRect (0,0,recWidth,recHeight));
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
    weapSprite.setPosition(sw.x + 32.f, sw.y + 42.f);
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
    weapSprite.setPosition(sw.x + -32.f, sw.y + 42.f);
    if(!flipped){
        weapSprite.scale(-1.f, 1.f);
    }
    flipped = true;

    window.draw(weapSprite);
}

void Pistol::attackAnim(RenderWindow &window, View &playerView) {
    if(rectLeft < 768){
        rectLeft += 64;
        this->weapSprite.setTextureRect(IntRect(rectLeft,0,recWidth, recHeight));
    }
    else if(rectLeft >= 768){
        rectLeft = 64;
        this->weapSprite.setTextureRect(IntRect(rectLeft,0,recWidth, recHeight));
    }
}

void Pistol::resetAnim(RenderWindow &window, View &playerView) {
    this->weapSprite.setTextureRect(IntRect (0,0,recWidth,recHeight));
}


void Pistol::update(RenderWindow& window, View &playerView){

}
