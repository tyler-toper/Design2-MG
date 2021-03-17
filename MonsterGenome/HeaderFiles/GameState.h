#pragma once

class GameState {
private:
    bool playing;
    bool paused;
public:
    enum State {PLAY, SETTINGS, MENU, PAUSE, SAVE};
    State state;

    GameState();
    State GetState();
    void SetState(State NewState);
    bool IsPlaying() const;
    void SetPlaying(bool cond);
    bool isPaused() const;
    void Pause();
    void Resume();
};

