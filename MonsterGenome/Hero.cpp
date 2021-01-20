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

        //should be in weapons firerate
        float weapontimer = 0.f;

    }

    bool Hero::checkCollison(vector<Platforms*>& borders){
        for(int i=0; i < borders.size(); i++){
            if(sprite.getGlobalBounds().intersects(borders[i]->getSprite().getGlobalBounds())){
                return true;
            }
        }
        return false;
    }

    void Hero::updatePostion(vector<Platforms*>& borders, vector<Projectile*>& proj, Time& timein){
            //Gravity and collision when jumpin
            float time = timein.asSeconds();
            weapontimer = weapontimer - time;
            jumpvel += 1100.f * time; // Vertical Acceleration 

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
                facing = -1.f;
                sprite.move(Vector2f(-1.f * horizontalvel * time, 0));
                if(checkCollison(borders)){
                    sprite.move(Vector2f(horizontalvel * time, 0));
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Right)){
                facing = 1.f;
                sprite.move(Vector2f(horizontalvel * time, 0));
                if(checkCollison(borders)){
                    sprite.move(Vector2f(-1.f * horizontalvel * time, 0));
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Up) & !jumping){
                jumping = true;
                jumpvel = -400.f;
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
            //Attacking
            if(Keyboard::isKeyPressed(Keyboard::Z)){
                attack(proj);
            }
    }

    Sprite& Hero::getSprite(){
        return this->sprite;
    }

    void Hero::attack(vector<Projectile*>& proj){
        if(weapontimer <= 0.f){
            proj.push_back(new Projectile("Images/shot.png", sprite.getPosition().x, sprite.getPosition().y, facing));
            weapontimer = 1.f;
        }
    }    

