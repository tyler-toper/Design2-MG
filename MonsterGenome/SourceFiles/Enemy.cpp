#include "../HeaderFiles/Enemy.h"
using namespace std;
using namespace sf;

/// Enemy Functions
// Constructors
Enemy::Enemy(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY) : Character(borders, proj, actors, true) {
    int ID = 0;
    int xpDrop = 100;
    maxInvulTime = 0.3f;
    faceright = false;

    text.loadFromFile("../Images/animation2.png");
    sprite.setTexture(text);
    sprite.setPosition(Vector2f(spawnX, spawnY));
    sprite.setTextureRect(IntRect(57, 11, 50, 60));
}

// Getters
Enemy::EnemyState* Enemy::getState() {
    return state_;
}

vector<int> Enemy::getActions() {
    return actions;
}

// Setters
void Enemy::setState(Enemy::EnemyState* newState) {
    // TODO: Should this delete the old state?
    state_ = newState;
}

// Mutators
void Enemy::checkMelee(){
    if((actors[0][0]->getEnemy() != this->ene) && sprite.getGlobalBounds().intersects(actors[0][0]->getSprite().getGlobalBounds())){
        if(actors[0][0]->getAttack()){
            damageCharacter(10);
        }
    }
}

void Enemy::updatePosition(Time& timein, RenderWindow& window, View &playerView){
    float time = timein.asSeconds();
    setAdditions(0.f, 0.f);
    setActions(time);
    //Gravity and collision when jumpin
    weapontimer = weapontimer - time;
    timepass = timepass - time;
    jumpvel += GRAV * time; // Vertical Acceleration

    if(invultimer > 0) {
        invultimer = invultimer - time;
    } else {
        invultimer = 0;
    }
    sprite.move(Vector2f(0, jumpvel * time));
    state_->handleInput(*this, timein, window, playerView);
    state_->update(*this);

    sprite.move(Vector2f(vertadd * time, horizadd * time));
    checkCollision();
    checkProjectile();
    checkMelee();
}


/// Fighter
Fighter::Fighter(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY) : Enemy(borders, proj, actors, spawnX, spawnY) {
    int ID = 0;
    int xpDrop = 100;
    rectWidthDef = 62;
    rectHeightDef = 64;
    rectLeftA = 92;
    rectLeftW = 64;
    rectLeftI = 64;
    frameTime = 15;
    offset = 0;

    // TODO: Determine what is necessary
    state_ = new StandingState();
    text.loadFromFile("../../Assets/Copyright Free Textures/Dark Knight/darkknight_all.png");
    sprite.setTexture(text);
    sprite.setPosition(Vector2f(spawnX, spawnY));
    sprite.setTextureRect(IntRect(0, 0, rectWidthDef, rectHeightDef));


}
int Fighter::kb = 0;

void Fighter::setAnimation(string animation){
    if(timepass <= 0){
        // TODO: Add Control binding?
        if(animation == "left" || animation == "right"){
            setWalkAnim();
            setResumeAttack();
            //cout << "left or right" << endl;
        }

        else if(animation == "attack" && kb == 1){
            setAttackAnim();
            //cout << "attack" << endl;
        }


        else if(animation == "idle"){
            setIdleAnim();
            //cout << "idle" << endl;
        }

        timepass = .1;

        flip(sprite);
    }
}
void Fighter::setIdleAnim() {
    int rectWidth = 64;
    int rectHeight = 65;

    if((sprite.getTextureRect().top != 0)){
        sprite.setTextureRect(IntRect(0,0,rectWidth,rectHeight));
    }

    else{
        if(rectLeftI < 638) {
            rectLeftI += rectWidth;
            sprite.setTextureRect(IntRect(rectLeftI,0,rectWidth,rectHeight));


        }
        else if(rectLeftI >= 638){
            rectLeftI = 0;
            sprite.setTextureRect(IntRect(rectLeftI,0,rectWidth,rectHeight));

        }
    }
}


void Fighter::setWalkAnim() {

    if((sprite.getTextureRect().top != 66)){
        sprite.setTextureRect(IntRect(0,66,64,68));
    }

    else{
        if(rectLeftW < 746) {
            rectLeftW += 64;
            sprite.setTextureRect(IntRect(rectLeftW,66,64,68));

        }
        else if(rectLeftW >= 746){
            rectLeftW = 0;
            sprite.setTextureRect(IntRect(rectLeftW,66,64,68));
        }
    }


}

void Fighter::setAttackAnim() {
    int rectWidth = 57; //90
    int rectHeight = 81;
    int top = 136;

    if((sprite.getTextureRect().top != top)){
        sprite.setTextureRect(IntRect(0,top,rectWidth,rectHeight));
    }
    else{
        if(rectLeftA < 92*7) {
            rectLeftA += 92; 
            sprite.setTextureRect(IntRect(rectLeftA,top,rectWidth,rectHeight));
        }

        if(rectLeftA >= 92*7) {
            rectLeftA += 92; 
            sprite.setTextureRect(IntRect(rectLeftA,top,90,rectHeight));
        }

        if(rectLeftA >= 1522){
            kb = 0;
            rectLeftA = 0;
        }

    }

}
void Fighter::setResumeAttack() {
    rectLeftA = 0;
}



void Fighter::setActions(float time) {
    this->atk = false;

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
}

/// Fighter States
// Standing
void Fighter::StandingState::handleInput(Enemy& ene, Time& timein, RenderWindow& window, View &playerView) {
    int dist = 60;
    float time = timein.asSeconds();

    Vector2f plyr = playerView.getCenter();
    Vector2f enemyVect = ene.getSprite().getPosition();

    float playerRangeHigh = plyr.x + 175;
    float playerRangeLow = plyr.x - 175;


    if((enemyVect.x < playerRangeHigh) && (enemyVect.x > playerRangeLow)){

        float xDir = (plyr.x + 50) - enemyVect.x;
        float yDir = plyr.y - enemyVect.y;


        float dLen = sqrt((xDir * xDir) + (yDir * yDir));

        if(dLen < 500 && (plyr.x != enemyVect.x)){
            enemyVect.x += time * 85 * (xDir/dLen);
        }

        if((enemyVect.x > (plyr.x + dist)) && kb == 0){
            ene.setFaceright(false);
            ene.getSprite().setPosition(enemyVect.x, enemyVect.y);
            ene.setAnimation("right");
        }

        else if((enemyVect.x < (plyr.x - dist)) && kb == 0){
            ene.setFaceright(true);
            ene.getSprite().setPosition(enemyVect.x, enemyVect.y);
            ene.setAnimation("left");
        }

        else if((enemyVect.x <= (plyr.x + dist)) && (enemyVect.x >= (plyr.x - dist)) || kb == 1){
            kb = 1;
            ene.setAnimation("attack");
        }

        if((enemyVect.x > (plyr.x + dist)) && kb == 1){
            ene.setFaceright(false);
            ene.getSprite().setPosition(enemyVect.x, enemyVect.y);
            ene.setAnimation("right");

        }
        else if((enemyVect.x < (plyr.x - dist)) && kb == 1){
            ene.setFaceright(true);
            ene.getSprite().setPosition(enemyVect.x, enemyVect.y);
            ene.setAnimation("left");
        }
    }

    else{
        ene.setAnimation("idle");
    }

}

void Fighter::StandingState::update(Enemy& ene) {

}

/// Wanderer
Wanderer::Wanderer(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY) : Enemy(borders, proj, actors, spawnX, spawnY) {
    int ID = 0;
    int xpDrop = 100;

    // TODO: Determine what is necessary
    state_ = new StandingState();
    text.loadFromFile("../Images/animation2.png");
    sprite.setTexture(text);
    sprite.setPosition(Vector2f(spawnX, spawnY));
    sprite.setTextureRect(IntRect(57, 11, 50, 60));
}

void Wanderer::setAnimation(string animation){
    // TODO: Clean up and remove unneeded animations or make part of enemy class
    if(timepass <= 0){
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

void Wanderer::setActions(float time) {
    // TODO: Make hitting a wall change direction!
    updateFaceright();
    if(faceright) {
        actions[0] = 0;
        actions[1] = 1;
    }
    else {
        actions[0] = 1;
        actions[1] = 0;
    }
}

//Special Functions
void Wanderer::updateFaceright(){
    for(int i=0; i < getBorders()->size(); i++){
        if(getSprite().getGlobalBounds().intersects(getBorders()[0][i]->getSprite().getGlobalBounds())){
            if(getBorders()[0][i]->getName() != "C"){
                if(aboveBelow(getSprite(), getBorders()[0][i]->getSprite()) == 0 || getBorders()[0][i]->getName() == "N"){
                    cout << "hi" << endl;
                    int temp = rightLeft(getSprite(), getBorders()[0][i]->getSprite()); 
                    if(temp == 1){
                        cout << "hi1" << endl;
                        setFaceright(true);
                    }
                    else if(temp == -1){
                        cout << "hi2" << endl;
                        setFaceright(false);
                    }
                }
            }
        }
    }
}

/// Wanderer States
// Standing
void Wanderer::StandingState::handleInput(Enemy& ene, Time& timein, RenderWindow& window, View &playerView) {
    float time = timein.asSeconds();
    vector<int> actions = ene.getActions();
    // Moving Left and Right with Collision
    if(actions[0]){
        ene.setFaceright(false);
        ene.getSprite().move(Vector2f(-1.f * ene.getHorizontalVel() * time, 0));
        ene.setAnimation("left");
    }
    else if(actions[1]){
        //ene.setFaceright(true);
        ene.getSprite().move(Vector2f(ene.getHorizontalVel() * time, 0));
        ene.setAnimation("right");
    }
    ene.setActions(time);
}

void Wanderer::StandingState::update(Enemy& ene) {
    vector<int> actions = ene.getActions();
    // Make this falling
    if (actions[2]) {
        Enemy::EnemyState *temp = ene.getState();
        ene.setState(new JumpingState());
        delete temp;
    }
}

// Jumping
void Wanderer::JumpingState::handleInput(Enemy& ene, Time& timein, RenderWindow& window, View &playerView) {
    float time = timein.asSeconds();
    vector<int> actions = ene.getActions();
    //Moving Left and Right with Collision
    if(actions[0]){
        ene.setFaceright(false);
        ene.getSprite().move(Vector2f(-1.f * ene.getHorizontalVel() * time, 0));
        ene.setAnimation("left");
    }
    else if(actions[1]){
        ene.setFaceright(true);
        ene.getSprite().move(Vector2f(ene.getHorizontalVel() * time, 0));
        ene.setAnimation("right");
    }
    else{
        ene.setAnimation("still");
    }
}

void Wanderer::JumpingState::update(Enemy& ene) {
    for(int i=0; i < ene.getBorders()->size(); i++){
        if(ene.getSprite().getGlobalBounds().intersects(ene.getBorders()[0][i]->getSprite().getGlobalBounds())){
            if(ene.getBorders()[0][i]->getName() == "nogo" || ene.getBorders()[0][i]->getName() == "M"){
                if(ene.aboveBelow(ene.getSprite(), ene.getBorders()[0][i]->getSprite()) == 1){
                    Enemy::EnemyState *temp = ene.getState();
                    ene.setState(new StandingState());
                    delete temp;
                }
            }
        }
    }
}
