#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "Weapon.cpp"
#include "Armor.cpp"
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
    void LoadWeapons(vector<Weapon> &Weapons){
        inFS.open(WeaponStats);
        if(inFS.is_open()){
            int index = 0;
            while(getline(inFS, line)){
                stringstream ss(line);
                string word;
                vector<string> temp;

                while(getline(ss, word, ',')){
                    temp.push_back(word);
                }

                string filename = WeaponTextures;
                filename += to_string(index) + ".png";

                Texture texture;
                texture.loadFromFile(filename);

                Weapon weapon(stoi(temp[0]), temp[1], stoi(temp[2]), texture);
                Weapons.push_back(weapon);
                index++;
            }
            inFS.close();
        }
        else{
            cout << "Unable to load weapons" << endl;
        }
    }

    void LoadArmor(vector<Armor> &Armors){
        inFS.open(ArmorStats);
        if(inFS.is_open()){
            int index = 0;
            while(getline(inFS,line)){
                stringstream ss(line);
                string word;
                vector<string> temp;

                while(getline(ss, word, ',')){
                    temp.push_back(word);
                }

                string filename = ArmorTextures;
                filename += to_string(index) + ".png";

                Texture texture;
                texture.loadFromFile(filename);

                Armor armor(stoi(temp[0]), temp[1], stoi(temp[2]), texture);
                Armors.push_back(armor);
                index++;
            }
            inFS.close();
        }
        else{
            cout << "Unable to load armor" << endl;
        }
    }
};