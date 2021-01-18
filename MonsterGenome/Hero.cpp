#include <string>
using namespace std;

class Hero{
private:
    string name;
    int level;
    int vitality;
    int health;
    int strength;


public:
    int experience;

    Hero(){
        name = "player";
        level = 0;
        experience = 0;
        vitality = 0;
        strength = 0;
        health = 100;
    }

};