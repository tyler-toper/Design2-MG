#include "Weapon.h"

// Constructor
Weapon::Weapon(int id, string &Name, int Damage, Texture &t){
    ID = id;
    name = Name;
    damage = Damage;
    texture = t;
}

// Getters
int Weapon::getID() const{
    return ID;
}

string Weapon::getName() const{
    return name;
}

int Weapon::getDamage() const{
    return damage;
}
