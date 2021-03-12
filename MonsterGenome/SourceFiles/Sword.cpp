#include "../HeaderFiles/Sword.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
using namespace sf;
using namespace std;

Sword::Sword(unsigned level, string textureFile):MeleeWeapon(level, textureFile){
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
    cout << sw.x << "and " << sw.y << endl;
    weapSprite.setPosition(sw.x + 20.f, sw.y + 45.f);
    window.draw(weapSprite);

}

void Sword::renderLeft(RenderWindow& window, View &playerView){

    Vector2f sw = playerView.getCenter();
    weapSprite.setPosition(sw.x + -20.f, sw.y + 45.f);

    weapSprite.scale(-1.f, 1.f);
    window.draw(weapSprite);
}


void Sword::update(RenderWindow& window, View &playerView){
/*    Vector2f sw = playerView.getCenter();
    weapSprite.setPosition(sw.x + 20.f, sw.y + 45.f);*/


}

/*void Sword::updateRight(RenderWindow& window, View &playerView){
    Vector2f sw = playerView.getCenter();
        weapSprite.setPosition(sw.x + 20.f, sw.y + 45.f);

}

void Sword::updateLeft(RenderWindow& window, View &playerView){
    Vector2f sw = playerView.getCenter();

        weapSprite.scale(-1.f, 1.f);
        weapSprite.setPosition(sw.x + -20.f, sw.y + 45.f);
}*/

void Sword::render(RenderWindow& window, View &playerView){

    //Vector2f sw = playerView.getCenter();

    //weapSprite.setPosition(sw.x + 20.f, sw.y + 45.f);
    window.draw(weapSprite);

}
