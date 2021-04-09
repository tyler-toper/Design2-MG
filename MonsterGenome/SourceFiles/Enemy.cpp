#include "../HeaderFiles/Enemy.h"
using namespace std;
using namespace sf;

/// Enemy Functions
// Constructors
Enemy::Enemy(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY) : Character(borders, proj, actors, true) {
    int ID = 0;
    int xpDrop = 100;
    maxInvulTime = 0.3f;


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
    state_->handleInput(*this, timein, window);
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
void Fighter::StandingState::handleInput(Enemy& ene, Time& timein, RenderWindow& window) {
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
    if(actions[2]){
        ene.jump();
        ene.getSprite().move(Vector2f(0, ene.getJumpVel() * time));
        ene.setAnimation("still"); //Change with animation
    }
    //Unfinsihed, will be ducking or something
    if(actions[3]){
        ene.setAnimation("still"); //CHange with animation
    }
    //Attacking
    if(actions[4]){
        ene.setAnimation("still"); //Change with animation
    }
}

void Fighter::StandingState::update(Enemy& ene) {
    vector<int> actions = ene.getActions();
    if (actions[2]) {
        Enemy::EnemyState *temp = ene.getState();
        ene.setState(new JumpingState());
        delete temp;
    }
}

// Jumping
void Fighter::JumpingState::handleInput(Enemy& ene, Time& timein, RenderWindow& window) {
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

void Fighter::JumpingState::update(Enemy& ene) {
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
void Wanderer::StandingState::handleInput(Enemy& ene, Time& timein, RenderWindow& window) {
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
void Wanderer::JumpingState::handleInput(Enemy& ene, Time& timein, RenderWindow& window) {
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
