#include "../HeaderFiles/AudioHandler.h"

AudioHandler::AudioHandler(){
    state = GameState::MENU;
    playing = false;
    changedState = false;
}

void AudioHandler::setState(GameState::State newState){
    if(state != newState){
        changedState = true;
    }
    state = newState;
}

void AudioHandler::playMusic(){
    if(!playing || changedState){
        changedState = false;
        if(state == GameState::MENU){
            if(!theme.openFromFile("../../Assets/Audio/Soundtracks/Theme.ogg")){
                cout << "Failed to open music" << endl;
            }
            if(theme.getStatus() != SoundSource::Status::Playing){
                theme.play();
                playing = true;
            }
        }
        else{
            theme.stop();
        }
    }
}



