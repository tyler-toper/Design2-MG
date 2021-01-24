#include "GameState.h"

GameState::GameState() {
    playing = false;
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