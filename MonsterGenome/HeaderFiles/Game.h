#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include "../HeaderFiles/Character.h"
#include "../HeaderFiles/Enemy.h"
#include "../HeaderFiles/HeroMod.h"
#include "../HeaderFiles/Platforms.h"
#include "../HeaderFiles/GameState.h"
using namespace std;
using namespace sf;


class Game {
private:
    vector<Character*> players;
    vector<Platforms*> borders;
    vector<Projectile*> projs;
    std::map<std::string, sf::Keyboard::Key> *controlMapping;
    HeroMod* mod;
    int lvl;
    bool modify = false;
    Texture backgroundT;
    Sprite backgroundS;

    friend class StartMenu;
    friend class SaveLoadMenu;

    Texture HUD;
    Sprite HUDSprite;
    RectangleShape healthBar;

    Font font;
    Text deathPrompt[2];

    SoundBuffer confirmBuffer;
    Sound confirmSound;


public:
    explicit Game(std::map<std::string, sf::Keyboard::Key>* controlMapping, int lvl);

    void PollGame(RenderWindow &window, Time& time, GameState &state, View &playerView);
    void Draw(RenderWindow &window, Time& time, View &playerView, View &mapView);
    void LoadLevel(int lvl, int LoadCase);
    Character* getPlayer();

    void PollDeath(RenderWindow &window, GameState &state);
    void DrawDeath(RenderWindow &window);

};