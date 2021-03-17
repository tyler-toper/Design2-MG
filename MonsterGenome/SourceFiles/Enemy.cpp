#include "../HeaderFiles/Enemy.h"
using namespace std;
using namespace sf;

/// Enemy Functions
Enemy::Enemy(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY) : Character(borders, proj, actors, true) {
    int ID = 0;
    int xpDrop = 100;

    state_ = new StandingState();
    text.loadFromFile("../Images/animation2.png");
    sprite.setTexture(text);
    sprite.setPosition(Vector2f(spawnX, spawnY));
    sprite.setTextureRect(IntRect(57, 11, 50, 60));
}

// TODO: Add param to change health lost
void Enemy::checkMeleeHit(){
    if((actors[0][0]->getEnemy() != this->ene) && sprite.getGlobalBounds().intersects(actors[0][0]->getSprite().getGlobalBounds())){
        if(actors[0][0]->getAttack()){
            this->health -= 10;
        }
    }
}

void Enemy::updatePosition(Time& timein, RenderWindow& window, View &playerView){
    this->atk = false;

    float time = timein.asSeconds();
    actionstime -= time;
//    actions[2] = 0;
    if(actionstime <= 0){
        actions.clear();
        for(int i = 0; i < 6; i++){
            int ran = rand() % 2;
            actions.push_back(ran);
        }
        actionstime = 2.f;
    }

    //Gravity and collision when jumpin
    weapontimer = weapontimer - time;
    timepass = timepass - time;
    jumpvel += GRAV * time; // Vertical Acceleration

    sprite.move(Vector2f(0, jumpvel * time));
    state_->handleInput(*this, timein, window);
    state_->update(*this);

    sprite.move(Vector2f(vertadd * time, horizadd * time));
    checkCollison();
    checkProjectile();
    checkMeleeHit();
}

/// Enemy States
// Standing
void Enemy::StandingState::handleInput(Enemy& ene, Time& timein, RenderWindow& window) {
    float time = timein.asSeconds();

    //Moving Left and Right with Collision
    if(ene.actions[0]){
        ene.faceright = false;
        ene.sprite.move(Vector2f(-1.f * ene.horizontalvel * time, 0));
        ene.setAnimation("left");
    }
    else if(ene.actions[1]){
        ene.faceright = true;
        ene.sprite.move(Vector2f(ene.horizontalvel * time, 0));
        ene.setAnimation("right");
    }
    if(ene.actions[2]){
        ene.jump();
        ene.sprite.move(Vector2f(0, ene.jumpvel * time));
        ene.setAnimation("still"); //Change with animation
    }
    //Unfinsihed, will be ducking or something
    if(ene.actions[3]){
        ene.setAnimation("still"); //CHange with animation
    }
    //Attacking
    if(ene.actions[4]){
        //attack(proj, Mouse::getPosition(window));
        ene.setAnimation("still"); //Change with animation
    }
}

void Enemy::StandingState::update(Enemy& ene) {
    if (ene.actions[2]) {
        Enemy::EnemyState *temp = ene.state_;
        ene.state_ = new JumpingState();
        delete temp;
    }
}
// Jumping
void Enemy::JumpingState::handleInput(Enemy& ene, Time& timein, RenderWindow& window) {
    float time = timein.asSeconds();

    //Moving Left and Right with Collision
    if(ene.actions[0]){
        ene.faceright = false;
        ene.sprite.move(Vector2f(-1.f * ene.horizontalvel * time, 0));
        ene.setAnimation("left");
    }
    else if(ene.actions[1]){
        ene.faceright = true;
        ene.sprite.move(Vector2f(ene.horizontalvel * time, 0));
        ene.setAnimation("right");
    }
    else{
        ene.setAnimation("still");
    }
}

void Enemy::JumpingState::update(Enemy& ene) {
    for(int i=0; i < ene.borders->size(); i++){
        if(ene.sprite.getGlobalBounds().intersects(ene.borders[0][i]->getSprite().getGlobalBounds())){
            if(ene.borders[0][i]->getName() == "nogo" || ene.borders[0][i]->getName() == "M"){
                if(ene.aboveBelow(ene.sprite, ene.borders[0][i]->getSprite()) == 1){
                    Enemy::EnemyState *temp = ene.state_;
                    ene.state_ = new StandingState();
                    delete temp;
                }
            }
        }
    }
}

/// Fighter
Fighter::Fighter(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY) : Enemy(borders, proj, actors, spawnX, spawnY) {
    int ID = 0;
    int xpDrop = 100;

    // TODO: Determine what is necessary
    state_ = new StandingState();
    text.loadFromFile("../Images/animation2.png");
    sprite.setTexture(text);
    sprite.setPosition(Vector2f(spawnX, spawnY));
    sprite.setTextureRect(IntRect(57, 11, 50, 60));
}

void Fighter::setAnimation(string animation){
    if(timepass <= 0){
        // TODO: Add Control binding?
        if(animation == "melee"){
            this->punch = true;
            mAnimation();
        }
        else{
            if(animation == "left" || animation == "right"){
                hAnimation();
            }
            if(animation == "jump"){

            }
            //Unfinsihed, will be ducking or something
            if(animation == "crouch"){

            }
            //Attacking
            if(animation == "ranged"){

            }
        }

        timepass = .1;
        if(animation == "still"){
            sprite.setTextureRect(IntRect(57, 11, 50, 60));
        }
    }
    flip(sprite);
}
