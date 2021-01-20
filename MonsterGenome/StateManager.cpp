#include "StateManager.h"

StateManager::StateManager() {
    s.push(MENU);
}

StateManager::State StateManager::GetState() {
    return s.top();
}

void StateManager::AddState(StateManager::State NewState) {
    s.push(NewState);
}

void StateManager::RemoveState() {
    s.pop();
}