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
    setAnimation();
}

/// Enemy States
// Standing
void Enemy::StandingState::handleInput(Enemy& ene, Time& timein, RenderWindow& window) {
    float time = timein.asSeconds();

    //Moving Left and Right with Collision
    if(ene.actions[0]){
        ene.faceright = false;
        ene.sprite.move(Vector2f(-1.f * ene.horizontalvel * time, 0));
    }
    else if(ene.actions[1]){
        ene.faceright = true;
        ene.sprite.move(Vector2f(ene.horizontalvel * time, 0));
    }
    if(ene.actions[2]){
        ene.jump();
        ene.sprite.move(Vector2f(0, ene.jumpvel * time));
    }
    //Unfinsihed, will be ducking or something
    if(ene.actions[3]){

    }
    //Attacking
    if(ene.actions[4]){
        //attack(proj, Mouse::getPosition(window));
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
    }
    else if(ene.actions[1]){
        ene.faceright = true;
        ene.sprite.move(Vector2f(ene.horizontalvel * time, 0));
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

void Fighter::setAnimation(){
    bool noaction = true;
    if(timepass <= 0){
        if(actions[5] || this->punch){
            this->punch = true;
            noaction = false;
            mAnimation();
        }
        else{
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
        }
        timepass = .1;
        if(noaction){
            sprite.setTextureRect(IntRect(57, 11, 50, 60));
        }
    }
    flip(sprite);
}
