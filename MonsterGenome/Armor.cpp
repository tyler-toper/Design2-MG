#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
using namespace std;
using namespace sf;

class Armor{
private:
    int ID;
    string name;
    int armorValue;

public:
    Texture texture;

    // Constructor
    Armor(int id, string &Name, int armor, Texture &t){
        ID = id;
        name = Name;
        armorValue = armor;
        texture = t;
    }

    // Getters
    int getID() const{
        return ID;
    }

    string getName() const{
        return name;
    }

    int getArmorValue() const{
        return armorValue;
    }


};

