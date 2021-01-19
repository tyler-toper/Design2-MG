#include <vector>
#include <SFML/Graphics.hpp>
#include "Platforms.h"
using namespace std;
using namespace sf;

// Platfrom/Boundry with Picture
Platforms::Platforms(String path, float col, float row){
    name = "nogo";
    text.loadFromFile(path);
    sprite.setTexture(text);
    sprite.setPosition(Vector2f(col, row));
}

//Invisible Boundry
Platforms::Platforms(float col, float row, float col2, float row2){
    name = "nogo";
    text.create(col, row);
    Uint8* pixels = new Uint8(col * row * 4);
    text.update(pixels);
    sprite.setTexture(text);
    sprite.setColor(sf::Color(255, 255, 255, 255));
    sprite.setPosition(Vector2f(col2, row2));
}

Sprite& Platforms::getSprite(){
    return this->sprite;
}