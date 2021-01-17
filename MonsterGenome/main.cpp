#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "Weapon.cpp"
#include "Armor.cpp"

using namespace std;
using namespace sf;

// Global path macros for files
#define WeaponStats "../../Assets/WeaponStats/Weapons.csv"
#define WeaponTextures "../../Assets/WeaponTextures/"
#define ArmorStats "../../Assets/ArmorStats/Armors.csv"
#define ArmorTextures "../../Assets/ArmorTextures/"


vector<Weapon> Weapons;
vector<Armor> Armors;

void loadAssets(){
    ifstream inFS;
    string line;

    // Load Weapons
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
        cout << "Unable to open file" << endl;
    }

    // Load Armors
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
    }

}

void openWindow(RenderWindow &window){
    while(window.isOpen()){
        window.clear(Color::White);
        Sprite knife(Weapons[2].texture);
        knife.setPosition(0, 0);
        window.draw(knife);

        Event event;
        while(window.pollEvent(event)){
            if(event.type == Event::Closed){
                window.close();
            }
        }

        window.display();
    }
}

int main() {
    RenderWindow window(VideoMode(1920, 1080), "The Monster Genome");
    loadAssets();
    openWindow(window);
    return 0;
}


// NOTE: The OpenGL glFlush() fail in Texture.cpp(98) occurs when allocating Texture objects without having
// a RenderWindow in the same scope. Everything still works fine with the error.