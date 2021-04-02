#ifndef SWORD_H
#define SWORD_H

#include "MeleeWeapon.h"

class MeleeWeapon;

class Sword:public MeleeWeapon {
private:
    bool flipped = false;
    int first = 0;
    int recWidth = 48;
    int recHeight = 48;
    int rectLeft = 0;

public:
    Sword(unsigned level, string textureFile);
    virtual ~Sword();

    virtual Sword* clone();
    //void render(RenderWindow& window, View &playerView);
    virtual void update(RenderWindow& window, View& playerView);
    virtual void renderRight(RenderWindow& window, View &playerView);
    virtual void renderLeft(RenderWindow& window, View &playerView);
    void attackAnim(RenderWindow& window, View &playerView);
    void resetAnim(RenderWindow& window, View &playerView);
};


#endif //SWORD_H
