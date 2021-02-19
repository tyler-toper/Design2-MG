#include "../HeaderFiles/AudioHandler.h"

// TODO: Make functions to load and store sound (not music) files

AudioHandler::AudioHandler(){
    state = GameState::MENU;
    stateChanged = true;
}

void AudioHandler::setState(GameState::State newState){
    if(state != newState){
        stateChanged = true;
    }
    state = newState;
}

void AudioHandler::playMusic(){
    if(stateChanged){
        stateChanged = false;
        if(state == GameState::MENU){
            if(!theme.openFromFile("../../Assets/Audio/Soundtracks/Theme.ogg")){
                cout << "Failed to open music" << endl;
            }
            else{
                theme.play();
            }
        }
        else{
            theme.stop();
        }
        
        if(state == GameState::PLAY){
            // Can't pause right now since it loads the file every time
            if(!buffer.loadFromFile("../../Assets/Audio/Soundtracks/Brave Worm.wav")){
                cout << "Failed to load sound" << endl;
            }
            else{
                sound.setBuffer(buffer);
                sound.setLoop(true);
                sound.play();
            }
        }
        else{
            sound.stop();
        }

        if(state == GameState::PAUSE || state == GameState::SETTINGS){
            if(!buffer.loadFromFile("../../Assets/Audio/Soundtracks/Gapman.wav")){
                cout << "Failed to load sound" << endl;
            }
            else{
                sound.setBuffer(buffer);
                sound.setLoop(true);
                sound.play();
            }
        }

    }
}



