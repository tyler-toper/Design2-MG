#pragma once

class GameState {
private:
    bool playing;
public:
    enum State {PLAY, SETTINGS, MENU, PAUSE};
    State state;

    GameState();
    State GetState();
    bool IsPlaying() const;
    void SetPlaying(bool cond);
    void SetState(State NewState);
};

