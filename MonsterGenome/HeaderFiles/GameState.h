#pragma once

class GameState {
private:
    bool playing;
    bool paused;
public:
    enum State {MENU, SETTINGS, PAUSE, SAVE, LOAD, LVL1};
    State state;

    GameState();
    State GetState() const;
    static State GetPrev();
    void SetState(State NewState);
    bool IsPlaying() const;
    void SetPlaying(bool cond);
    bool isPaused() const;
    void Pause();
    void Resume();
};

