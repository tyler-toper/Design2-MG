#include "../HeaderFiles/Projectile.h"
using namespace std;
using namespace sf;

Projectile::Projectile(String path, float col, float row, bool faceright, bool ene, int damage){
    name = "nogo";
    this->ene = ene;
    text.loadFromFile(path);
    sprite.setTexture(text);
    sprite.setPosition(Vector2f(col, row + 15));
    this->damage = damage;
    // TODO: Make velocity mutable
    if(faceright) {
        xvel = 250;
        sprite.setScale(2,2);
    }
    else {
        xvel = -250;
        sprite.setScale(-2,2);
    }
    yvel = 0;
}

bool Projectile::update(vector<Platforms*>& borders, Time& timein){
    float time = timein.asSeconds();
    sprite.move(Vector2f(xvel* time, yvel * time));
    return checkCollision(borders);
}

bool Projectile::checkCollision(vector<Platforms*>& borders){
    for(int i=0; i < borders.size(); i++){
        String name = borders[i]->getName();
        if(sprite.getGlobalBounds().intersects(borders[i]->getSprite().getGlobalBounds()) && name != "C"){
            return true;
        }
    }
    return false;
}

Sprite& Projectile::getSprite(){
    return this->sprite;
}

bool Projectile::getEnemy(){
    return this->ene;
}

int Projectile::getDamage() {
    return this->damage;
}