#pragma once

#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Weapon.h"
#include "Armor.h"
using namespace std;
using namespace sf;

// Global path macros for files
#define WeaponStats "../../Assets/WeaponStats/Weapons.csv"
#define WeaponTextures "../../Assets/WeaponTextures/"
#define ArmorStats "../../Assets/ArmorStats/Armors.csv"
#define ArmorTextures "../../Assets/ArmorTextures/"

class LoadAssets{
private:
    ifstream inFS;
    string line;

public:
    void LoadWeapons(vector<Weapon> &Weapons);
    void LoadArmor(vector<Armor> &Armors);
};