#include "Projectile.h"
using namespace std;
using namespace sf;

Projectile::Projectile(String path, float col, float row, float dir){
        name = "nogo";
        text.loadFromFile(path);
        sprite.setTexture(text);
        sprite.setPosition(Vector2f(col, row));
        xvel = 100 * dir;
        yvel = 0;
}

bool Projectile::update(vector<Platforms*>& borders, Time& timein){
    float time = timein.asSeconds();
    sprite.move(Vector2f(xvel* time, yvel * time));
    return checkCollision(borders);
}

bool Projectile::checkCollision(vector<Platforms*>& borders){
    for(int i=0; i < borders.size(); i++){
            if(sprite.getGlobalBounds().intersects(borders[i]->getSprite().getGlobalBounds())){
                return true;
            }
        }
        return false;
}

Sprite& Projectile::getSprite(){
        return this->sprite;
    }