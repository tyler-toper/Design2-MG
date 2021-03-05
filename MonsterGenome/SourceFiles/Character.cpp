#include "../HeaderFiles/Character.h"
using namespace std;
using namespace sf;

    /// Generic Functions
    int aboveBelow(Sprite& first, Sprite& second){
        float fypos = first.getPosition().y;
        float fxpos = first.getPosition().x;
        int fheight = first.getTextureRect().height;
        int fwidth = first.getTextureRect().width;

        float sypos = second.getPosition().y;
        float sxpos = second.getPosition().x;
        int sheight = second.getTextureRect().height;
        int swidth = second.getTextureRect().width;

        if(((fxpos + fwidth/2) > sxpos) && ((fxpos - fwidth/2) < (sxpos + swidth))){
            if(fypos + fheight < sypos + sheight){
                return 1;
            }
            else if(fypos > sypos){
                return -1;
            }
        }
        return 0;
    }

    int rightLeft(Sprite& first, Sprite& second){
        float fxpos = first.getPosition().x;
        int fwidth = first.getTextureRect().width;

        float sxpos = second.getPosition().x;
        int swidth = second.getTextureRect().width;

        if((fxpos - fwidth/2) > sxpos){
            return 1;
        }
        else if((fxpos + fwidth/2) < (sxpos + swidth)){
            return -1;
        }
        else if((sxpos > (fxpos - fwidth/2)) && ((sxpos + swidth) < (fxpos + fwidth/2))){
            if(sxpos - (fxpos - fwidth/2) > ((fxpos + fwidth/2) - (sxpos + swidth))){
                return -1;
            }
            return 1;
        }
        else{
            return 0;
        }
    }

    /// Character Functions
    // Constructor
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

    // Getters
    // Setters
    void Character::setAdditions(float v, float h){
        this->vertadd = v;
        this->horizadd = h;
    }

    // Mutators
    void Character::checkCollison(vector<Platforms*>& borders){
        setAdditions(0.f, 0.f);
        for(int i=0; i < borders.size(); i++){
            FloatRect intersection;
            if(sprite.getGlobalBounds().intersects(borders[i]->getSprite().getGlobalBounds(), intersection)){
                removeCollision(borders[i], intersection);
                if(borders[i]->getName() == "M"){
                    MovePlatform *d = static_cast<MovePlatform *>(borders[i]);
                    if(aboveBelow(sprite, d->getSprite()) == -1 && (d->getYspeed() > 0)){
                        d->reverse();
                    }
                    else if(aboveBelow(sprite, d->getSprite()) == 1){
                        setAdditions(d->getXspeed(), abs(d->getYspeed()));
                    }
                }
            }
        }
    }

    void Character::removeCollision(Platforms* borders, FloatRect& intersection){
        int relative = aboveBelow(sprite, borders->getSprite());

        if(relative == 1 || relative == -1){
            if(intersection.width < intersection.height){
                sprite.move(intersection.width * rightLeft(sprite, borders->getSprite()), 0);
            }
            else if(relative == 1){
                sprite.move(0, intersection.height * -1.f);
                jumping = false;
                jumpvel = 0;
            }
            else{
                sprite.move(0, intersection.height);
                jumpvel = 0;
            }
        }
        else{
            sprite.move(intersection.width * rightLeft(sprite, borders->getSprite()), 0);
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

    void Character::checkMeleeHit(vector<Character*>& players){
        for(int i=1; i < players.size(); i++){
            if((players[i]->getEnemy() != this->ene) && sprite.getGlobalBounds().intersects(players[i]->getSprite().getGlobalBounds())){
                if(players[i]->getAttack()){
                    this->health -= 10;
                }
            }
        }
    }

    void Character::flip(Sprite& sprite){
        sprite.setOrigin({ sprite.getGlobalBounds().width/2.0f, 0});
        sprite.setScale({ int(pow(-1, !faceright)) , 1 });
    }

    void Character::hAnimation(){
        if(sprite.getTextureRect().top != 242 | sprite.getTextureRect().left == 396){
            sprite.setTextureRect(IntRect(36, 242, 50, 60));
        }
        else{
            sprite.setTextureRect(IntRect(sprite.getTextureRect().left+60, sprite.getTextureRect().top, 50, 60));
        }
    }

    void Character::mAnimation(){
        if(sprite.getTextureRect().top != 325 || sprite.getTextureRect().left == 336){
            sprite.setTextureRect(IntRect(36, 325, 50, 60));
        }
        else{
            sprite.setTextureRect(IntRect(sprite.getTextureRect().left+60, sprite.getTextureRect().top, 50, 60));
            if(sprite.getTextureRect().left == 156 || sprite.getTextureRect().left == 336){
                this->punch = false;
                this->atk = true;
            }
        }
    }

    Sprite& Character::getSprite(){
        return this->sprite;
    }

    bool Character::getAttack(){
        return this->atk;
    }

    bool Character::getEnemy(){
        return this->ene;
    }

    int Character::getHealth(){
        return this->health;
    }

    void Character::attack(vector<Projectile*>* proj, Vector2i loc){
        if(weapontimer <= 0.f){
            string path;
            if(ene){
                path = "../Images/shot1.png";
            }
            else
            {
                path = "../Images/shot.png";
            }
            proj[0].push_back(new Projectile(path, sprite.getPosition().x, sprite.getPosition().y, (float)loc.x, (float)loc.y, this->ene));
            weapontimer = 1.f;
        }
    }

    /// Hero Functions
    Hero::Hero(std::map<std::string, sf::Keyboard::Key>* controlMapping, vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* players) : Character(false){
        this->controlMapping = controlMapping;
        state_ = new StandingState();
        this->borders = borders;
        this->proj = proj;
        this->players = players;
    }

    void Hero::setAnimation(){
        bool noaction = true;
        // Needs to dereference controlMapping in order to read map
        std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;

        if(timepass <= 0){
            // TODO: Add Control binding?
            if(Keyboard::isKeyPressed(Keyboard::X) || this->punch){
                this->punch = true;
                mAnimation();
                noaction = false;
            }

            else{
                if(Keyboard::isKeyPressed(controls["Move Left"]) || Keyboard::isKeyPressed(controls["Move Right"])){
                    hAnimation();
                    noaction = false;
                }
                if(Keyboard::isKeyPressed(controls["Jump"]) & !jumping){
                    noaction = false;
                }
                //Unfinsihed, will be ducking or something
                if(Keyboard::isKeyPressed(controls["Crouch"])){
                    //noaction = false;
                }
                //Attacking
                if(Keyboard::isKeyPressed(controls["Attack"])){
                    noaction = false;
                }
            }

            timepass = .1;
            if(noaction){
                sprite.setTextureRect(IntRect(57, 11, 50, 60));
            }
        }
        flip(sprite);
    }

    void Hero::updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj,vector<Character*>& players,Time& timein, RenderWindow& window){
        float time = timein.asSeconds();
        this->atk = false;
       //Gravity and collision when jumpin
        weapontimer = weapontimer - time;
        timepass = timepass - time;
        jumpvel += 1100.f * time; // Vertical Acceleration

        sprite.move(Vector2f(0, jumpvel * time));
        state_->handleInput(*this, timein, window);
        state_->update(*this);

        sprite.move(Vector2f(vertadd * time, horizadd * time));
        checkCollison(*this->borders);
        checkProjectile(*this->proj);
        checkMeleeHit(*this->players);
        setAnimation();
    }
    // Hero States
    // Standing
    void Hero::StandingState::handleInput(Hero& hero, Time& timein, RenderWindow& window) {
        std::map<std::string, sf::Keyboard::Key> controls = *hero.controlMapping;
        float time = timein.asSeconds();

        if (Keyboard::isKeyPressed(controls["Move Left"])) {
            hero.faceright = false;
            hero.sprite.move(Vector2f(-1.f * hero.horizontalvel * time, 0));
        }
        else if (Keyboard::isKeyPressed(controls["Move Right"])) {
            hero.faceright = true;
            hero.sprite.move(Vector2f(hero.horizontalvel * time, 0));
        }
        if (Keyboard::isKeyPressed(controls["Jump"])) {
            hero.jumpvel = -400.f;
            hero.sprite.move(Vector2f(0, hero.jumpvel * time));
        }
        //Unfinished, will be ducking or something
        if (Keyboard::isKeyPressed(controls["Crouch"])) {

        }
        //Attacking
        if (Keyboard::isKeyPressed(controls["Attack"])) {
            hero.attack(hero.proj, Mouse::getPosition(window));
        }
    }

    void Hero::StandingState::update(Hero& hero) {
        std::map<std::string, sf::Keyboard::Key> controls = *hero.controlMapping;
        if (Keyboard::isKeyPressed(controls["Jump"])) {
            Hero::HeroState *temp = hero.state_;
            hero.state_ = new JumpingState();
            delete temp;
        }
    }
    // Jumping
    void Hero::JumpingState::handleInput(Hero& hero, Time& timein, RenderWindow& window) {
        std::map<std::string, sf::Keyboard::Key> controls = *hero.controlMapping;
        float time = timein.asSeconds();

        if (Keyboard::isKeyPressed(controls["Move Left"])) {
            hero.faceright = false;
            hero.sprite.move(Vector2f(-1.f * hero.horizontalvel * time, 0));
        }
        else if (Keyboard::isKeyPressed(controls["Move Right"])) {
            hero.faceright = true;
            hero.sprite.move(Vector2f(hero.horizontalvel * time, 0));
        }
    }

    void Hero::JumpingState::update(Hero& hero) {
        for(int i=0; i < hero.borders->size(); i++){
            if(hero.sprite.getGlobalBounds().intersects(hero.borders[0][i]->getSprite().getGlobalBounds())){
                if(hero.borders[0][i]->getName() == "nogo" || hero.borders[0][i]->getName() == "M"){
                   if(aboveBelow(hero.sprite, hero.borders[0][i]->getSprite()) == 1){
                       Hero::HeroState *temp = hero.state_;
                       hero.state_ = new StandingState();
                       delete temp;
                   }
                }
            }
        }
    }

/// Enemy Functions

    Enemy::Enemy() : Character(true) {
        int ID = 0;
        int xpDrop = 100;
    }

    void Enemy::checkMeleeHit(vector<Character*>& players){
        if((players[0]->getEnemy() != this->ene) && sprite.getGlobalBounds().intersects(players[0]->getSprite().getGlobalBounds())){
            if(players[0]->getAttack()){
                this->health -= 10;
            }
        }
    }

    void Enemy::setAnimation(){
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

    void Enemy::updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj, vector<Character*>& players, Time& timein, RenderWindow& window){
            this->atk = false; 

            float time = timein.asSeconds();
            actionstime -= time;
            actions[2] = 0;
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
            jumpvel += 1100.f * time; // Vertical Acceleration 

            sprite.move(Vector2f(0, jumpvel * time));
            if(actions[5]){

            }
            else{
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
                //Unfinsihed, will be ducking or something
                if(actions[3]){
                    
                }
                //Attacking
                if(actions[4]){
                    //attack(proj, Mouse::getPosition(window));
                }
            }
            sprite.move(Vector2f(vertadd * time, horizadd * time));
            checkCollison(borders);
            checkProjectile(proj);
            checkMeleeHit(players);
            setAnimation();
    }
