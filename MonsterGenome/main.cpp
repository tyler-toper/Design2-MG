#include <iostream>
#include <vector>

#include "Weapon.h"
#include "Armor.h"
#include "LoadAssets.h"
#include "Menu.h"
#include "Game.h"
#include "Pause.h"
#include "Settings.h"
#include "GameState.h"

#define windowWidth 1024
#define windowHeight 768
// To get a proper window size, maybe we can have an initial window to prompt the user to choose a resolution

vector<Weapon> Weapons;
vector<Armor> Armors;

// TODO: Can make some functions for menus inherited

void openWindow(RenderWindow &window){
    // TODO: Scale everything when changing window size
    Menu menu(windowWidth, windowHeight);
    View mapView;
    View playerView(Vector2f((float)windowWidth/2, (float)windowHeight/2), Vector2f(windowWidth, windowHeight));
    window.setView(playerView);
    Game game;
    Hero hero;
    Clock clock;
    Time time;
    GameState state;
    Pause pause(windowWidth, windowHeight);
    Settings settings(windowWidth, windowHeight);


    while(window.isOpen()){
        window.clear(Color::White);
        time = clock.restart();

        /*
        Event e;
        while(window.pollEvent(e)){
            if(e.type == Event::Closed){
                window.close();
                break;
            }
            if(e.type == Event::LostFocus){
                // When the window is out of focus (not the active window). Pause game
            }
            if(e.type == Event::GainedFocus){
                // When the window regains focus (active window again). Resume game
            }
        }
        */

        if(state.GetState() == GameState::PLAY){
            game.PollGame(window, time, state);
            game.Draw(window, time, playerView, mapView);
        }
        else if(state.GetState() == GameState::MENU){
            menu.PollMenu(window, state);
            menu.Draw(window);
        }
        else if(state.GetState() == GameState::PAUSE){
            playerView.setSize(window.getSize().x, window.getSize().y);
            playerView.setCenter((float)windowWidth/2, (float)windowHeight/2);
            window.setView(playerView);
            pause.PollMenu(window, state);
            pause.Draw(window);

        }
        else if(state.GetState() == GameState::SETTINGS){
            Texture texture;
            texture.loadFromFile("../../Assets/Backgrounds/Temp Background.png");
            Sprite background(texture);
            background.setPosition(0, 0);
            window.draw(background);

            settings.PollMenu(window, state);
            settings.Draw(window);
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