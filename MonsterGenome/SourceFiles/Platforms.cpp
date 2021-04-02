#include <vector>
#include <SFML/Graphics.hpp>
#include "../HeaderFiles/Platforms.h"
using namespace std;
using namespace sf;

// Platfrom/Boundry with Picture
Platforms::Platforms(String path, float col, float row){
    name = "nogo";
    text.loadFromFile(path);
    sprite.setTexture(text);
    sprite.setPosition(Vector2f(col, row));
}

Platforms::Platforms(float col, float row, float col2, float row2, bool horiz){
    if(horiz){
        name = "nogo";
        text.create(col, row);
        Uint8 *pixels = new Uint8(col * row * 4);
        text.update(pixels);
        sprite.setTexture(text);
        sprite.setColor(sf::Color::Transparent);
        sprite.setPosition(Vector2f(col2, row2));
    }
    else {
        name = "N";
        text.create(col, row);
        Uint8 *pixels = new Uint8(col * row * 4);
        text.update(pixels);
        sprite.setTexture(text);
        sprite.setColor(sf::Color::Transparent);
        sprite.setPosition(Vector2f(col2, row2));
    }
}

MovePlatform::MovePlatform(String path, float col, float row, float endcol, float endrow, float speed) : Platforms(path, col, row){
    name = "M";
    this->speed = speed;
    this->totaldist = sqrt(pow((endcol - col),2) + pow((endrow - row),2));
    this->fliptime = totaldist / speed;
    xspeed = speed * (endcol - col) / totaldist;
    yspeed = speed * (endrow - row) / totaldist;
}

Sprite& Platforms::getSprite(){
    return this->sprite;
}

string Platforms::getName(){
    return this->name;
}

float MovePlatform::getXspeed(){
    return this->xspeed;
}

float MovePlatform::getYspeed(){
    return this->yspeed;
}

void Platforms::update(Time& timein){

}

void MovePlatform::update(Time& timein){
    float time = timein.asSeconds();
    this->fliptime -= time;
    if(fliptime <= 0){
        reverse();
    }
    this->getSprite().move(Vector2f(xspeed* time, yspeed * time));
}

void MovePlatform::reverse(){
    this->xspeed *= -1.f;
    this->yspeed *= -1.f;
    this->fliptime = (totaldist/speed - fliptime);
}

Checkpoint::Checkpoint(String path, float col, float row) : Platforms(path, col, row){
    name = "C";
    activated = false;
    this->resetLocation.x = col;
    this->resetLocation.y = row;
}

Vector2f Checkpoint::getLocation(){
    return this->resetLocation;
}

void Checkpoint::setActivation(){
    this->activated = true;
    text.loadFromFile("../../Assets/Copyright Free Textures/Space Texture Pack/Teleportation.png");
    sprite.setTexture(text, true);
    sprite.move(Vector2f(0, -72));
    /*Image img;
    img.loadFromFile("../../Assets/Copyright Free Textures/Space Texture Pack/Teleportation.png");
    text.update(img);*/
}

bool Checkpoint::getActivation(){
    return this->activated;
}