#include <string>
using namespace std;

class Hero{
private:
    string name;
    int level;
    int vitality;
    int health;
    int strength;
    int experience;
    int armor;
    int levelUpXP;

    void checkLevel(){
        if(experience > levelUpXP){
            int carry = experience - levelUpXP;
            experience = carry;
            level++;
        }
    }

public:

    Hero(){
        name = "player";
        level = 1;
        experience = 0;
        vitality = 0;
        strength = 0;
        health = 100;
        armor = 0;
        levelUpXP = level * 2 * 1000;
    }

    void addXP(int xp){
        experience += xp;
        checkLevel();
    }

};