#include "../HeaderFiles/Character.h"
using namespace std;
using namespace sf;

    Character::Character(bool ene){
        int armor = 100;
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
        this->ene = ene;
        float timepass = .05;
        //should be in weapons fireratea

    }

    Hero::Hero(std::map<std::string, sf::Keyboard::Key>* controlMapping) : Character(false){
        this->controlMapping = controlMapping;
    }

    Enemy::Enemy() : Character(true) {
        int ID = 0;
        int xpDrop = 100;
    }

    void Character::setAdditions(float v, float h){
        this->vertadd = v;
        this->horizadd = h;
    }

    void Character::checkCollison(vector<Platforms*>& borders){
        setAdditions(0.f, 0.f);
        for(int i=0; i < borders.size(); i++){
            FloatRect intersection;
            if(sprite.getGlobalBounds().intersects(borders[i]->getSprite().getGlobalBounds(), intersection)){
                removeCollision(borders[i], intersection);
                if(borders[i]->getName() == "M"){
                    MovePlatform *d = static_cast<MovePlatform *>(borders[i]);
                    if((sprite.getPosition().y > borders[i]->getSprite().getPosition().y) && (d->getYspeed() > 0) && (abs(sprite.getPosition().x > ((borders[i]->getSprite().getPosition().x) - 53)))){
                        d->reverse();
                    }
                    else{
                        setAdditions(d->getXspeed(), abs(d->getYspeed()));
                    }
                }
            }
        }
    }

    void Character::removeCollision(Platforms* borders, FloatRect& intersection){
        if(intersection.width > intersection.height){
            sprite.move(0, intersection.height * -1.f * pow(-1, jumpvel < 0));
            if(intersection.width >= 1){
                    if(jumpvel > 0){
                        jumping = false;
                    }
                    jumpvel = 0;
                }
        }
        else{
            sprite.move(intersection.width * pow(-1, faceright), 0);   
        }
    }

    void Character::checkProjectile(vector<Projectile*>& proj){
        for(int i=0; i < proj.size(); i++){
            if((proj[i]->getEnemy() != this->ene) && sprite.getGlobalBounds().intersects(proj[i]->getSprite().getGlobalBounds())){
                delete proj[i]; 
                proj.erase(proj.begin() + i--);
                health -= 10;
            }
        }
    }

    void Character::flip(Sprite& sprite){
        sprite.setOrigin({ sprite.getGlobalBounds().width/2.0f, 0});
        sprite.setScale({ pow(-1, int(!faceright)) , 1 });
    }

    void Character::hAnimation(){
        if(sprite.getTextureRect().top != 242 | sprite.getTextureRect().left == 396){
            sprite.setTextureRect(IntRect(36, 242, 50, 60));
        }
        else{
            sprite.setTextureRect(IntRect(sprite.getTextureRect().left+60, sprite.getTextureRect().top, 50, 60));              
        }
    }
    void Hero::setAnimation(){
        bool noaction = true;
        // Needs to dereference controlMapping in order to read map
        std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;

        if(timepass <= 0){
            if(Keyboard::isKeyPressed(controls["Left"]) || Keyboard::isKeyPressed(Keyboard::Right)){
                hAnimation();
                noaction = false;
            }
            if(Keyboard::isKeyPressed(controls["Jump"]) & !jumping){
                noaction = false;
            }
            // Unfinsihed, will be ducking or something
            if(Keyboard::isKeyPressed(controls["Crouch"])){
                //noaction = false;
            }
            //Attacking
            if(Keyboard::isKeyPressed(controls["Attack"])){
                noaction = false;
            }
            timepass = .1;
            if(noaction){
                sprite.setTextureRect(IntRect(57, 11, 53, 60));
            }
        }
        flip(sprite);
    }

    void Enemy::setAnimation(){
        bool noaction = true;
        if(timepass <= 0){
            if(actions[0] || actions[1]){
                hAnimation();
                noaction = false;
            }
            if(actions[2] & !jumping){
                noaction = false;
            }
            //Unfinsihed, will be ducking or something
            if(actions[3]){
                //noaction = false;
            }
            //Attacking
            if(actions[4]){
                //noaction = false;
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

        // Needs to dereference controlMapping in order to read map
        std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;

        //Moving Left and Right with Collision
        if(Keyboard::isKeyPressed(controls["Left"])){
            faceright = false;
            sprite.move(Vector2f(-1.f * horizontalvel * time, 0));
        }
        else if(Keyboard::isKeyPressed(controls["Right"])){
            faceright = true;
            sprite.move(Vector2f(horizontalvel * time, 0));
        }
        if(Keyboard::isKeyPressed(controls["Jump"]) & !jumping){
            jumping = true;
            jumpvel = -400.f;
            sprite.move(Vector2f(0, jumpvel * time));
        }
        //Unfinsihed, will be ducking or something
        if(Keyboard::isKeyPressed(controls["Crouch"])){

        }
        //Attacking
        if(Keyboard::isKeyPressed(controls["Attack"])){
            attack(proj, Mouse::getPosition(window));
        }
        sprite.move(Vector2f(vertadd * time, horizadd * time));
        checkCollison(borders);
        checkProjectile(proj);
        setAnimation();
    }

    void Enemy::updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj, Time& timein, RenderWindow& window){
            float time = timein.asSeconds();
            actionstime -= time;
            actions[2] = 0;
            if(actionstime <= 0){
                actions.clear();
                for(int i = 0; i < 5; i++){
                    int ran = rand() % 2;
                    actions.push_back(ran);
                }
                actionstime = 2.f;
            }
           
            //Gravity and collision when jumpin
            weapontimer = weapontimer - time;
            timepass = timepass - time;
            jumpvel += 1100.f * time; // Vertical Acceleration 

            sprite.move(Vector2f(0, jumpvel * time));
            
            //Moving Left and Right with Collision
            if(actions[0]){
                faceright = false;
                sprite.move(Vector2f(-1.f * horizontalvel * time, 0));
            }
            else if(actions[1]){
                faceright = true;
                sprite.move(Vector2f(horizontalvel * time, 0));
            }
            if(actions[2] & !jumping){
                jumping = true;
                jumpvel = -400.f;
                sprite.move(Vector2f(0, jumpvel * time));
            }
            // Unfinished, will be ducking or something
            if(actions[3]){
                
            }
            // Attacking
            if(actions[4]){
                attack(proj, Mouse::getPosition(window));
            }
            checkCollison(borders);
            checkProjectile(proj);
            setAnimation();
    }

    Sprite& Character::getSprite(){
        return this->sprite;
    }

    void Character::attack(vector<Projectile*>& proj, Vector2i loc){
        if(weapontimer <= 0.f){
            string path;
            if(ene){
                path = "../Images/shot1.png";
            }
            else
            {
                path = "../Images/shot.png";
            }
            proj.push_back(new Projectile(path, sprite.getPosition().x, sprite.getPosition().y, (float)loc.x, (float)loc.y, this->ene));
            weapontimer = 1.f;
        }
    }    

