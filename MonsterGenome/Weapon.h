#ifndef MAIN_CPP_WEAPON_H
#define MAIN_CPP_WEAPON_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
using namespace std;
using namespace sf;

class Weapon{
private:
    int ID;
    string name;
    int damage;

public:
    Texture texture;

    // Constructor
    Weapon(int id, string &Name, int Damage, Texture &t);

    // Getters
    int getID() const;
    string getName() const;
    int getDamage() const;
};


/*
 * Weapon Ideas: For easier implementation, use hitscan for all weapons except projectiles and throwables
 *
 *      Regular: Shoots normal bullets, medium damage
 *          Pistols, assault rifles, SMGs, shotguns, snipers
 *
 *      Lasers: Shoots continuous beam. Low damage, high rate of fire. Overheats
 *
 *      Plasma: Like blasters, medium damage
 *
 *      Gauss: High damage, slow rate of fire.
 *          Railguns
 *
 *      Projectile: High damage, but don't reach target immediately. Area of effect
 *          Grenade launchers, rocket launchers, guided rocket launcher
 *
 *      Throwables: High damage, but affected by gravity. Area of effect
 *          Grenades (HE, frag, incendiary ,etc.)
 *
 * Maybe charged weapons, burst fire. Special attacks? Pulse cannons?
 * Maybe elements: Fire, poison, energy, radiation, etc.
 */

#endif //MAIN_CPP_WEAPON_H
