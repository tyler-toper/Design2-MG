#ifndef SWORD_H
#define SWORD_H

#include "MeleeWeapon.h"

class MeleeWeapon;

class Sword:public MeleeWeapon {
private:
    bool flipped = false;
    int first = 0;
public:
    Sword(unsigned level, string textureFile);
    virtual ~Sword();

    virtual Sword* clone();
    //void render(RenderWindow& window, View &playerView);
    virtual void update(RenderWindow& window, View& playerView);
    virtual void renderRight(RenderWindow& window, View &playerView);
    virtual void renderLeft(RenderWindow& window, View &playerView);
};


#endif //SWORD_H
