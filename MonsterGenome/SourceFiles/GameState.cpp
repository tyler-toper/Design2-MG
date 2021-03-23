#include "../HeaderFiles/GameState.h"

static GameState::State prev = GameState::MENU;

GameState::GameState() {
    playing = false;
    paused = false;
    state = GameState::MENU;
}

GameState::State GameState::GetState() const{
    return state;
}

bool GameState::IsPlaying() const{
    return playing;
}

void GameState::SetPlaying(bool cond){
    playing = cond;
}

void GameState::SetState(GameState::State NewState){
    prev = state;
    state = NewState;
}

GameState::State GameState::GetPrev(){
    return prev;
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