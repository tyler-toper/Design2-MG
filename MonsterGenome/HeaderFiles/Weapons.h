#ifndef WEAPONS_H
#define WEAPONS_H

#include <SFML/Graphics.hpp>
#include "Items.h"

using namespace std;
using namespace sf;

class Weapons:public Items {
private:
    void initValues();

protected:
    Sprite weapSprite;
    Texture weapTexture;

    unsigned damage;
    Clock attackTimer;
    Int32 attackTimerMax;

public:
    Weapons(unsigned level, string textureFile);
/*
    Weapons(unsigned level, unsigned damage, string textureFile);
*/
    virtual ~Weapons();
    const bool getAttackTimer();

    virtual Items* clone()= 0;
    virtual void update(RenderWindow& window, View& playerView)=0;
    //void render(RenderWindow& window, View &playerView);
    virtual void renderRight(RenderWindow& window, View &playerView)=0;
    virtual void renderLeft(RenderWindow& window, View &playerView)=0;

};


#endif //WEAPONS_H
