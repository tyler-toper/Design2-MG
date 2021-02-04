#include "../HeaderFiles/Armor.h"

// Constructor
Armor::Armor(int id, string &Name, int armor, Texture &t){
    ID = id;
    name = Name;
    armorValue = armor;
    texture = t;
}

// Getters
int Armor::getID() const{
    return ID;
}

string Armor::getName() const{
    return name;
}

int Armor::getArmorValue() const{
    return armorValue;
}