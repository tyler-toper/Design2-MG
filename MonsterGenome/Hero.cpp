#include "Hero.h"
using namespace std;
using namespace sf;

/// Constructors
Hero::Hero(){
    name = "player";
    level = 0;
    experience = 0;
    vitality = 0;
    strength = 0;
    health = 100;
    jumping = false;
    jumpvel = 0;
    horizontalvel = 200.f;
    text.loadFromFile("../Images/example.png");
    sprite.setTexture(text);
    sprite.setPosition(Vector2f(400.f, 300.f));

    //should be in weapons firerate
    float weapontimer = 0.f;

    // TODO: Reminder that people need to be able to update there controls without restarting the game!!!
    // TODO: Add controls being loading from file
    // Maybe convert keys to char
    // Load controls
    controls["Right"] = Keyboard::Right;
    controls["Left"] = Keyboard::Left;
    controls["Jump"] = Keyboard::Up;
    controls["Crouch"] = Keyboard::Down;
    controls["Attack"] = Keyboard::Space;
    controls["Reload"] = Keyboard::R;
    controls["Pause"] = Keyboard::P;
}

/// Getters
Sprite& Hero::getSprite(){
    return this->sprite;
}

// This could be expanded to all relevant variables, but I don't think its necessary yet.
string Hero::getName() {
    return this->name;
}

int Hero::getExperience(){
    return this->experience;
}

bool Hero::checkCollision(vector<Platforms*>& borders){
    for(int i = 0; i < borders.size(); i++){
        if(sprite.getGlobalBounds().intersects(borders[i]->getSprite().getGlobalBounds())){
            return true;
        }
    }
    return false;
}

/// Setters
// Could use a different structure than map, but need to settle on how controls are saved.
void Hero::setControls(std::map<std::string, Keyboard::Key> newControls) {
    controls["Right"] = newControls["Right"];
    controls["Left"] = newControls["Left"];
    controls["Jump"] = newControls["Jump"];
    controls["Crouch"] = newControls["Crouch"];
    controls["Attack"] = newControls["Attack"];
    controls["Reload"] = newControls["Reload"];
    controls["Pause"] = newControls["Pause"];
}

/// Mutators
void Hero::updatePosition(vector<Platforms*>& borders, vector<Projectile*>& proj, Time& timein, RenderWindow& window){
    //Gravity and collision when jumping
    //TODO: Should this be in milliseconds?
    float time = timein.asSeconds();
    //TODO: I feel this should be moved to its own function. It's weird to have the weapon state be messed with in the updatePosition function - Tyler
    weapontimer = weapontimer - time;
    jumpvel += 1100.f * time; // Vertical Acceleration

    sprite.move(Vector2f(0, jumpvel * time));
    if(checkCollision(borders)){
        sprite.move(Vector2f(0, -1.f * jumpvel * time));
        if(jumpvel > 0){
            state_ = STATE_STANDING;
        }
        jumpvel = 0;
    }

    // Movement
    // Moving Left with Collision
    if(Keyboard::isKeyPressed(controls["Left"])){
        sprite.move(Vector2f(-1.f * horizontalvel * time, 0));
        if(checkCollision(borders)){
            sprite.move(Vector2f(horizontalvel * time, 0));
        }
    }
    // Moving Right with Collision
    if(Keyboard::isKeyPressed(controls["Right"])){
        sprite.move(Vector2f(horizontalvel * time, 0));
        if(checkCollision(borders)){
            sprite.move(Vector2f(-1.f * horizontalvel * time, 0));
        }
    }
    // Jumping
    if(Keyboard::isKeyPressed(controls["Jump"]) && state_ != STATE_JUMPING){
        state_ = STATE_JUMPING;
        jumpvel = -800.f;
        sprite.move(Vector2f(0, jumpvel * time));
        if(checkCollision(borders)){
            sprite.move(Vector2f(0, -1.f * jumpvel * time));
        }
    }
    // Unfinished, will be ducking or something
    if(Keyboard::isKeyPressed(controls["Down"])){

        if(checkCollision(borders)){
            sprite.move(Vector2f(0.f, -.15));
        }
    }
    // Attacking
    if(Keyboard::isKeyPressed(controls["Attack"])){
        attack(proj, Mouse::getPosition(window));
    }
}

void Hero::updateState(){

}

void Hero::attack(vector<Projectile*>& proj, Vector2i loc){
    if(weapontimer <= 0.f){
        proj.push_back(new Projectile("../Images/shot.png", sprite.getPosition().x, sprite.getPosition().y, (float)loc.x, (float)loc.y));
        weapontimer = 1.f;
    }
}