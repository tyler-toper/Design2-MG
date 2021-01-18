#include <iostream>
#include <vector>

#include "Weapon.h"
#include "Armor.h"
#include "LoadAssets.h"
#include "Menu.h"

#define windowWidth 1920
#define windowHeight 1440

vector<Weapon> Weapons;
vector<Armor> Armors;


void openWindow(RenderWindow &window){
    Menu menu(windowWidth, windowHeight);

    while(window.isOpen()){
        window.clear(Color::White);

        Texture texture;
        texture.loadFromFile("../../Assets/Backgrounds/Temp Background.png");
        Sprite background(texture);
        background.setPosition(0, 0);
        window.draw(background);


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
            if(event.type == Event::KeyPressed){
                if(event.key.code == Keyboard::Up){
                    menu.MoveUp();
                }
                if(event.key.code == Keyboard::Down){
                    menu.MoveDown();
                }
                if(event.key.code == Keyboard::Return){
                    if(menu.GetSelected() == 0){
                        cout << "Play has been selected." << endl;
                    }
                    else if(menu.GetSelected() == 1){
                        cout << "Settings has been selected." << endl;
                    }
                    else if(menu.GetSelected() == 2){
                        window.close();
                        break;
                    }
                }
            }
        }

        menu.Draw(window);
        window.display();
    }
}

int main() {
    RenderWindow window(VideoMode(windowWidth, windowHeight), "The Monster Genome");
    LoadAssets loader;
    loader.LoadWeapons(Weapons);
    loader.LoadArmor(Armors);
    openWindow(window);
    return 0;
}


// NOTE: The OpenGL glFlush() fail in Texture.cpp(98) occurs when allocating Texture objects without having
// a RenderWindow in the same scope. Everything still works fine with the error.