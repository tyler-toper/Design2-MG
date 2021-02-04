#include "../HeaderFiles/GameState.h"

GameState::GameState() {
    playing = false;
    paused = false;
    state = GameState::MENU;
}

GameState::State GameState::GetState(){
    return state;
}

bool GameState::IsPlaying() const{
    return playing;
}

void GameState::SetPlaying(bool cond){
    playing = cond;
}

void GameState::SetState(GameState::State NewState){
    state = NewState;
}

bool GameState::isPaused() const{
    return paused;
}

void GameState::Pause() {
    paused = true;
}

void GameState::Resume() {
    paused = false;
}