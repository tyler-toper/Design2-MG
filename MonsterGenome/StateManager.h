#pragma once

#include <stack>
using namespace std;


class StateManager {

public:
    enum State {PLAY, SETTINGS, MENU};
    stack<State> s;

    StateManager();
    State GetState();
    void AddState(State NewState);
    void RemoveState();
};

