#include "../HeaderFiles/Interface.h"

Interface::Interface()
{
    UI = None;
}
Sprite& Interface::getInterface()
{
    if(UI != None)
    {
        return UI_Display;
    }
    return Empty;
}
void Interface::setInterface(string name)
{
    if(name == "HUD")
    {
        if(!texture.loadFromFile("../../Assets/UI/HUD.png"))
        {
            cout << "Error loading interface texture." << endl;
        }
        UI_Display.setTexture(texture);
        UI = HUD;
    }
    else if(name == "Menu")
    {
        if(!texture.loadFromFile("../../Assets/UI/Save_Menu.png"))
        {
            cout << "Error loading interface texture." << endl;
        }
        UI_Display.setTexture(texture);
        UI = Menu;
    }
    else if(name == "Store")
    {
        if(!texture.loadFromFile("../../Assets/UI/Weapons_Store.png"))
        {
            cout << "Error loading interface texture." << endl;
        }
        UI_Display.setTexture(texture);
        UI = Store;
    }
    else
    {
        UI = None;
    }
}