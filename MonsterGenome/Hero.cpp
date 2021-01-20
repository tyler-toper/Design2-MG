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
        horizontalvel = 100.f;
        text.loadFromFile("Images/example.png");
        sprite.setTexture(text);
        sprite.setPosition(Vector2f(400.f, 300.f));
    }

    bool Hero::checkCollison(vector<Platforms>& borders){
        for(int i=0; i < borders.size(); i++){
            if(sprite.getGlobalBounds().intersects(borders[i].getSprite().getGlobalBounds())){
                return true;
            }
        }
        return false;
    }

    void Hero::updatePostion(vector<Platforms>& borders, Time& timein){
            //Gravity and collision when jumpin
            float time = timein.asSeconds();
            jumpvel += 200.f * time; // Vertical Acceleration 
            sprite.move(Vector2f(0, jumpvel * time));
            if(checkCollison(borders)){
                sprite.move(Vector2f(0, -1.f * jumpvel * time));
                if(jumpvel > 0){
                    jumping = false;
                }
                jumpvel = 0;
            }
            
            //Moving Left and Right with Collision
            if(Keyboard::isKeyPressed(Keyboard::Left)){
                sprite.move(Vector2f(-1.f * horizontalvel * time, 0));
                if(checkCollison(borders)){
                    sprite.move(Vector2f(horizontalvel * time, 0));
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Right)){
                sprite.move(Vector2f(horizontalvel * time, 0));
                if(checkCollison(borders)){
                    sprite.move(Vector2f(-1.f * horizontalvel * time, 0));
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Up) & !jumping){
                jumping = true;
                jumpvel = -150.f;
                sprite.move(Vector2f(0, jumpvel * time));
                if(checkCollison(borders)){
                    sprite.move(Vector2f(0, -1.f * jumpvel * time));
                }
            }

            //Unfinsihed, will be ducking or something
            if(Keyboard::isKeyPressed(Keyboard::Down)){
                
                if(checkCollison(borders)){
                    sprite.move(Vector2f(0.f, -.15));
                }
            }
    }

    Sprite& Hero::getSprite(){
        return this->sprite;
    }

