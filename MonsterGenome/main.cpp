#include <iostream>
#include <vector>

#include "Weapon.h"
#include "Armor.h"
#include "LoadAssets.h"
#include "Menu.h"
#include "Game.h"
#include "Pause.h"
#include "GameState.h"

#define windowWidth 1024
#define windowHeight 768
// To get a proper window size, maybe we can have an initial window to prompt the user to choose a resolution

vector<Weapon> Weapons;
vector<Armor> Armors;


void openWindow(RenderWindow &window){
    // TODO: Scale everything when changing window size
    Menu menu(windowWidth, windowHeight);
    Game game;
    Hero hero;
    Clock clock;
    Time time;
    GameState state;
    Pause pause(windowWidth, windowHeight);

    while(window.isOpen()){
        window.clear(Color::White);
        time = clock.restart();


        Event event;
        /*
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
*/
        if(state.GetState() == GameState::PLAY){
            game.PollGame(window, time, state);
            game.Draw(window, time);
        }
        else if(state.GetState() == GameState::MENU){
            menu.PollMenu(window, state);
            menu.Draw(window);
        }
        else if(state.GetState() == GameState::PAUSE){
            pause.PollMenu(window, state);
            pause.Draw(window);
        }
        else if(state.GetState() == GameState::SETTINGS){
            Texture texture;
            texture.loadFromFile("../../Assets/Backgrounds/Temp Background.png");
            Sprite background(texture);
            background.setPosition(0, 0);
            window.draw(background);
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