#include <iostream>
#include <vector>

#include "Weapon.h"
#include "Armor.h"
#include "LoadAssets.h"

vector<Weapon> Weapons;
vector<Armor> Armors;


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
                break;
            }
            if(event.type == Event::LostFocus){
                // When the window is out of focus (not the active window). Pause game
            }
            if(event.type == Event::GainedFocus){
                // When the window regains focus (active window again). Resume game
            }
        }

        window.display();
    }
}

int main() {
    RenderWindow window(VideoMode(1920, 1440), "The Monster Genome");
    LoadAssets loader;
    loader.LoadWeapons(Weapons);
    loader.LoadArmor(Armors);
    openWindow(window);
    return 0;
}


// NOTE: The OpenGL glFlush() fail in Texture.cpp(98) occurs when allocating Texture objects without having
// a RenderWindow in the same scope. Everything still works fine with the error.