#include "Hero.h"
using namespace std;
using namespace sf;

Hero::Hero(){
    name = "player";
    level = 0;
    experience = 0;
    vitality = 0;
    strength = 0;
    health = 100;
    jumping = false;
    jumpvel = 0;
    text.loadFromFile("../Images/example.png");
    sprite.setTexture(text);
    sprite.setPosition(Vector2f(400.f, 300.f));
}

bool Hero::checkCollision(vector<Platforms>& borders){
    for(int i=0; i < borders.size(); i++){
        if(sprite.getGlobalBounds().intersects(borders[i].getSprite().getGlobalBounds())){
            return true;
        }
    }
    return false;
}

void Hero::updatePosition(vector<Platforms>& borders){
    //Gravity and collision when jumping
    jumpvel += .01; // Vertical Acceleration
    sprite.move(Vector2f(0, jumpvel));
    if(checkCollision(borders)){
        sprite.move(Vector2f(0, -1.f * jumpvel));
        if(jumpvel > 0){
            jumping = false;
        }
        jumpvel = 0;
    }

    //Moving Left and Right with Collision
    if(Keyboard::isKeyPressed(Keyboard::Left)){
        sprite.move(Vector2f(-.15, 0));
        if(checkCollision(borders)){
            sprite.move(Vector2f(.15, 0));
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::Right)){
        sprite.move(Vector2f(.15, 0));
        if(checkCollision(borders)){
            sprite.move(Vector2f(-.15, 0));
        }
    }
    if(Keyboard::isKeyPressed(Keyboard::Up) & !jumping){
        jumping = true;
        jumpvel = -2;
        sprite.move(Vector2f(0, jumpvel));
        if(checkCollision(borders)){
            sprite.move(Vector2f(0, 1/10.f));
        }
    }

    //Unfinsihed, will be ducking or something
    if(Keyboard::isKeyPressed(Keyboard::Down)){

        if(checkCollision(borders)){
            sprite.move(Vector2f(0.f, -.15));
        }
    }
}

Sprite& Hero::getSprite(){
    return this->sprite;
}