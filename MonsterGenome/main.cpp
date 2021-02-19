#include <iostream>
#include <vector>

#include "HeaderFiles/Weapon.h"
#include "HeaderFiles/Armor.h"
#include "HeaderFiles/LoadAssets.h"
#include "HeaderFiles/Menu.h"
#include "HeaderFiles/Game.h"
#include "HeaderFiles/Pause.h"
#include "HeaderFiles/Settings.h"
#include "HeaderFiles/GameState.h"

#include <SFML/Audio.hpp>

#define windowWidth 1024
#define windowHeight 768
// To get a proper window size, maybe we can have an initial window to prompt the user to choose a resolution

vector<Weapon> Weapons;
vector<Armor> Armors;


void openWindow(RenderWindow &window){
    // TODO: Scale everything when changing window size
    // Create objects
    Menu menu(windowWidth, windowHeight);
    View mapView;
    View playerView(Vector2f((float)windowWidth/2, (float)windowHeight/2), Vector2f(windowWidth, windowHeight));
    window.setView(playerView);
    Game game;
    Clock clock;
    Time time;
    GameState state;
    Pause pause(windowWidth, windowHeight);
    Settings settings(windowWidth, windowHeight);

    Music music;
    if(!music.openFromFile("../../Assets/Audio/Soundtracks/Theme.ogg")){
        cout << "Failed to open music" << endl;
    }

    // Main game loop. While the window is open
    while(window.isOpen()){
        window.clear(Color::White);
        time = clock.restart();

        if(state.GetState() == GameState::PLAY){
            game.PollGame(window, time, state);
            game.Draw(window, time, playerView, mapView);
            music.stop();
        }
        else if(state.GetState() == GameState::MENU){
            if(music.getStatus() != SoundSource::Status::Playing){
                music.play();
            }
            menu.PollMenu(window, state);
            menu.Draw(window);
        }
        else if(state.GetState() == GameState::PAUSE){
            playerView.setSize(window.getSize().x, window.getSize().y);
            playerView.setCenter((float)windowWidth/2, (float)windowHeight/2);
            window.setView(playerView);
            pause.PollMenu(window, state);
            pause.Draw(window);
            music.stop();
        }
        else if(state.GetState() == GameState::SETTINGS){
            settings.PollMenu(window, state);
            settings.Draw(window);
            music.stop();
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