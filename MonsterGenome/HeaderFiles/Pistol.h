#ifndef PISTOL_H
#define PISTOL_H

#include "RangedWeapon.h"

class RangedWeapon;

class Pistol: public RangedWeapon {
private:
    bool flipped = false;
    int first = 0;
    int recWidth = 64;
    int recHeight = 32;
    int rectLeft = 0;
public:
    Pistol(unsigned level, string textureFile);
    virtual ~Pistol();

    virtual Pistol* clone();
    virtual void update(RenderWindow& window, View &playerView);
    virtual void renderRight(RenderWindow& window, View &playerView);
    virtual void renderLeft(RenderWindow& window, View &playerView);
    void attackAnim(RenderWindow& window, View &playerView);
    void resetAnim(RenderWindow& window, View &playerView);
};


#endif //PISTOL_H
