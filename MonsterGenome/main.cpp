#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "Weapon.cpp"
using namespace std;
using namespace sf;

vector<Weapon> Weapons;

void loadWeapons(){
    ifstream inFS("../WeaponStats/Weapons.csv");
    string line;

    while(getline(inFS, line)){
        int index = 0;
        stringstream ss(line);
        string word;
        vector<string> temp;

        while(getline(ss, word, ',')){
            temp.push_back(word);
        }

        string filename = "../WeaponSprites/";
        filename += to_string(index);
        filename += ".png";

        Texture texture;
        texture.loadFromFile(filename);

        Weapon weapon(stoi(temp[0]), temp[1], stoi(temp[2]), texture);
        Weapons.push_back(weapon);
        index++;
    }

}

void openWindow(){
    RenderWindow window(VideoMode(1920, 1080), "The Monster Genome");

    while(window.isOpen()){
        window.clear(Color::White);

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
    loadWeapons();
    //openWindow();
    return 0;
}
