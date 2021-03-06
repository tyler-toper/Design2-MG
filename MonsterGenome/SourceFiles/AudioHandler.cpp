#include "../HeaderFiles/AudioHandler.h"

AudioHandler::AudioHandler(){
    state = GameState::MENU;
    prev = GameState::MENU;
    stateChanged = true;

    theme.openFromFile("../../Assets/Audio/Soundtracks/Theme.ogg");
    theme.setLoop(true);
    theme.setVolume(25);

    playBuffer.loadFromFile("../../Assets/Audio/Soundtracks/Deep Sea Abyss.wav");
    playSound.setBuffer(playBuffer);
    playSound.setLoop(true);
    playSound.setVolume(35);

    settingsBuffer.loadFromFile("../../Assets/Audio/Soundtracks/Gapman.wav");
    settingsSound.setBuffer(settingsBuffer);
    settingsSound.setLoop(true);
    settingsSound.setVolume(25);

    deathBuffer.loadFromFile("../../Assets/Audio/Soundtracks/Sad Story.wav");
    deathSound.setBuffer(deathBuffer);
    deathSound.setLoop(true);
    deathSound.setVolume(30);

}

void AudioHandler::setState(GameState::State newState){
    if(state != newState){
        stateChanged = true;
    }
    prev = state;
    state = newState;
}

void AudioHandler::playMusic(){
    if(stateChanged){
        stateChanged = false;
        if(state == GameState::MENU || prev == GameState::MENU){
            if(theme.getStatus() != Sound::Status::Playing){
                theme.play();
            }
        }
        else{
            theme.stop();
        }
        
        if(state == GameState::LVL1){
            if(prev == GameState::SAVELOAD || prev == GameState::DEAD) {
                playSound.stop();
            }
            playSound.play();
        }
        else if(state == GameState::MENU){
            playSound.stop();
        }
        else{
            playSound.pause();
        }

        if((state == GameState::PAUSE || state == GameState::SETTINGS || state == GameState::START || state == GameState::SAVELOAD) && prev != GameState::MENU){
            if(settingsSound.getStatus() != Sound::Status::Playing){
                settingsSound.play();
            }
        }
        else{
            settingsSound.stop();
        }

        if(state == GameState::DEAD){
            deathSound.play();
        }
        else{
            deathSound.stop();
        }
    }
}



