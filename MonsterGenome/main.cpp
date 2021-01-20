#include <iostream>
#include <vector>

#include "Weapon.h"
#include "Armor.h"
#include "LoadAssets.h"
#include "Menu.h"
#include "Game.h"
#include "Hero.h"
#include "StateManager.h"

#define windowWidth 1024
#define windowHeight 768

vector<Weapon> Weapons;
vector<Armor> Armors;


void openWindow(RenderWindow &window){
    Menu menu(windowWidth, windowHeight);
    Game game;
    Hero hero;
    StateManager state;

    while(window.isOpen()){
        window.clear(Color::White);


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

        if(state.GetState() == StateManager::MENU){
            Texture texture;
            texture.loadFromFile("../../Assets/Backgrounds/Temp Background.png");
            Sprite background(texture);
            background.setPosition(0, 0);
            window.draw(background);

            Sprite sword(Weapons[2].texture);
            sword.setPosition(0, 0);
            window.draw(sword);

            menu.PollMenu(event, window, state);
            menu.Draw(window);
        }
        if(state.GetState() == StateManager::PLAY){
            game.PollGame();
            game.Draw(window);
        }


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