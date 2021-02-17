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
    Sprite& getInterface();                 //Returns the interface as a sprite
    void setInterface(string name);

};