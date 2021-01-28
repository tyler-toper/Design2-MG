#include "Hero.h"
using namespace std;
using namespace sf;

    Hero::Hero(bool ene){
        name = "player";
        level = 0;
        experience = 0;
        vitality = 0;
        strength = 0;
        health = 100;
        jumping = false;
        jumpvel = 0;
        horizontalvel = 100.f;
        text.loadFromFile("../Images/animation.png");
        sprite.setTexture(text);
        sprite.setPosition(Vector2f(400.f, 300.f));
        sprite.setTextureRect(IntRect(57, 11, 50, 60));
        //remove soon
        ene = ene;
        float timepass = .05;
        //should be in weapons firerate

    }

    bool Hero::checkCollison(vector<Platforms*>& borders){
        for(int i=0; i < borders.size(); i++){
            if(sprite.getGlobalBounds().intersects(borders[i]->getSprite().getGlobalBounds())){
                return true;
            }
        }
        return false;
    }

    void Hero::checkProjectile(vector<Projectile*>& proj){
        for(int i=0; i < proj.size(); i++){
            Projectile* temp = proj[i];
            if(temp->getEnemy() != this->ene & sprite.getGlobalBounds().intersects(temp[i].getSprite().getGlobalBounds())){
                delete proj[i]; 
                proj.erase(proj.begin() + i);
                i--;
                health -= 10;
                cout << health << endl;
            }
        }
    }

    void Hero::flip(Sprite& sprite){
        sprite.setOrigin({ sprite.getGlobalBounds().width/2.0f, 0});
        sprite.setScale({ pow(-1, int(!faceright)) , 1 });
    }

    void Hero::hAnimation(){
        if(sprite.getTextureRect().top != 242 | sprite.getTextureRect().left == 396){
                    sprite.setTextureRect(IntRect(36, 242, 50, 60));
                }
                else{
                    sprite.setTextureRect(IntRect(sprite.getTextureRect().left+60, sprite.getTextureRect().top, 50, 60));                    
                }
    }

    void Hero::setAnimation(){
        bool noaction = true;
        if(timepass <= 0){
            if(Keyboard::isKeyPressed(Keyboard::Left) | Keyboard::isKeyPressed(Keyboard::Right)){
                hAnimation();
                noaction = false;
            }
            if(Keyboard::isKeyPressed(Keyboard::Up) & !jumping){
                noaction = false;
            }
            //Unfinsihed, will be ducking or something
            if(Keyboard::isKeyPressed(Keyboard::Down)){
                noaction = false;
            }
            //Attacking
            if(Keyboard::isKeyPressed(Keyboard::Z)){
                noaction = false;
            }
            timepass = .1;
            if(noaction){
            sprite.setTextureRect(IntRect(57, 11, 53, 60));
        }
        }
        flip(sprite);
    }

    void Hero::updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj, Time& timein, RenderWindow& window){
            //Gravity and collision when jumpin
            float time = timein.asSeconds();
            weapontimer = weapontimer - time;
            timepass = timepass - time;
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
                faceright = false;
                sprite.move(Vector2f(-1.f * horizontalvel * time, 0));
                if(checkCollison(borders)){
                    sprite.move(Vector2f(horizontalvel * time, 0));
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Right)){
                faceright = true;
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
                attack(proj, Mouse::getPosition(window));
            }   
            setAnimation();
    }

    Sprite& Hero::getSprite(){
        return this->sprite;
    }

    void Hero::attack(vector<Projectile*>& proj, Vector2i loc){
        if(weapontimer <= 0.f){
            proj.push_back(new Projectile("../Images/shot.png", sprite.getPosition().x, sprite.getPosition().y, (float)loc.x, (float)loc.y, ene));
            weapontimer = 1.f;
        }
    }    

