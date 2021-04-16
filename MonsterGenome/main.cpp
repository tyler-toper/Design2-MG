#include <iostream>
#include <vector>

#include "HeaderFiles/Weapon.h"
#include "HeaderFiles/Menu.h"
#include "HeaderFiles/Game.h"
#include "HeaderFiles/Pause.h"
#include "HeaderFiles/Settings.h"
#include "HeaderFiles/GameState.h"
#include "HeaderFiles/AudioHandler.h"
#include "HeaderFiles/StartMenu.h"
#include "HeaderFiles/SaveLoadMenu.h"

#define windowWidth 1024
#define windowHeight 768


void openWindow(RenderWindow &window){
    // Create objects
    Settings settings(windowWidth, windowHeight);
    Menu menu(windowWidth, windowHeight, settings.GetControlMapping());
    View mapView;
    View playerView(Vector2f((float)windowWidth/2, (float)windowHeight/2), Vector2f(windowWidth, windowHeight));
    window.setView(playerView);
    Game game(settings.GetControlMapping(), 1);
    Clock clock;
    Time time;
    GameState state;
    // Add Settings Controls Pointer/Reference
    Pause pause(windowWidth, windowHeight, settings.GetControlMapping(), game);
    AudioHandler audioHandler;
    StartMenu startMenu(windowWidth, windowHeight, settings.GetControlMapping());
    SaveLoadMenu SLMenu(windowWidth, windowHeight, settings.GetControlMapping());


    // Main game loop. While the window is open
    while(window.isOpen()){
        window.clear(Color::Black);
        time = clock.restart();
        audioHandler.setState(state.GetState());
        audioHandler.playMusic();

        if(state.GetState() == GameState::LVL1){
            game.PollGame(window, time, state, playerView);
            game.Draw(window, time, playerView, mapView);
        }
        else if(state.GetState() == GameState::MENU){
            state.SetPlaying(false);
            menu.PollMenu(window, state);
            menu.Draw(window);

        }
        else if(state.GetState() == GameState::PAUSE){
            playerView.setSize(window.getSize().x, window.getSize().y);
            playerView.setCenter((float)windowWidth/2, (float)windowHeight/2);
            window.setView(playerView);
            pause.PollMenu(window, state, game);
            pause.Draw(window);
        }
        else if(state.GetState() == GameState::SETTINGS){
            settings.PollMenu(window, state);
            settings.Draw(window);
        }
        else if(state.GetState() == GameState::START){
            startMenu.PollMenu(window, state, game);
            startMenu.Draw(window);
        }
        else if(state.GetState() == GameState::SAVELOAD){
            SLMenu.PollMenu(window, state, game);
            SLMenu.Draw(window);
        }
        else if(state.GetState() == GameState::DEAD){
            game.PollDeath(window, state);
            game.DrawDeath(window);
        }
    
        window.display();
    }
}

int main() {
    RenderWindow window(VideoMode(windowWidth, windowHeight), "The Monster Genome", Style::Titlebar | Style::Close);
    openWindow(window);
    return 0;
}