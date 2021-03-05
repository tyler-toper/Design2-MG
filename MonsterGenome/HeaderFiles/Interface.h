#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
using namespace std;
using namespace sf;

class Interface
{
    enum InterfaceType
    {
        None,
        HUD,
        Menu,
        Store
    };
private:
    InterfaceType UI = None;
    Texture texture;
    Sprite UI_Display;
    Sprite Empty;
public:
    Interface();
    Interface(string name);
    Sprite& getSprite();                 //Returns the interface as a sprite
    void setInterface(string name);

};