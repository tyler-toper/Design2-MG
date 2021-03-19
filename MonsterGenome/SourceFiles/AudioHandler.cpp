#include "../HeaderFiles/AudioHandler.h"

AudioHandler::AudioHandler(){
    state = GameState::MENU;
    stateChanged = true;

    theme.openFromFile("../../Assets/Audio/Soundtracks/Theme.ogg");
    theme.setLoop(true);
    theme.setVolume(25);

    playBuffer.loadFromFile("../../Assets/Audio/Soundtracks/Brave Worm.wav");
    playSound.setBuffer(playBuffer);
    playSound.setLoop(true);
    playSound.setVolume(25);

    settingsBuffer.loadFromFile("../../Assets/Audio/Soundtracks/Gapman.wav");
    settingsSound.setBuffer(settingsBuffer);
    settingsSound.setLoop(true);
    settingsSound.setVolume(25);

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
            theme.play();
        }
        else{
            theme.stop();
        }
        
        if(state == GameState::PLAY){
            playSound.play();
        }
        else{
            playSound.pause();
        }

        if(state == GameState::PAUSE || state == GameState::SETTINGS){
            if(settingsSound.getStatus() != Sound::Status::Playing){
                settingsSound.play();
            }
        }
        else{
            settingsSound.stop();
        }
    }
}



