#include "../HeaderFiles/Character.h"
using namespace std;
using namespace sf;

    /// Character Functions
    // Private Functions
    int Character::rightLeft(Sprite& first, Sprite& second){
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

    bool Character::isAnyKeyPressed(std::map<std::string, sf::Keyboard::Key>* controlMapping)
	{
        for (auto const& x : controlMapping[0]){
            if (sf::Keyboard::isKeyPressed(controlMapping[0][x.first]))
				return true;
        }
		return false;
	}

    /// Character Functions
    // Constructor
    Character::Character(vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, bool ene){
        armor = 100;
        name = "player";
        level = 0;
        experience = 0;
        vitality = 0;
        strength = 0;
        health = 100;
        maxHealth = 100;
        jumpvel = 0;
        this->checkpoint = false;
        text.loadFromFile("../Images/animation2.png");
        sprite.setTexture(text);
        sprite.setPosition(Vector2f(400.f, 300.f));
        sprite.setTextureRect(IntRect(57, 11, 50, 60));
        this->borders = borders;
        this->proj = proj;
        this->actors = actors;
        //remove soon
        this->ene = ene;
        float timepass = .05;
        //should be in weapons fireratea
        /// Character Movement Attributes
        // Walking and Running
        horizontalvel = 200.f;
        baseHorizontalvel = 200.f;
        maxHorizontalvel = 400.f;
        horizontalAcc = 1.f;

        // Jumping
        jumpHeight = 400.0f;

        // Weapons
        reloadTime = 1.0f;
        charReloadMod = 1.0f;
        minCharReloadMod = 0.1f;
        maxCharReloadMod = 1.5f;
        charDamageMod = 0;
    }

    // Setters
    void Character::setAdditions(float v, float h){
        if(v == 0 && h == 0){
            this->vertadd = v;
            this->horizadd = h;
        }
        else{
            this->vertadd += v;
            this->horizadd += h;
        }
        
    }

    void Character::setAdditionsKnock(float v, float h){       
        this->vertaddKnock = v;
        this->horzaddKnock = h;

        //horzAccel Not used right now
        if(h > 0){
            this->horzAcel = abs(this->horzAcel) * -1;
        }
        else{
            this->horzAcel = abs(this->horzAcel);
        }
    }

    void Character::setKnockFrame(){
        if(this->vertaddKnock >= 0){
            this->horzaddKnock = 0;
            this->vertaddKnock = 0;
        }
    }

    void Character::resetCheck(){
        this->checkpoint = false;
    }

    // Getters
    Sprite& Character::getSprite(){
        return this->sprite;
    }

    bool Character::getAttack(){
        return this->atk;
    }

    bool Character::getEnemy(){
        return this->ene;
    }

    bool Character::getCheckPoint(){
        return this->checkpoint;
    }

    int Character::getHealth(){
        return this->health;
    }

    int Character::getMaxHealth(){
        return this->maxHealth;
    }

    vector<Platforms*>* Character::getBorders() {
        return this->borders;
    }

    Vector2f Character::getReset(){
        return this->resetPoint;
    }

    int Character::aboveBelow(Sprite& first, Sprite& second){
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

    float Character::getHorizontalVel() {
        return horizontalvel;
    }

    bool Character::isFaceright() {
        return faceright;
    }

    float Character::getJumpVel() {
        return jumpvel;
    }

    // Setters
    void Character::setFaceright(bool newFaceright) {
        faceright = newFaceright;
    }

    void Character::setHealth(int newHealth) {
        health = newHealth;
    }

    void Character::setMaxHealth(int newMaxHealth) {
        maxHealth = newMaxHealth;
    }

    // Mutators
    void Character::checkCollision(){
        for(int i=0; i < borders[0].size(); i++){
            FloatRect intersection;
            if(sprite.getGlobalBounds().intersects(borders[0][i]->getSprite().getGlobalBounds(), intersection)){
                if(borders[0][i]->getName() == "M"){
                    removeCollision(borders[0][i], intersection);
                    MovePlatform *d = static_cast<MovePlatform *>(borders[0][i]);
                    if(aboveBelow(sprite, d->getSprite()) == -1 && (d->getYspeed() > 0)){
                        d->reverse();
                    }
                    else if(aboveBelow(sprite, d->getSprite()) == 1){
                        setAdditions(d->getXspeed(), abs(d->getYspeed()));
                    }
                }
                else if(borders[0][i]->getName() == "C"){
                    if(!this->ene){
                        Checkpoint *d = static_cast<Checkpoint *>(borders[0][i]);
                        if(!d->getActivation()){
                            d->setActivation();
                            this->resetPoint = Vector2f(d->getLocation().x, d->getLocation().y - this->getSprite().getTextureRect().height);
                            this->checkpoint = true;
                        }
                    }
                }
                else{
                    removeCollision(borders[0][i], intersection);
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
                jumpvel = 0;
            }
            else{
                sprite.move(0, intersection.height);
                jumpvel = 0;
                vertaddKnock = 0;
            }
        }
        else{
            sprite.move(intersection.width * rightLeft(sprite, borders->getSprite()), 0);
        }
    }

    void Character::checkProjectile(){
        for(int i=0; i < proj[0].size(); i++){
            if((proj[0][i]->getEnemy() != this->ene) && sprite.getGlobalBounds().intersects(proj[0][i]->getSprite().getGlobalBounds())){
                damageCharacter(proj[0][i]->getDamage());
                delete proj[0][i];
                proj[0].erase(proj[0].begin() + i--);
            }
        }
    }

    // TODO: Move this to Hero and make the Character function virtual
    void Hero::checkMelee() {
        for(int i=1; i < actors[0].size(); i++){
            if(sprite.getGlobalBounds().intersects(actors[0][i]->getSprite().getGlobalBounds())){
                if (invultimer <= 0) {
                    // TODO: Fix this knockback issue
                    if (sprite.getPosition().x - actors[0][i]->getSprite().getPosition().x > 0) {
                        // Getting hit on right side
                        setAdditionsKnock(-350, 400);
                    } else {
                        // Getting hit on left side
                        setAdditionsKnock(-350, -400);
                    }
                    damageCharacter(10);
                }
            }
        }
    }

    void Character::flip(Sprite& sprite){
        sprite.setOrigin({ sprite.getGlobalBounds().width/2.0f, 0});
        sprite.setScale(pow(-1, !faceright), 1);
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

    void Character::attack(vector<Projectile*>* proj){
        if(weapontimer <= 0.f){
            // TODO: The path should be derived from the weapon the character is holding
            string path;
            if(ene){
                path = "../../Assets/Custom/Fireball1.png";
            }
            else
            {
                path = "../../Assets/Custom/Fireball2.png";
            }
            proj[0].push_back(new Projectile(path, sprite.getPosition().x, sprite.getPosition().y, this->faceright, this->ene, 10 + charDamageMod));
            // TODO: Load the weapons reload time instead of reloadTime variable
            weapontimer = reloadTime * charReloadMod;
        }
    }

    void Character::jump() {
        jumpvel = -jumpHeight;
    }

void Hero::weaponToggles(string key){
    if(key == "sword"){
        equipSw = true;
        equipPis = false;
    }
    else if(key == "pistol"){
        equipPis = true;
        equipSw = false;
    }
    else if(key == "all"){
        equipPis = false;
        equipSw = false;
    }
}


void Hero::equipWeapon(RenderWindow& window, View &playerView){
    std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;

    if (Keyboard::isKeyPressed(controls["Sword"])) {
        weaponToggles("sword");
    }

    if (Keyboard::isKeyPressed(controls["Pistol"])) {
        weaponToggles("pistol");
    }

    if (Keyboard::isKeyPressed(controls["Unequip"])) {
        weaponToggles("all");
    }

    if(equipSw){
        if (faceright) {
            sword->renderRight(window, playerView);
        }
        else if (!faceright) {
            sword->renderLeft(window, playerView);
        }
    }
    else if(equipPis){
        if (faceright) {
            pistol->renderRight(window, playerView);
        }
        else if (!faceright) {
            pistol->renderLeft(window, playerView);
        }
    }

}

void Hero::animWeapon(RenderWindow &window, View &playerView) {
    if(equipPis){
        if(Mouse::isButtonPressed(Mouse::Left)){
            pistol->attackAnim(window, playerView);
        }
        else{
            pistol->resetAnim(window, playerView);
        }
    }

    else if(equipSw){
        if(Mouse::isButtonPressed(Mouse::Left)){
            sword->attackAnim(window, playerView);
        }
        else{
            sword->resetAnim(window, playerView);
        }
    }
}

void Character::damageCharacter(int damageTaken) {
    if (invultimer <= 0) {
        health -= damageTaken;
        invultimer = maxInvulTime;
    }
}

void Character::healCharacter(int damageHealed) {
    if(health + damageHealed < maxHealth) {
        health += damageHealed;
    }
    else {
        health = maxHealth;
    }
}

/// Hero Functions
// Constructor
Hero::Hero(std::map<std::string, sf::Keyboard::Key>* controlMapping, vector<Platforms*>* borders, vector<Projectile*>* proj, vector<Character*>* actors, float spawnX, float spawnY) : Character(borders, proj, actors, false){
    this->resetPoint = Vector2f(spawnX, spawnY);
    this->controlMapping = controlMapping;
    state_ = new StandingState();

    // Safe spawning measures
    invultimer = 1.0f;

    // Jumping
    jumpCount = 0;
    jumpingHeld = false;
    jumpCountMax = 1;

    // Weapons Modification
    reloadTime = 0.5f;
    charReloadMod = 1.0f;
    minCharReloadMod = 0.1f;
    maxCharReloadMod = 1.5f;
    charDamageMod = 0;

    text.loadFromFile("../Images/animation2.png");
    sprite.setTexture(text);
    sprite.setPosition(Vector2f(spawnX, spawnY));
    sprite.setTextureRect(IntRect(57, 11, 50, 60));

    this->inventory = new Inventory(10);
    this->sword = new Sword(0, "../../Assets/WeaponTextures/sword_anim.png");
    this->pistol = new Pistol(0, "../../Assets/WeaponTextures/pistol_anim.png");

    //inv testing
    //cout << "Inv before add: " << this->inventory->getCap() << " " << this->inventory->getSize() << "\n";
    this->inventory->add(this->sword);
    this->inventory->add(this->pistol);
    //this->inventory->saveFile("../../Assets/WeaponStats/inventory.csv");

    //    cout << "Inv after add:  " << this->inventory->getCap() << " " << this->inventory->getSize() << "\n";
    //    this->inventory->remove(0);
    //    this->inventory->remove(0);
    //    cout << "Inv after removal:  " << this->inventory->getCap() << " " << this->inventory->getSize() << "\n";

}
// Setters
void Hero::setAnimation(string animation){
    // Needs to dereference controlMapping in order to read map
    std::map<std::string, sf::Keyboard::Key> controls = *controlMapping;


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

void Hero::setJumpingHeld(bool state) {
    jumpingHeld = state;
}

// Getters
int Hero::getJumpCount() const {
    return jumpCount;
}

bool Hero::isJumpingHeld() const {
    return jumpingHeld;
}

// Mutators
void Hero::updatePosition(Time& timein, RenderWindow& window, View &playerView){
    // Clear additions from previous frame update
    setAdditions(0.f, 0.f);
    float time = timein.asSeconds();
    this->atk = false;

    // Weapon control timer
    if(weapontimer > 0) {
        weapontimer = weapontimer - time;
    } else {
        weapontimer = 0;
    }

    // Invincibility timer
    if(invultimer > 0) {
        invultimer = invultimer - time;
    } else {
        invultimer = 0;
    }

    timepass = timepass - time;
    jumpvel += GRAV * time; // Vertical Acceleration

    vertaddKnock += GRAV * time;
    setKnockFrame();

    sprite.move(Vector2f(0, jumpvel * time));

    sprite.move(Vector2f(horzaddKnock * time, (vertaddKnock) * time));
    state_->handleInput(*this, timein, window, playerView);
    state_->update(*this);
    checkProjectile();
    checkMelee();

    //Gravity and collision when jumping
    checkCollision();
    // TODO: This is a one time setter to position, knockback in checkMelee() assumes that these are velocities that are saved
    // This could be a clean up spire.move and the above move is the one using velocity?
    sprite.move(Vector2f(vertadd * time, horizadd * time));
}

void Hero::run(bool isRunning) {
    if(isRunning) {
        if(horizontalvel < maxHorizontalvel) { horizontalvel += horizontalAcc; }
        else if (horizontalvel > maxHorizontalvel) { horizontalvel -= horizontalAcc; }
    }
    else {
        if (horizontalvel > baseHorizontalvel) { horizontalvel -= 2 * horizontalAcc; }
        else { horizontalvel = baseHorizontalvel; }
    }
}

void Hero::jump() {
    if (jumpCount > 0) {
        jumpvel = -jumpHeight;
        jumpCount--;
    }
}

void Hero::refreshJumps() {
    jumpCount = jumpCountMax;
}

bool Hero::improveJumpCount() {
    // TODO: Decide if a canImprove function is needed (to tell game to not give this as an option)
    if(jumpCountMax < jumpCountAbsMax) {
        jumpCountMax++;
        return true;
    }
    return false;
}

void Hero::modifyCharReloadMod(float change) {
    float min = minCharReloadMod;
    float max = maxCharReloadMod;
    if(charReloadMod + change >= min && charReloadMod + change <= max) {
        charReloadMod += change;
    }
    else if(charReloadMod + change < min) {
        charReloadMod = min;
    }
    else {
        charReloadMod = max;
    }
    // As an aside, the firerate doesn't increase linearly. Going from 1.0 to 0.9 is not the same as going from 0.9 to 0.8
}

void Hero::modifyCharDamageMod(int change) {
    int min = 0;
    if(charDamageMod + change >= min) {
        charDamageMod += change;
    }
    else {
        charDamageMod = min;
    }
}

void Hero::modifyMoveSpeed(float change) {
    baseHorizontalvel += change;
    maxHorizontalvel += change;
}

void Hero::modifyJumpHeight(float change) {
    jumpHeight += change;
}

// Hero States
// Standing
void Hero::StandingState::handleInput(Hero& hero, Time& timein, RenderWindow& window, View &playerView) {
    std::map<std::string, sf::Keyboard::Key> controls = *hero.controlMapping;
    float time = timein.asSeconds();

    // If the player is pressing left or right, but not at the same time, handle movement
    if (Keyboard::isKeyPressed(controls["Move Left"]) ^ Keyboard::isKeyPressed(controls["Move Right"])) {

        hero.run(Keyboard::isKeyPressed(controls["Run"]));

        if (Keyboard::isKeyPressed(controls["Move Left"])) {
            hero.faceright = false;
            // TODO: Move this to one spite.move function
            hero.sprite.move(Vector2f(-1.f * hero.horizontalvel * time, 0));
            hero.setAnimation("left");
        }
        if (Keyboard::isKeyPressed(controls["Move Right"])) {
            hero.faceright = true;
            // TODO: Move this to one spite.move function
            hero.sprite.move(Vector2f(hero.horizontalvel * time, 0));
            hero.setAnimation("right");
        }
    }
    else {
        // No movement, clear run speed
        hero.run(false);
    }
    if (!hero.isJumpingHeld() && Keyboard::isKeyPressed(controls["Jump"])) {
        hero.jump();

        // TODO: Move this to one spite.move function
        hero.sprite.move(Vector2f(0, hero.jumpvel * time));
        hero.setAnimation("still"); //CHange when we have animation}
    }

    //Unfinished, will be ducking or something
    if (Keyboard::isKeyPressed(controls["Crouch"])) {
        hero.setAnimation("still"); //CHange when we have animation

    }
    //Attacking
    if (Keyboard::isKeyPressed(controls["Attack"])) {
        hero.attack(hero.proj);
        hero.setAnimation("still"); //CHange when we have animation
    }
    if(!hero.isAnyKeyPressed(hero.controlMapping)){
        hero.setAnimation("still");
    }
}

void Hero::StandingState::update(Hero& hero) {
    std::map<std::string, sf::Keyboard::Key> controls = *hero.controlMapping;

    // Checking for ground
    bool isGrounded = false;
    for(int i=0; i < hero.borders->size(); i++) {
        if (hero.sprite.getGlobalBounds().intersects(hero.borders[0][i]->getSprite().getGlobalBounds())) {
            String name = hero.borders[0][i]->getName();
            if (name == "nogo" || name == "M") {
                if (hero.aboveBelow(hero.sprite, hero.borders[0][i]->getSprite()) == 1) {
                    isGrounded = true;
                }
            }
        }
    }


    // State transitions
    // TODO: Needs to detect when the player is no longer standing on platform
    if (!isGrounded) {
        Hero::HeroState *temp = hero.state_;
        hero.state_ = new JumpingState();
        delete temp;
    }
    else {
        // Refresh jumps
        hero.refreshJumps();
    }

    // Handling held keys
    // TODO: Move this to updatePosition?
    hero.setJumpingHeld(Keyboard::isKeyPressed(controls["Jump"]));

}

// Jumping
void Hero::JumpingState::handleInput(Hero& hero, Time& timein, RenderWindow& window, View &playerView) {
    std::map<std::string, sf::Keyboard::Key> controls = *hero.controlMapping;
    float time = timein.asSeconds();

    // If the player is pressing left or right, but not at the same time, handle movement
    if (Keyboard::isKeyPressed(controls["Move Left"]) ^ Keyboard::isKeyPressed(controls["Move Right"])) {
        if (Keyboard::isKeyPressed(controls["Move Left"])) {
            hero.faceright = false;
            // TODO: Move this to one spite.move function
            hero.sprite.move(Vector2f(-1.f * hero.horizontalvel * time, 0));
            hero.setAnimation("left");
        }
        if (Keyboard::isKeyPressed(controls["Move Right"])) {
            hero.faceright = true;
            // TODO: Move this to one spite.move function
            hero.sprite.move(Vector2f(hero.horizontalvel * time, 0));
            hero.setAnimation("right");

        }
    }
    else{
        hero.setAnimation("still");
    }

    //Attacking
    if (Keyboard::isKeyPressed(controls["Attack"])) {
        hero.attack(hero.proj);
        hero.setAnimation("still"); //CHange when we have animation
    }


    if (!hero.isJumpingHeld() &&  Keyboard::isKeyPressed(controls["Jump"])) {
        hero.jump();
    }

}

void Hero::JumpingState::update(Hero& hero) {
    std::map<std::string, sf::Keyboard::Key> controls = *hero.controlMapping;

    for(int i=0; i < hero.borders->size(); i++){
        if(hero.sprite.getGlobalBounds().intersects(hero.borders[0][i]->getSprite().getGlobalBounds())){
            String name = hero.borders[0][i]->getName();
            if(name == "nogo" || name == "M" ){
                if(hero.aboveBelow(hero.sprite, hero.borders[0][i]->getSprite()) == 1){
                    Hero::HeroState *temp = hero.state_;
                    hero.state_ = new StandingState();
                    delete temp;
                }
            }
        }
    }

    // Handling held keys
    // TODO: Move this to updatePosition?
    hero.setJumpingHeld(Keyboard::isKeyPressed(controls["Jump"]));
}

int Character::getDamageMod() const {
        return charDamageMod + 10;
    }

int Character::getCharReloadMod() const {
        return int(charReloadMod);
    }

int Character::getJumpCountMax() const {
        return jumpCountMax;
    }

int Character::getJumpHeight() const {
    return int(jumpHeight);
    }

int Character::getMoveSpeed() const {
        return int(baseHorizontalvel);
    }

