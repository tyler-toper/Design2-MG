#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
using namespace sf;
using namespace std;
class Weapon{
private:
    string name;
    int damage;
    int ID;
    Texture texture;

public:
    // Constructor
    Weapon(int id, string &Name, int Damage, Texture &t){
        ID = id;
        name = Name;
        damage = Damage;
        texture = t;
    }

    // Getters
    int getID() const{
        return ID;
    }

    string getName() const{
        return name;
    }

    int getDamage() const{
        return damage;
    }

    Texture getTexture() const{
        return texture;
    }

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