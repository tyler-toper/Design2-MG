#include "../HeaderFiles/LoadAssets.h"

void LoadAssets::LoadWeapons(vector<Weapon> &Weapons){
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

void LoadAssets::LoadArmor(vector<Armor> &Armors){
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